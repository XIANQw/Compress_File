#ifndef ARBRE_H
#define ARBRE_H

/*
 * Il n'est pas necessaire de connaitre le contenu de la structure
 * pour une utilisation extérieure, à condition d'utiliser les
 * fonctions telles que les constructeurs / destructeurs, get_freq, etc.
 */
typedef struct noeud_m * arbre_t;
struct noeud_m {
  float freq;
  int lettre; /* si le noeud n'est pas une feuille, on peut par exemple mettre le maximum des codes ascii des fils */
  unsigned int code; /* coding par entier (en binaire) ; on commence toujours par 1 - qui definit la taille de fait */
  arbre_t left;
  arbre_t right;
};


#define HAUTEUR_MAX 31

arbre_t new_arbre(float, int);
void free_arbre(arbre_t);
int est_feuille(arbre_t);
float get_freq(arbre_t);
int get_lettre(arbre_t);
unsigned int get_code(arbre_t);
void set_code(unsigned int, arbre_t);
void add_left_child(arbre_t, arbre_t);
void add_right_child(arbre_t, arbre_t);
arbre_t left_child(arbre_t);
arbre_t right_child(arbre_t);
void dot_arbre (arbre_t);

#endif /* ARBRE_H */
