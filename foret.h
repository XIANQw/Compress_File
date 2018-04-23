#ifndef FORET_H
#define FORET_H

#include "arbre.h"

typedef struct foret_s * foret_t;
struct foret_s {
  arbre_t arbre;
  foret_t next;
};

foret_t new_foret(void);
void free_foret(foret_t);
arbre_t pop_arbre_foret(foret_t *);
void insert_arbre_foret_sorted(foret_t *,arbre_t);
void print_foret(foret_t);
int cmp_freq_lettre(arbre_t, arbre_t);
#endif /* FORET_H */
