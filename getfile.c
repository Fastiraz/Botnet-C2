#include <libssh2.h>
#include <libssh2_sftp.h>
#include <stdio.h>

char *deposerFichierSFTP(const char *nomFichier, const char *nomUtilisateur, const char *nomHote, const char *motDePasse) {
    int rc;
    LIBSSH2_SESSION *session;
    LIBSSH2_SFTP *sftp_session;
    LIBSSH2_SFTP_HANDLE *sftp_handle;

    // Initialiser libssh2. 

    if (libssh2_init(0) != 0) {
        return "Échec de l'initialisation de libssh2.#";
    }

    // Créer une session SSH.

    session = libssh2_session_init();

    if (session == NULL) {
        libssh2_exit();
        return "Impossible d'initialiser la session SSH.#";
    }

    // Se connecter au serveur distant. 

    if (libssh2_session_handshake(session, socket) != 0) {
        libssh2_session_disconnect(session, "Échec de la connexion.");
        libssh2_session_free(session);
        libssh2_exit();
        return "Échec de la connexion SSH. #";
    }

    // Authentification. */

    if (libssh2_userauth_password(session, nomUtilisateur, motDePasse) != 0) {
        libssh2_session_disconnect(session, "Échec de l'authentification.");
        libssh2_session_free(session);
        libssh2_exit();
        return "Échec de l'authentification SSH #.";
    }

    // Créer une session SFTP.

    sftp_session = libssh2_sftp_init(session);

    if (sftp_session == NULL) {
        libssh2_session_disconnect(session, "Échec de la création de la session SFTP.");
        libssh2_session_free(session);
        libssh2_exit();
        return "Échec de la création de la session SFTP. #";
    }

    // Ouvrir le fichier en local.

    FILE *file = fopen(nomFichier, "rb");

    if (!file) {
        libssh2_session_disconnect(session, "Impossible d'ouvrir le fichier local.");
        libssh2_session_free(session);
        libssh2_exit();
        return "Impossible d'ouvrir le fichier local. #";
    }

    // Créer un fichier sur le serveur distant.

    sftp_handle = libssh2_sftp_open(sftp_session, nomFichier, LIBSSH2_FXF_WRITE|LIBSSH2_FXF_CREAT|LIBSSH2_FXF_TRUNC, LIBSSH2_SFTP_S_IRUSR|LIBSSH2_SFTP_S_IWUSR);

    if (sftp_handle == NULL) {
        fclose(file);
        libssh2_session_disconnect(session, "Échec de la création du fichier distant.");
        libssh2_session_free(session);
        libssh2_exit();
        return "Échec de la création du fichier distant. #";
    }

    // Transférer les données du fichier local au fichier distant.

    char buffer[4096];
    size_t nread;

    while ((nread = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        if (libssh2_sftp_write(sftp_handle, buffer, nread) != nread) {
            fclose(file);
            libssh2_sftp_close(sftp_handle);
            libssh2_session_disconnect(session, "Échec de l'écriture dans le fichier distant.");
            libssh2_session_free(session);
            libssh2_exit();
            return "Échec de l'écriture dans le fichier distant. #";
        }
    }

    fclose(file);
    libssh2_sftp_close(sftp_handle);

    // Nettoyage et fermeture des sessions SSH et SFTP.

    libssh2_sftp_shutdown(sftp_session);
    libssh2_session_disconnect(session, "Fichier déposé avec succès.");
    libssh2_session_free(session);
    libssh2_exit();

    return "Fichier déposé avec succès. #";
}