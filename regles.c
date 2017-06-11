
#include <stdbool.h>
#include "grille.h"
#include <assert.h>
/*============================================================

 888888ba   88888888b  .88888.  dP         88888888b    d88
 88    `8b  88        d8'   `88 88         88            88
 a88aaaa8P' a88aaaa   88        88         a88aaaa       88
 88   `8b.  88        88   YP88 88         88            88
 88     88  88        Y8.   .88 88         88            88
 dP     dP  88888888P  `88888'  88888888P  88888888P    d88P

=============================================================*/

/*
 *Regle 1:
 *Si la case n'a qu'un candidat, on remplace la valeur 0
 * par le candidat.
 */
void regle1(T_sudoku* sudoku) {
    for (int i = 0; i < 81; ++i) {
        int* tab;
        int n_candidats, indiceLigne, indiceCol;
        conversion_ind_ligne_colonne(i, &indiceLigne, &indiceCol );
        get_cand_and_ncand_case(sudoku, indiceLigne, indiceCol, &tab, &n_candidats);
        if (n_candidats == 1) {
            set_valeur_case(sudoku, indiceLigne, indiceCol,  *(tab));
            set_valeur_case_nbr_candidat(sudoku, indiceLigne, indiceCol, 0);
        }
    }
}

/*====================================================================
 888888ba   88888888b  .88888.  dP         88888888b    d8888b.
 88    `8b  88        d8'   `88 88         88               `88
 a88aaaa8P' a88aaaa   88        88         a88aaaa      .aaadP'
 88   `8b.  88        88   YP88 88         88           88'
 88     88  88        Y8.   .88 88         88           88.
 dP     dP  88888888P  `88888'  88888888P  88888888P    Y88888P

======================================================================*/



/*****************************************************
 *              Fonctions utiles
*****************************************************/
//Supprime la premiere occurence de nbr dans le tableau tab et retourne le result de l'operation
bool pop(int* tab, int  taille, int nbr) {
    //Pe int* TAB, int taille [0 9], int nbr [0 ; 9]
    assert((taille >= 0) && (taille < 10) && (nbr >= 0) && (nbr < 10));
    int position = taille + 1;
    for (int j = 0; j < taille; ++j) {
        // j appartient a [0 taille]
        assert((taille >= 0) && (taille < 10) && (nbr >= 0) && (nbr < 10) && (j >= 0) && (j < taille));
        if (*(tab + j) == nbr) {
            // inv  + cond
            //j appartient a [0 taille] et *(tab + j) == nbr
            assert(((taille >= 0) && (taille < 10) && (nbr >= 0) && (nbr < 10)) && (*(tab + j) == nbr));
            position = j;
            break;
        }
    }
    if (position < taille) {
        assert((taille >= 0) && (taille < 10) && (nbr >= 0) && (nbr < 10) && (position < taille));
        for (int cpt = position; cpt < 9; ++cpt) {
            assert((taille >= 0) && (taille < 10) && (nbr >= 0) && (nbr < 10) && (position < taille)
                   && (cpt >= position) && (cpt <= 9));
            tab[cpt] = tab[cpt + 1];
        }
        return true;
    }
    return false;
}

/* Met a jour la liste des candidats et le nombre pour une case donnée,
   en fonction d'un tableau de nouveau candidat de nbrval element*/
void maj_candidats_case(T_sudoku* sudoku, int indligne, int indcol , int* tabValeurs, int nbrValeurs) {
    //pour chaque valeurs deja présente dans la ligne
    int* tab;
    int n_candidats;
    for (int i = 0; i < nbrValeurs; ++i) {
        get_cand_and_ncand_case(sudoku, indligne, indcol, &tab, &n_candidats);
        if (pop(tab, n_candidats, *(tabValeurs + i))) {
            n_candidats -= 1;
        }
        set_valeur_case_nbr_candidat(sudoku, indligne, indcol, n_candidats);
    }
}


/*****************************************************
 *              regle un occurence par ligne
*****************************************************/

//retourne dans un tableau tabout[9] les elements deja présent dans la ligne  et dans nbtabout le nbr d elements
void valeurs_dans_ligne(const T_sudoku* sudoku, int indligne, int* tabout, int *nbrtabout) {
    int taille = 0;
    for (int indcol = 0; indcol < 9; ++indcol) {
        int temp;
        temp = get_valeur_case(sudoku, indligne, indcol);
        if ( temp != 0) {
            *(tabout + taille)  = temp;
            taille += 1;
        }
    }
    //affecter la taille
    *(nbrtabout) = taille;
}


