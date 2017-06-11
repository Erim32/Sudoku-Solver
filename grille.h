#ifndef GRILLE_H
#define GRILLE_H

typedef struct
{
	int val ;
	/* Valeur de la case (0 si vide)*/
	int n_candidats ; /* Nombre de candidats possibles */
	int candidats[9] ; /* Liste de candidats */
} T_case;

typedef struct
{
	T_case grille[81] ; /*vecteur de 81 cases*/
} T_sudoku;

//retourne la valeur d'une case a partir de l'indice de la ligne et de l'indice de colonne.
void conversion_ind_ligne_colonne(int i, int* indiceLigne, int* indiceCol );
//retourne le numero de la case correspondant a indiceCol indiceLigne
int conversion_nuemro_case(int indiceLigne, int indiceCol);
//retourne  le numero de la region correspondant a une case de cooredonnée indiceLigne, indiceCol
int conversion_region(int indiceligne, int indiceCol);

//retourne la valeur de la case indiceligne indicecol
int get_valeur_case(const T_sudoku* sudoku, int indiceLigne, int indiceCol);
//retourne le nombre de candidat de la case indiceligne indicecol
int get_nbrcand_case(const T_sudoku* sudoku, int indiceLigne, int indiceCol);
//retourne dans tab et n_candidat respectivement un pointeur vers les candidats et le nombre de candidat de la case indiceligne indicecol
void get_cand_and_ncand_case(const T_sudoku* sudoku, int indiceLigne, int indiceCol, int** tab, int* n_candidats);

//definit la valeur de la case indliceLigne indiceCol egale a valeurCase
void set_valeur_case(T_sudoku* sudoku, int indiceLigne, int indiceCol, int valeurCase);
//definit la valeur position indiceCand du tableau des candidats de la case indliceLigne indiceCol egale a valeur
void set_valeur_case_candidats(T_sudoku* sudoku, int indiceLigne, int indiceCol, int indiceCandidat, int valeur);
//definit le nombre de candidat de la case indliceLigne indiceCol egale a valeur
void set_valeur_case_nbr_candidat(T_sudoku* sudoku, int indiceLigne, int indiceCol, int nbrCandidat);

#endif