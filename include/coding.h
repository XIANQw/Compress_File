#ifndef CODING_H
#define CODING_H

#include "freq.h" /* freq_t */
#include "arbre.h" /* arbre_t */

typedef unsigned int code_t[257];
arbre_t combineArbre(arbre_t , arbre_t);
arbre_t construirecodage(freq_t);
void tablecodage(arbre_t, code_t);
void text_compression(FILE *, code_t);

#endif /* CODING_H */