//Supprime dans une grille T_SUDOKU, toutes les candidats deja présente dans chaque ligne
void suppression_candidats_ligne(T_sudoku* sudoku) {
    for (int indligne = 0; indligne < 9; ++indligne) {
        int valeursLigne[9];
        int nbrvaleursLigne;
        valeurs_dans_ligne(sudoku, indligne, valeursLigne, &nbrvaleursLigne);
        for (int indcol = 0; indcol < 9; ++indcol) {
            if (get_valeur_case(sudoku, indligne, indcol) == 0) {
                maj_candidats_case(sudoku, indligne, indcol , valeursLigne, nbrvaleursLigne);
            }
        }
    }
}


/*****************************************************
 *              regle un occurence par colonne
 *****************************************************/
//retourne dans un tableau tabout[9] les elements deja présent dans la colonne dans nbtabout et le nbr d elements
void valeurs_dans_col(const T_sudoku* sudoku, int indcol, int* tabout, int *nbrtabout) {
    int taille = 0;
    for (int indligne = 0; indligne < 9; ++indligne) {
        int temp;
        temp = get_valeur_case(sudoku, indligne, indcol);
        if ( temp != 0) {
            *(tabout + taille) = temp;
            taille += 1;
        }
    }
    //affecter la taille
    *(nbrtabout) = taille;
}


//Supprime dans une grille T_SUDOKU, toutes les candidat deja présente dans chaque colonne
void suppression_candidats_col(T_sudoku* sudoku) {
    for (int indcol = 0; indcol < 9; ++indcol) {
        int valeursCol[9];
        int nbrvaleursCol;
        valeurs_dans_col(sudoku, indcol, valeursCol, &nbrvaleursCol);
        for (int indligne = 0; indligne < 9; ++indligne) {
            if (get_valeur_case(sudoku, indligne, indcol) == 0) {
                maj_candidats_case(sudoku, indligne, indcol , valeursCol, nbrvaleursCol);
            }
        }
    }
}


/*****************************************************
 *              regle un occurence groupement
*****************************************************/
//retourne dans un tableau tabout[9] les elements deja présent dans la region dans nbtabout et le nbr d elements
void valeurs_dans_region(const T_sudoku* sudoku, int numeroRegion, int* tabout, int *nbrtabout) {
    int indLigneDepart, indColDepart;
    *(nbrtabout) = 0;
    indLigneDepart = (numeroRegion / 3) * 3;
    indColDepart = (numeroRegion % 3) * 3;
    //recuperation des valeurs
    for (int parcoursLigne = 0; parcoursLigne < 3; ++parcoursLigne) {
        for (int parcoursCol = 0; parcoursCol < 3; ++parcoursCol) {
            int val = get_valeur_case(sudoku, (indLigneDepart + parcoursLigne), (indColDepart + parcoursCol));
            int taille = *(nbrtabout);
            if (val != 0) {
                *(tabout + taille) = val;
                *nbrtabout += 1;
            }
        }
    }
}

//Supprime dans une grille T_SUDOKU, toutes les valeurs deja présente dans chaque région
void suppression_candidats_region(T_sudoku* sudoku) {
    for (int numeroCase = 0; numeroCase < 81; ++numeroCase) {
        int indiceLigne, indiceCol, nbrvaleursReg;
        int valeursReg[9];
        nbrvaleursReg = 0;
        conversion_ind_ligne_colonne(numeroCase, &indiceLigne, &indiceCol );

        if (get_valeur_case(sudoku, indiceLigne, indiceCol) == 0) {
            int indiceRegion = ((indiceLigne / 3) * 3) + (indiceCol / 3);
            valeurs_dans_region(sudoku, indiceRegion, valeursReg, &nbrvaleursReg);
            for (int i = 0; i < nbrvaleursReg; ++i)
                maj_candidats_case(sudoku, indiceLigne, indiceCol , valeursReg, nbrvaleursReg);
        }
    }
}


/*Regle2:
 *Une occurence de valeur unique par groupement
 */
void regle2(T_sudoku* sudoku) {
    suppression_candidats_ligne(sudoku);
    suppression_candidats_col(sudoku);
    suppression_candidats_region(sudoku);
}



