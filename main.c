#include <stdbool.h>
#include <time.h>
#include "grille.h"
#include "inout.h"
#include "regles.h"
#include "resolution.h"



int main (int argc, char *argv[]) {
    /* Délcarations */
    T_sudoku sudoku;
    bool modePas;

    header();
    //recuperation de la grille
    if (argc == 1)
        saisie_grille(&sudoku);
    else if (argc == 2)
        recuperer_grille(&sudoku, argv[1]);
    else {
        message_erreur_nbr_fichier();
        return 1;
    }

    afficher_grille(&sudoku);
    modePas = selection_mode();

    /* Traitement */
    clock_t deb = clock();
    while (! juste(&sudoku)) {


        // mise a jour des cases.
        regle2(&sudoku);
        regle3(&sudoku);
        regle4(&sudoku);
        //en dernier pour eviter un passage des regles 1 2 3 sans effet
        regle1(&sudoku);

        if (modePas) {
            pas_a_pas(&sudoku);
        }
    }
    clock_t fin = clock();
    message_grille_resolu(&sudoku, (fin - deb) / CLOCKS_PER_SEC);

    return 0;
}