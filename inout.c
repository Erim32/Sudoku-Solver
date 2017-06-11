#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "grille.h"

void header() {
    printf(
        "==================================================================================================\n"
        "=                                                                                                =\n"
        "=   ,---.             ,--.       ,--.                ,---.         ,--.                          =\n"
        "=  '   .-' ,--.,--. ,-|  | ,---. |  |,-.,--.,--.    '   .-'  ,---. |  |,--.  ,--.,---. ,--.--.   =\n"
        "=  `.  `-. |  ||  |' .-. || .-. ||     /|  ||  |    `.  `-. | .-. ||  | \\  `'  /| .-. :|  .--'   =\n"
        "=  .-'    |'  ''  '\\ `-' |' '-' '|  \\  \\'  ''  '    .-'    |' '-' '|  |  \\    / \\   --.|  |      =\n"
        "=  `-----'  `----'  `---'  `---' `--'`--'`----'     `-----'  `---' `--'   `--'   `----'`--'      =\n"
        "=                                                                                                =\n"
        "=                                            Projet S3                                           =\n"
        "=                                       Auteur: Erim32 (github.com/Erim32)                       =\n"
        "==================================================================================================\n");
}

//affiche la grille sudoku
//PE sudoku de type T_sudoku
void afficher_grille(const T_sudoku* sudoku) {
    printf("\n");
    for (int numeroLigne = 0; numeroLigne < 9; ++numeroLigne) {
        // \all numeroLigne entier appartennant a [0 8]
        assert((numeroLigne >= 0) && (numeroLigne < 9));
        if (numeroLigne % 3 == 0) {
            //numeroLigne % 3 = 0
            assert(numeroLigne % 3 == 0);
            printf("+---------+---------+---------+\n");
        }
        for (int numeroCol = 0; numeroCol < 9; ++numeroCol) {
            // \all numeroCol entier appartennant a [0 8]
            assert((numeroCol >= 0) && (numeroCol < 9));
            if (numeroCol % 3 == 0) {
                //numeroCol % 3 = 0
                assert(numeroCol % 3 == 0);
                printf("|");
            }
            printf(" %d ", get_valeur_case(sudoku, numeroLigne, numeroCol));
        }
        printf("|\n");
    }
    printf("+---------+---------+---------+\n");
    printf("\n");
    //PS: void
}

//return true for pas a pas, return false pour affichage final
bool selection_mode() {
    char choix;
    printf("Saisisez un mode d'affichage:\n"
           "\t1)Pas a pas.\n"
           "\t2)Grille finale uniquement.\n");
    scanf(" %c", &choix);
    while ((choix != '1') && (choix != '2')) {
        printf("/!\\Saisie invalide recommencez: ");
        scanf(" %c", &choix);
        printf("\n");
    }
    return (choix == '1');
}

void pas_a_pas(T_sudoku* sudoku) {
    afficher_grille(sudoku);
    printf("Appuyer sur une touche pour continuer: ");
    getchar();
}


//message d'erreur a afficher si le nombre d'argument de l'appel du programme est invalide
void message_fichier_incorrect() {
    printf("/!\\ Erreur: Le fichier n\'existe pas ou le chemin est incorrect.\n");
}