/*=========================================================================

 888888ba   88888888b  .88888.  dP         88888888b    d8888b.
 88    `8b  88        d8'   `88 88         88               `88
 a88aaaa8P' a88aaaa   88        88         a88aaaa       aaad8'
 88   `8b.  88        88   YP88 88         88               `88
 88     88  88        Y8.   .88 88         88               .88
 dP     dP  88888888P  `88888'  88888888P  88888888P    d88888P

 ==========================================================================*/
//Retourne la présence d'au moins une occurenc de "valeur" dans le tableau tab de "taille" éléments
bool est_dans_tab(int* tab, int taille, int valeur) {
    for (int i = 0; i < taille; ++i) {
        if (tab[i] == valeur)
            return true;
    }
    return false;
}

//Determine si oui ou non le candidat est présent une seule fois dans la ligne.
bool est_candidat_unique_ligne(T_sudoku* sudoku, int indLigne, int candidat) {
    int cptCandUnique = 0;
    //recuperer les valeurs deja dans la ligne
    int valeursLigne[9];
    int nbrvaleursLigne;
    valeurs_dans_ligne(sudoku, indLigne, valeursLigne, &nbrvaleursLigne);
    //parcourir les cases qui n'ont pas de valeur
    for (int indiceCol = 0; indiceCol < 9; ++indiceCol) {
        if (get_valeur_case(sudoku, indLigne, indiceCol) == 0) {
            //recuperation des valeurs dans dans la colonne
            int valeursDansColonne[9];
            int nbrvaleursCol;
            valeurs_dans_col(sudoku, indiceCol, valeursDansColonne, &nbrvaleursCol);
            //recuperation des candidats de la case
            int* tabCandCase;
            int nbrCandCase;
            get_cand_and_ncand_case(sudoku, indLigne, indiceCol, &tabCandCase, &nbrCandCase);
            for (int iCand = 0; iCand < nbrCandCase; ++iCand) {
                //si le candidat n est pas deja dans la ligne ni dans la colonne
                bool niDansLigneNiDansCol = ((! est_dans_tab(valeursLigne, nbrvaleursLigne, *(tabCandCase + iCand)))
                                             && (! est_dans_tab(valeursDansColonne, nbrvaleursCol, *(tabCandCase + iCand)) ));

                if (niDansLigneNiDansCol) {
                    // un passage obligatoire
                    if ((*(tabCandCase + iCand) == candidat))
                        cptCandUnique += 1;

                    if (cptCandUnique > 1)
                        return false;
                }
            }
        }
    }
    return (cptCandUnique == 1);
}

//Determine si oui ou non le candidat est présent une seule fois dans la colonne.
bool est_candidat_unique_col(T_sudoku* sudoku, int indiceCol, int candidat) {
    //recuperer les valeurs deja dans la colonne
    int valeursDeLaCol[9];
    int nbrvaleursCol;
    valeurs_dans_col(sudoku, indiceCol, valeursDeLaCol, &nbrvaleursCol);
    //parcourir les cases qui n'ont pas de valeur et chercher nbr occurence de chaque candidat
    int cptCandUnique = 0;
    for (int indiceLigne = 0; indiceLigne < 9; ++indiceLigne) {

        if (get_valeur_case(sudoku, indiceLigne, indiceCol) == 0) {

            //recuperer les valeurs deja dans la ligne testé
            int valeursLigne[9];
            int nbrvaleursLigne;
            valeurs_dans_ligne(sudoku, indiceLigne, valeursLigne, &nbrvaleursLigne);

            //recupere le tab des candidat de la case
            int* tabCandCase;
            int nbrCandCase;
            get_cand_and_ncand_case(sudoku, indiceLigne, indiceCol, &tabCandCase, &nbrCandCase);
            //pour chaque candidat
            for (int iCand = 0; iCand < nbrCandCase; ++iCand) {
                //si le candidat n est pas deja dans la ni dans la ligne colonne de la case teste (effet r2)
                bool niDansLigneNiDansCol = ((! est_dans_tab(valeursLigne, nbrvaleursLigne, *(tabCandCase + iCand)))
                                             && (! est_dans_tab(valeursDeLaCol, nbrvaleursCol, *(tabCandCase + iCand))));
                if (niDansLigneNiDansCol) {
                    if (tabCandCase[iCand] == candidat)
                        cptCandUnique += 1;

                    if (cptCandUnique > 1)
                        return false;
                }
            }
        }
    }
    return (cptCandUnique == 1);
}

