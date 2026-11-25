/*
 * Problema 2
 * Imbunatatiti interpretorul de la problema 1 astfel incat sa recunoasca
 * < si > ca redirectari ale intrarii si iesirii, realizand efectiv
 * redirectarile.
 *   Exemple:  ECOU salut > a.txt
 *             sort < nume.txt
 *
 * Utilizare: ex02
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void)
{
    /* Scrieti solutia aici */
    char linie[1024];
    char copie_linie[1024];
    char *args[64];

    while (1) {
        printf("> ");
        if (fgets(linie, sizeof(linie), stdin) == NULL) {
            break;
        }

        linie[strcspn(linie, "\r\n")] = '\0';

        if (strlen(linie) == 0) {
            continue;
        }

        strcpy(copie_linie, linie);

        char *in_file = NULL;
        char *out_file = NULL;
        char clean_linie[1024] = "";
        int argc = 0;

        char *token = strtok(linie, " ");
        while (token != NULL) {
            if (strcmp(token, "<") == 0) {
                token = strtok(NULL, " ");
                if (token != NULL) {
                    in_file = token;
                }
            }
            else if (strncmp(token, "<", 1) == 0 && strlen(token) > 1) {
                in_file = token + 1;
            }
            else if (strcmp(token, ">") == 0) {
                token = strtok(NULL, " ");
                if (token != NULL) {
                    out_file = token;
                }
            }
            else if (strncmp(token, ">", 1) == 0 && strlen(token) > 1) {
                out_file = token + 1;
            }
            else {
                if (argc < 63) {
                    args[argc++] = token;
                }
                if (clean_linie[0] != '\0') {
                    strcat(clean_linie, " ");
                }
                strcat(clean_linie, token);
            }
            token = strtok(NULL, " ");
        }
        args[argc] = NULL;

        if (argc == 0) {
            continue;
        }

        int saved_stdin = _dup(0);
        int saved_stdout = _dup(1);

        if (in_file != NULL) {
            int fd_in = _open(in_file, _O_RDONLY);
            if (fd_in == -1) {
                printf("Comanda incorecta\n");
                _close(saved_stdin);
                _close(saved_stdout);
                continue;
            }
            _dup2(fd_in, 0);
            _close(fd_in);
        }

        if (out_file != NULL) {
            int fd_out = _open(out_file, _O_WRONLY | _O_CREAT | _O_TRUNC, _S_IREAD | _S_IWRITE);
            if (fd_out == -1) {
                printf("Comanda incorecta\n");
                _dup2(saved_stdin, 0);
                _dup2(saved_stdout, 1);
                _close(saved_stdin);
                _close(saved_stdout);
                continue;
            }
            _dup2(fd_out, 1);
            _close(fd_out);
        }

        if (strcmp(args[0], "DIR") == 0 ||
            strcmp(args[0], "TIME") == 0 ||
            strcmp(args[0], "DATE") == 0) {
            system(clean_linie);
        }
        else if (strcmp(args[0], "COMANDA") == 0) {
            system("cmd");
        }
        else if (strcmp(args[0], "ECOU") == 0) {
            for (int i = 1; i < argc; i++) {
                printf("%s%s", args[i], (i < argc - 1) ? " " : "");
            }
            printf("\n");
        }
        else {
            intptr_t status = _spawnvp(_P_WAIT, args[0], (const char * const *)args);
            if (status == -1) {
                printf("Comanda incorecta\n");
            }
        }

        fflush(stdout);
        _dup2(saved_stdin, 0);
        _dup2(saved_stdout, 1);
        _close(saved_stdin);
        _close(saved_stdout);
    }

    return 0;
}
