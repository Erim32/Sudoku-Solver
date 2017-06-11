#ifndef INOUT_H
#define INOUT_H

//Affiche le bandeau principal du programme
void header();

//selectione mode resultat final ou pas a pas
//return true pour un affichage pas a pas
bool selection_mode();

//attend la saisie du charactere pour continuer l'execution du programme
void pas_a_pas(T_sudoku* sudoku);

//Affiche une grille
void afficher_grille(const T_sudoku* sudoku);

//Permet de saisir, une grille
void saisie_grille(T_sudoku* sudoku);

//Permet la grille contenu dans un fichier file
void recuperer_grille(T_sudoku* sudoku, char file[]);
/*
 *  Messages
 */
//message lorsque la grille est resolu
void message_grille_resolu(T_sudoku* sudoku, float temps);

/*
 *Messages d'erreurs
 */
//message si le nombre d argument au programme est invalide
void message_erreur_nbr_fichier();

#endif