//Determine si oui ou non le candidat est présent une seule fois dans la region.
bool est_candidat_unique_region(const T_sudoku* sudoku, int numeroRegion, int candidat) {
    int indLigneDepart, indColDepart;
    int cptCandUnique = 0;

    indLigneDepart = (numeroRegion / 3) * 3;
    indColDepart = (numeroRegion % 3) * 3;

    //recuperer les valeurs deja dans la region
    int valeursDansReg[9], nbrvaleursReg;
    valeurs_dans_region(sudoku, numeroRegion, valeursDansReg, &nbrvaleursReg);
    //recuperation des valeurs
    for (int parcoursLigne = 0; parcoursLigne < 3; ++parcoursLigne) {
        for (int parcoursCol = 0; parcoursCol < 3; ++parcoursCol) {
            int ligne   = (indLigneDepart + parcoursLigne);
            int colonne = (indColDepart + parcoursCol);
            if (get_valeur_case(sudoku, ligne, colonne) == 0) {
                //recuperations des valeurs des case dans la ligne et dans la colonne
                int valeursLigne[9], valeursDeLaCol[9], nbrvaleursLigne, nbrvaleursCol;
                valeurs_dans_ligne(sudoku, ligne, valeursLigne, &nbrvaleursLigne);
                valeurs_dans_col(sudoku, colonne, valeursDeLaCol, &nbrvaleursCol);


                //recuperer informations sur la case
                int* tabCandCase;
                int nbrCandCase;
                get_cand_and_ncand_case(sudoku, (indLigneDepart + parcoursLigne), (indColDepart + parcoursCol), &tabCandCase, &nbrCandCase);
                for (int iCand = 0; iCand < nbrCandCase; ++iCand) {
                    //si le candidat n est pas deja dans la region
                    bool pasDansGroupements = (  (!( est_dans_tab(valeursLigne, nbrvaleursLigne, *(tabCandCase + iCand)) )) &&
                                                 (!( est_dans_tab(valeursDeLaCol, nbrvaleursCol, *(tabCandCase + iCand)) )) &&
                                                 (!( est_dans_tab(valeursDansReg, nbrvaleursReg, *(tabCandCase + iCand)) )) );
                    if (pasDansGroupements) {
                        if (tabCandCase[iCand] == candidat)
                            cptCandUnique += 1;

                        if (cptCandUnique > 1)
                            return false;
                    }
                }
            }
        }
    }
    return (cptCandUnique == 1);
}


void regle3(T_sudoku* sudoku) {
    //pour chaque case
    for (int indiceLigne = 0; indiceLigne < 9; ++indiceLigne) {
        for (int indiceCol = 0; indiceCol < 9; ++indiceCol) {
            //si la case n a pas de valeur
            if (get_valeur_case(sudoku, indiceLigne, indiceCol) == 0) {
                //pour chaque candidats de la case
                int nbrCand;
                int* tabCand;
                int i = 0;
                get_cand_and_ncand_case(sudoku, indiceLigne, indiceCol, &tabCand, &nbrCand);
                //La valeur n'est pas deja dans la ligne ou la colonne
                int* tabValCol;
                int nbrValCol;
                get_cand_and_ncand_case(sudoku, indiceLigne, indiceCol, &tabValCol, &nbrValCol);

                //recuperation des valeurs dans la colonne
                int tabValDansCol[9], tabValLigne[9], tabValDansReg[9], nbrValDansCol, nbrValLigne, nbrValReg;
                valeurs_dans_col(sudoku, indiceCol, tabValDansCol, &nbrValDansCol);
                valeurs_dans_ligne(sudoku, indiceLigne, tabValLigne, &nbrValLigne);
                int region = (((indiceLigne / 3) * 3 ) + ( indiceCol / 3));
                valeurs_dans_region(sudoku, region, tabValDansReg, &nbrValReg);

                //tant que la case n'a pas de valeur et qu'on a pas tester tous les candidats
                while ((i < nbrCand) && (get_valeur_case(sudoku, indiceLigne, indiceCol) == 0) ) {
                    //si cand unique dans groupement
                    int cand = *(tabCand + i);
                    bool estCandUnique, pasDejaPresent;

                    estCandUnique = ((est_candidat_unique_ligne(sudoku, indiceLigne, cand)) ||
                                     (est_candidat_unique_col(sudoku, indiceCol, cand))  ||
                                     (est_candidat_unique_region(sudoku, region, cand)));

                    pasDejaPresent = ((! est_dans_tab(tabValLigne, nbrValLigne, cand))
                                      && (! est_dans_tab(tabValDansCol, nbrValDansCol, cand ))
                                      && (! est_dans_tab(tabValDansReg, nbrValReg, cand)));
                    if (estCandUnique && pasDejaPresent) {
                        //insertion et changement n_cand
                        set_valeur_case(sudoku, indiceLigne, indiceCol, cand);
                        set_valeur_case_nbr_candidat(sudoku, indiceLigne, indiceCol, 0);
                    }
                    i += 1;
                }
            }
        }
    }
}

