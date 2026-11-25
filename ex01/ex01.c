/*
 * Problema 1
 * Realizati un interpretor de comenzi propriu:
 *   - recunoaste comenzile DIR, TIME, DATE, COMANDA, ECOU;
 *   - DIR, TIME, DATE sunt transmise interpretorului sistemului (cmd);
 *   - COMANDA lanseaza interpretorul sistemului pana se tasteaza EXIT;
 *   - ECOU afiseaza toate argumentele primite;
 *   - orice alta comanda e lansata ca program (spawnvp: directorul
 *     curent, apoi PATH); daca nu reuseste se afiseaza "Comanda incorecta";
 *   - separatorul dintre cuvinte este doar spatiul.
 *
 * Utilizare: ex01
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>

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

        int argc = 0;
        char *token = strtok(linie, " ");
        while (token != NULL && argc < 63) {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        args[argc] = NULL;

        if (argc == 0) {
            continue;
        }

        if (strcmp(args[0], "DIR") == 0 ||
            strcmp(args[0], "TIME") == 0 ||
            strcmp(args[0], "DATE") == 0) {
            system(copie_linie);
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
    }

    return 0;
}