//permet de saisir une grille de sudoku
void saisie_grille(T_sudoku* sudoku) {
    //PE: sudoku une grille de type T_sudoku
    printf("Saisissez votre grille:\n"
           "   Utilisez 0 pour remplir les cases vides.\n\n");
    for (int numeroLigne = 0; numeroLigne < 9; ++numeroLigne) {
        // \all numeroLigne entier appartennant a [0 8]
        assert((numeroLigne >= 0) && (numeroLigne < 9));
        for (int numeroCol = 0; numeroCol < 9; ++numeroCol) {
            // \all numeroLigne entier appartennant a [0 8]
            assert((numeroLigne >= 0) && (numeroLigne < 9) && (numeroCol >= 0) && (numeroCol < 9));
            char valeurSaisie = ' ';
            while (! ((valeurSaisie >= '0') && (valeurSaisie <= '9'))) {
                // \all numeroLigne entier appartennant a [0 8]
                assert((numeroLigne >= 0) && (numeroLigne < 9) && (numeroCol >= 0) && (numeroCol < 9) &&
                       (! ((valeurSaisie >= '0') && (valeurSaisie <= '9'))));
                scanf("%c", &valeurSaisie);
            }
            //conversion du charactere en chiffre
            valeurSaisie = valeurSaisie - '0';
            assert((numeroLigne >= 0) && (numeroLigne < 9) && (numeroCol >= 0) && (numeroCol < 9) &&
                   ((valeurSaisie >= 0) && (valeurSaisie < 10)));
            set_valeur_case(sudoku, numeroLigne, numeroCol, valeurSaisie);
            //\forall x tel que x = get_valeur_case(.. numeroLigne, numeroCol)  -> x = valeurSaisie
            assert(get_valeur_case(sudoku, numeroLigne, numeroCol) ==  valeurSaisie);
            if (valeurSaisie == 0) {
                //inv et condition
                assert((numeroLigne >= 0) && (numeroLigne < 9) && (numeroCol >= 0) && (numeroCol < 9) && (valeurSaisie == 0));
                //Affectation des cadidats
                for (int i = 0; i < 9; ++i) {
                    //all inv + condition
                    assert((numeroLigne >= 0) && (numeroLigne < 9) && (numeroCol >= 0) && (numeroCol < 9) && ((i >= 0) && (i < 9)));
                    set_valeur_case_candidats(sudoku, numeroLigne, numeroCol, i, i + 1);
                }
                set_valeur_case_nbr_candidat(sudoku, numeroLigne, numeroCol, 9);
                //\forall x = get_valeur_case_nbr_candidat(sudoku, numeroLigne, numeroCol) -> x = 9
                assert(get_nbrcand_case(sudoku, numeroLigne, numeroCol) ==  9);

            } else {
                //inv et  non condition
                assert((numeroLigne >= 0) && (numeroLigne < 9) && (numeroCol >= 0) && (numeroCol < 9) && (valeurSaisie != 0));
                set_valeur_case_nbr_candidat(sudoku, numeroLigne, numeroCol, 0);
                //\forall x = get_valeur_case_nbr_candidat(sudoku, numeroLigne, numeroCol) -> x = 9
                assert(get_nbrcand_case(sudoku, numeroLigne, numeroCol) ==  0);
            }
        }
    }
}

//lis le contenu d'un fichier et récupere les 81 valeurs nécessaire pour faire la grille de sudoku
void recuperer_grille(T_sudoku* sudoku, char file[]) {
    FILE *fp;
    char valeurSaisie;
    int indice = 0;
    fp = fopen(file, "r");
    if (fp == NULL) {
        message_fichier_incorrect();
        exit(0);
    }
    while ((valeurSaisie = fgetc(fp)) != EOF) {
        if ((valeurSaisie >= '0') && (valeurSaisie <= '9')) {
            int numeroLigne, numeroCol;
            conversion_ind_ligne_colonne(indice, &numeroLigne, &numeroCol);
            //conversion du charactere en chiffre
            valeurSaisie = valeurSaisie - '0';
            set_valeur_case(sudoku, numeroLigne, numeroCol, valeurSaisie);
            if (valeurSaisie == 0) {
                //Affectation des cadidats
                for (int i = 0; i < 9; ++i) {
                    set_valeur_case_candidats(sudoku, numeroLigne, numeroCol, i, i + 1);
                }
                set_valeur_case_nbr_candidat(sudoku, numeroLigne, numeroCol, 9);
            } else {
                set_valeur_case_nbr_candidat(sudoku, numeroLigne, numeroCol, 0);
            }
            indice += 1;
        }
    }
    fclose(fp);
}

//message si la grille a été resolu
void message_grille_resolu(T_sudoku* sudoku, float temps) {
    printf("==================================\n"
           "|            Grille resolue      |\n"
           "|            Temps: %.4f       |\n"
           "==================================\n\n", temps);

    afficher_grille(sudoku);

}

//message d'erreur a afficher si le nombre d'argument de l'appel du programme est invalide
void message_erreur_nbr_fichier() {
    printf("/!\\ Erreur: vous ne pouvez passer au maximum que 1 parametre.\n");
}