/*=============================================================================

 888888ba   88888888b  .88888.  dP         88888888b    dP   dP
 88    `8b  88        d8'   `88 88         88           88   88
 a88aaaa8P' a88aaaa   88        88         a88aaaa      88aaa88
 88   `8b.  88        88   YP88 88         88                88
 88     88  88        Y8.   .88 88         88                88
 dP     dP  88888888P  `88888'  88888888P  88888888P         dP


================================================================================*/
bool deja_present_region(T_sudoku* sudoku, int indligne, int  indcol, int candidat) {
    int numeroRegion = conversion_region(indligne, indcol);

    //verification dans le grouppement
    int indLigneDepart, indColDepart;
    indLigneDepart = (numeroRegion / 3) * 3;
    indColDepart = (numeroRegion % 3) * 3;

    for (int addligne = 0; addligne < 3; ++addligne) {
        for (int addcol = 0; addcol < 3; ++addcol) {
            int ligne = indLigneDepart + addligne;
            int colonne = indColDepart + addcol;
            if (get_valeur_case(sudoku, ligne, colonne) == candidat)
                return true;
        }
    }

    return false;
}


//retourne si un candidat est present dans l'un des tabcand de la ligne indLigne entre indColDepart et indColFin
bool est_present_cand_ligne(const T_sudoku * sudoku, int indLigne, int indColDepart, int indColFin, int valeurTest) {
    //Pour chaque case de la ligne
    for (int indiceCol = indColDepart; indiceCol <= indColFin; ++indiceCol) {
        if (get_valeur_case(sudoku, indLigne, indiceCol) == 0) {
            //recuperer tabcand et nbrcand
            int nbrCand;
            int* tabCand;
            get_cand_and_ncand_case(sudoku, indLigne, indiceCol, &tabCand, &nbrCand);
            for (int i = 0; i < nbrCand; ++i) {
                if (*(tabCand + i) == valeurTest) {
                    return true;
                }
            }
        }
    }
    return false;
}


//retourne si un candidat est present dans l'un des tabcand de la ligne indLigne entre indColDepart et indColFin
bool est_present_cand_col(const T_sudoku * sudoku, int indCol, int indLigneDepart, int indLigneFin, int valeurTest) {
    //Pour chaque case de la colonne
    for (int indLigne = indLigneDepart; indLigne <= indLigneFin; ++indLigne) {
        if (get_valeur_case(sudoku, indLigne, indCol) == 0) {
            //recuperer tabcand et nbrcand
            int nbrCand;
            int* tabCand;
            get_cand_and_ncand_case(sudoku, indLigne, indCol, &tabCand, &nbrCand);
            for (int i = 0; i < nbrCand; ++i) {
                if (*(tabCand + i) == valeurTest) {
                    return true;
                }
            }
        }
    }
    return false;
}

//Supprime un candidat dans une ligne sauf dans les cases etre [indColDepart et indColDepart+2]
void supprimer_cand_dans_ligne_sauf_entre(T_sudoku * sudoku, int indligne, int indColDepart, int valeurAPop) {
    for (int i = 0; i < 9; ++i) {
        //si nous ne somme pas dans l'intervalle a concerver
        if (! ((i >= indColDepart) && (i <= (indColDepart + 2)))) {
            //suppression du candidat
            maj_candidats_case(sudoku, indligne, i , &valeurAPop, 1);
        }
    }
}

//Supprime un candidat dans une colonne sauf dans les cases etre [indLigneDepart et indLigneDepart+2]
void supprimer_cand_dans_col_sauf_entre(T_sudoku * sudoku, int indcol, int indLigneDepart, int valeurAPop) {
    for (int i = 0; i < 9; ++i) {
        //si nous ne somme pas dans l'intervalle a concerver
        if (! ((i >= indLigneDepart) && (i <= (indLigneDepart + 2)))) {
            //suppression du candidat
            maj_candidats_case(sudoku, i, indcol, &valeurAPop, 1);
        }
    }
}


