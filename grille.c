#include  <assert.h>
#include "grille.h"

/*
 * Conversion
 */
void conversion_ind_ligne_colonne(int i, int* indiceLigne, int* indiceCol ) {
	//PE: \all I  et I  appartient aux entiers natuerels et (I >= 0 && I < 81)
	assert((i >= 0) && (i < 81));
	*indiceCol 		= i % 9;
	*indiceLigne	= i / 9;
	/*PS: \all I ->(
	 *       ((indiceLigne >= 0) && (indiceLigne < 9) et
	 *       ((indiceCol >= 0) && (indiceCol < 9)
	 */
	assert(((*indiceCol)   >= 0) && (*indiceCol < 9));
	assert(((*indiceLigne) >= 0) && (*indiceLigne < 9));
}


int conversion_numero_case(int indiceLigne, int indiceCol) {
	assert((indiceLigne >= 0) && (indiceLigne < 9));
	assert((indiceCol >= 0)   && (indiceCol < 9));
	return ((9 * indiceLigne) + indiceCol);
}

int conversion_region(int indiceligne, int indiceCol) {
	return (((indiceligne / 3) * 3) + (indiceCol / 3));
}

/*
*get
*/
int get_valeur_case(const T_sudoku* sudoku, int indiceLigne, int indiceCol) {
	return (sudoku->grille[(indiceLigne * 9) + indiceCol].val);
}

int get_nbrcand_case(const T_sudoku* sudoku, int indiceLigne, int indiceCol) {
	return (sudoku->grille[(indiceLigne * 9) + indiceCol].n_candidats);
}

void get_cand_and_ncand_case(const T_sudoku* sudoku, int indiceLigne, int indiceCol, int ** tab, int * n_candidats) {
	*n_candidats = get_nbrcand_case(sudoku, indiceLigne, indiceCol);
	*tab = &(sudoku->grille[(indiceLigne * 9) + indiceCol]).candidats;
	//Je ne sais pas comment corriger le passage d'adresse vers le pointeur
}


/*
* set
*/
void set_valeur_case(T_sudoku* sudoku, int indiceLigne, int indiceCol, int valeurCase) {
	sudoku->grille[(9 * indiceLigne) + indiceCol].val = valeurCase;
}

void set_valeur_case_candidats(T_sudoku* sudoku, int indiceLigne, int indiceCol, int indiceCandidat, int valeur) {
	sudoku->grille[(9 * indiceLigne) + indiceCol].candidats[indiceCandidat] = valeur;

}

void set_valeur_case_nbr_candidat(T_sudoku* sudoku, int indiceLigne, int indiceCol, int nbrCandidat) {
	sudoku->grille[(9 * indiceLigne) + indiceCol].n_candidats = nbrCandidat;
}

