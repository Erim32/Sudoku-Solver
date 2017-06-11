#include <stdbool.h>
#include "grille.h"


bool juste(const T_sudoku* sudoku) {
    //la somme des ligne est egale a 45
    for (int iligne = 0;  iligne < 9; ++iligne) {
        int sommeLigne = 0;
        for (int col = 0; col < 9; ++col) {
            int val = get_valeur_case(sudoku, iligne, col);
            if (val == 0)
                return false;
            else
                sommeLigne += val;
        }
        if (sommeLigne != 45)
            return false;
    }

    //la somme des colonnes est egale a 45
    for (int icol = 0; icol < 9; ++icol) {
        int sommeCol = 0;
        for (int ligne = 0; ligne < 9; ++ligne) {
            int val = get_valeur_case(sudoku, ligne, icol);
            if (val == 0)
                return false;
            else
                sommeCol += val;
        }
        if (sommeCol != 45)
            return false;
    }
    //sinon la grille est juste
    return true;
}