//Determine si un candidat est présent sur au moins 2 case de la ligne, dans la region teste
bool cand_present_pls_fois_ligne_dans_region(T_sudoku* sudoku, int indligne, int indcol, int candidat) {
    int cptPresence = 0;
    for (int addc = 0; addc < 3; ++addc) {
        int colonne = (indcol + addc);
        if (get_valeur_case(sudoku, indligne, colonne) == 0) {
            int* tab;
            int n_candidats;
            get_cand_and_ncand_case(sudoku, indligne, colonne, &tab, &n_candidats);
            for (int x = 0; x < n_candidats; ++x) {
                if (*(tab + x) == candidat)
                    cptPresence += 1;
            }
        }
    }
    return (cptPresence > 1);
}

bool cand_present_pls_fois_colonne_dans_region(T_sudoku* sudoku, int indligne, int indcol, int candidat) {
    int cptPresence = 0;
    for (int addl = 0; addl < 3; ++addl) {
        int ligne = (indligne + addl);
        if (get_valeur_case(sudoku, ligne, indcol) == 0) {
            int* tab;
            int n_candidats;
            get_cand_and_ncand_case(sudoku, ligne, indcol, &tab, &n_candidats);
            for (int x = 0; x < n_candidats; ++x) {
                if (*(tab + x) == candidat)
                    cptPresence += 1;
            }
        }
    }
    return (cptPresence > 1);
}



//pour chaque region
void application_R4(T_sudoku* sudoku, int numeroRegion) {
    int indLigneDepart, indColDepart;
    indLigneDepart = (numeroRegion / 3) * 3;
    indColDepart = (numeroRegion % 3) * 3;

    //pour chaque candidat
    for (int candTest = 1; candTest < 10; ++candTest) {
        int cptEstDansLigne = 0;
        int cptEstDansCol = 0;
        int tempLignOrCol;
        bool presenceMultipleLigne, presenceMultipleColonne, dejaPresentRegion;


        /*
         *Verifications lignes
         */
        for (int addLigne = 0; addLigne < 3; ++addLigne) {
            int ligne = ((indLigneDepart + addLigne) % (indLigneDepart + 3));
            //si il n'est pas dja présent dans le groupement
            if (est_present_cand_ligne(sudoku, ligne , indColDepart, (indColDepart + 2), candTest)) {
                cptEstDansLigne += 1;
                tempLignOrCol = ligne;
            }
        }

        //si une unique ligne contient le candTest  et qu'il est présent plusieurs fois dans la region
        if (cptEstDansLigne == 1) {
            //verification de validite
            presenceMultipleLigne = cand_present_pls_fois_ligne_dans_region(sudoku, tempLignOrCol, indColDepart, candTest);
            dejaPresentRegion = deja_present_region(sudoku, tempLignOrCol, indColDepart, candTest);
            if (presenceMultipleLigne && (! dejaPresentRegion)) {
                //recuperation des informations valeurs présente relative a la case
                supprimer_cand_dans_ligne_sauf_entre(sudoku, tempLignOrCol, indColDepart, candTest);
            }

        }
        /*
         * Verification colonnes
         */

        for (int addCol = 0; addCol < 3; ++addCol) {
            if (est_present_cand_col(sudoku, ((indColDepart + addCol) % (indColDepart + 3)), indLigneDepart, (indLigneDepart + 2), candTest)) {
                cptEstDansCol += 1;
                tempLignOrCol = ((indColDepart + addCol) % (indColDepart + 3));
            }
        }
        //si une unique ligne contient le candTest
        if (cptEstDansCol == 1) {
            presenceMultipleColonne = cand_present_pls_fois_colonne_dans_region(sudoku, indLigneDepart, tempLignOrCol, candTest);
            dejaPresentRegion = deja_present_region(sudoku, indLigneDepart, tempLignOrCol, candTest);
            if (presenceMultipleColonne && (! dejaPresentRegion)) {
                supprimer_cand_dans_col_sauf_entre(sudoku, tempLignOrCol, indLigneDepart, candTest);
            }
        }
    }
}

void regle4(T_sudoku* sudoku) {
    for (int indiceRegion = 0; indiceRegion < 9; ++indiceRegion) {
        application_R4(sudoku, indiceRegion);
    }
}
