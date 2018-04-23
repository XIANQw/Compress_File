#include "coding.h"
#include "foret.h"
#include <stdio.h>
#include <stdlib.h> /* exit */
static void tablecodage_recursif(arbre_t, code_t);


arbre_t construirecodage(freq_t tab){
  foret_t f = new_foret();
  arbre_t combine = new_arbre(0,0);
  int c;
  for(c=0; c<MAXSIZE;c++){
    if(tab[c]!=0) insert_arbre_foret_sorted(&f,new_arbre(tab[c],c));
  }
  while((combine->freq < 1)&&(f->next!=NULL)){

    combine = combineArbre(pop_arbre_foret(&f),pop_arbre_foret(&f));
    insert_arbre_foret_sorted(&f,combine);
  }
  return f->arbre;
}

/*
 * Combiner 2 arbres
 */
arbre_t combineArbre(arbre_t a, arbre_t b){
  arbre_t res ;
  float freq;
  int lettre;
  if(!a||!b) return a?a:b;
  freq = a->freq + b->freq;
  lettre = (a->lettre > b->lettre)?a->lettre:b->lettre;
  res = new_arbre(freq,lettre);
  res -> left = a ; res -> right = b ;
  return  res ;
}
/*
 * construit un tableau contenant le code de chaque caractere
 */
void tablecodage(arbre_t T, code_t c){
  int i;
  for(i=0;c[i];i++) c[i]=0;
  set_code(1,T);
  tablecodage_recursif(T,c);
  }

static void tablecodage_recursif(arbre_t T, code_t c){
  if(est_feuille(T)){
    c[get_lettre(T)] = get_code(T);
    return;
  }
  set_code(get_code(T)<<1,left_child(T));
  tablecodage_recursif(left_child(T),c);
  set_code(get_code(T)<<1|1,right_child(T));
  tablecodage_recursif(right_child(T),c);
}

/* calculer la longueur du code de caractere*/
int len_code(int a){
  int degree=0;
  while(a!=0){
    a=a/2;
    degree++;
  }
  return degree;
}

void text_compression(FILE *f, code_t tab){
  int out_char,i,bit_position,nb_bits,index,nb_byte;
  while((i = fgetc(f))!=EOF){
    nb_bits = len_code(tab[i]);
    index = 1;
    nb_byte = 0;
    while(nb_byte<((nb_bits-1)/8+1)){
      for(bit_position=7,out_char=0;(bit_position>-1)&&(index<=nb_bits);index++,bit_position--)
        out_char |= ((tab[i]>>(nb_bits-index))&1) << bit_position;
      nb_byte++;
      putchar(out_char);
    }
  }
}
