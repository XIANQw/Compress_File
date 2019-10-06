#include "../include/foret.h"
#include "../include/arbre.h"
#include <stdlib.h>
#include <stdio.h>


/*
 * CONSTRUCTEUR
 * Rien à faire ici : la gestion de la mémoire se passera dans
 * la fonction insertion_arbre_foret_triee.
 * Ce n'est néanmois pas une mauvaise habitude de l'écrire / l'utiliser.
 */
foret_t new_foret(){
  return (foret_t)NULL;
}


/*
 * DESTRUCTEUR
 * libere la memoire associé à la foret F (n'oubliez pas d'appeler le destructeur associé aux arbres !)
 */
void free_foret(foret_t F){
  foret_t temp;
  while(F != NULL){
    temp = F;
    F=F->next;
    free_arbre(temp->arbre);
    free(temp);
  }
  return ;
}

/*
 * Retourne le premier arbre de la foret
 * Penser à libérer la mémoire associée au maillon de la liste chainée !
 */
arbre_t pop_arbre_foret(foret_t *F){
  arbre_t temp;
  if ((*F)==NULL) return NULL ;
  temp = (*F)->arbre;
  (*F)->arbre = NULL ;
  *F = (*F)->next;
  return temp;
}



int cmp_freq_lettre(arbre_t a, arbre_t b){
  if(a==NULL||b==NULL) return -2;
  if(a->freq > b->freq) return 1;
  if (a->freq < b->freq) return -1;
  return 0;
}


/*
 * Ajoute un arbre dans la foret
 * L'ajout est fait pour avoir une foret triee par frequences croissantes
 * Si vous souhaitez avoir un comportement non aléatoire de votre algorithme
 * (cela peut être utile pour comparer vos résultats), vous pouvez également
 * trier en fonction de la valeur de la lettre - dans le cas où la fréquence
 * est la même. Le cas échéant, vous pouvez écrire une fonction de comparaison
 * pour rendre le code plus lisible. Son prototype pourrait être
 * static int cmp_freq_lettre(arbre_t, arbre_t);
 */

/* version recursif
void insert_arbre_foret_sorted(foret_t *F, arbre_t T){
  foret_t res ;
  if(!(*F)){
    res = malloc(sizeof(struct foret_s));
    res->arbre=T;
    (*F)=res;
    (*F)->next = NULL;
    return ;
  }
  switch(cmp_freq_lettre(T, (*F)->arbre)) {
    case 0 :
	  case 1 :{
      insert_arbre_foret_sorted( &((*F)->next),T);
      return ;
    }
 	  case -1 :{
    	res = malloc(sizeof(struct foret_s));
    	res->arbre=T;
      res->next = *F ;
	 	  *F = res ;
      return ;
		}
    default : {
      fprintf(stderr,"problem\n") ; exit(2) ;
    }
  }
  fprintf(stderr,"This should never happen \n");
  return ;
}
*/
void insert_arbre_foret_sorted(foret_t *F, arbre_t T){
  foret_t res ;
  res = malloc(sizeof(struct foret_s));
  res->arbre=T;
  while((*F)!=NULL){
    if(cmp_freq_lettre(T,(*F)->arbre)>=0)
      F = &((*F)->next);
    else break;
  }
  if (*F==NULL){
    *F = res;
    (*F)->next = NULL;
    return ;
  }
  res->next = *F;
  *F = res;
}
