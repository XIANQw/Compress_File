#include <stdio.h> /* pour dot_arbre only */
#include <stdlib.h> /* malloc, free */
#include <ctype.h> /* isalnum & co */
#include "arbre.h" /* arbre_t + macro */
#define ARBREVIDE -1



/*
 * CONSTRUCTEUR
 * retourne un pointeur sur un arbre (malloc) , initialisé avec le couple (freq,c)
 */
arbre_t new_arbre(float freq, int c){
  arbre_t tmp;
  tmp = malloc(sizeof(struct noeud_m));
  tmp -> left = NULL;
  tmp -> right = NULL;
  tmp -> freq = freq;
  tmp -> lettre = c;
  return tmp;
}

/*
 * DESTRUCTEUR
 * libere la memoire associé à l'arbre T
 */
void free_arbre(arbre_t T){
  if(T==NULL) return ;
  free_arbre(left_child(T));
  free_arbre(right_child(T));
  free(T);
}

/* retourne vrai si T est une feuille, faux sinon */
int est_feuille(arbre_t T){
  if(T==NULL) exit(ARBREVIDE);
  return (left_child(T)==NULL)&&(right_child(T)==NULL);
}

float get_freq(arbre_t T){
  return T->freq;
}

int get_lettre(arbre_t T){
  return T->lettre;
}

unsigned int get_code(arbre_t T){
  return T->code;
}

void set_code(unsigned int c,arbre_t T){
  T->code=c;
}

void add_left_child(arbre_t a,arbre_t g){
  a->left=g;
}

void add_right_child(arbre_t a,arbre_t d){
  a->right=d;
}

arbre_t left_child(arbre_t a){
  return a?a->left:NULL;
}

arbre_t right_child(arbre_t a){
  return a?a->right:NULL;
}

/*
 * Affichage pour dot. Adaptation d'un code écrit par Francois Boulier
 * dot -Tpdf a.dot -o a.pdf
 * ./code
 * aaabbab
 * digraph G {
 *     label_7eb070 [label="7"];
 *     label_62 [label="b:3"];
 *     label_7eb070 -> label_62 [label="0"];
 *     label_61 [label="a:4"];
 *     label_7eb070 -> label_61 [label="1"];
 *     label_62 [shape=box];
 *     label_61 [shape=box];
 * }
 */

static void dot2_noeud_arbre(char *label,char *label_decl,arbre_t G){
  if (est_feuille(G)){
    if (G->lettre==256)
      sprintf(label_decl,"label_%02x [label=\"EOF:%.2f\"]",(unsigned)G->lettre,G->freq);
    else if (G->lettre=='\n')
      sprintf(label_decl,"label_%02x [label=\"\'\\\\n\':%.2f\"]",(unsigned)G->lettre,G->freq);
    else if (G->lettre=='\t')
      sprintf(label_decl,"label_%02x [label=\"\'\\\\t\':%.2f\"]",(unsigned)G->lettre,G->freq);
    else if (G->lettre==' ')
      sprintf(label_decl,"label_%02x [label=\"SPACE:%.2f\"]",(unsigned)G->lettre,G->freq);
    else if ( (G->lettre > 40) && (G->lettre <177)) /* caractère imprimable */
      sprintf(label_decl,"label_%02x [label=\"%c:%.2f\"]",(unsigned)G->lettre,(char)G->lettre,G->freq);
    else /* caractère non imprimable -> on affiche son code ascii en hexadécimal */
      sprintf(label_decl,"label_%02x [label=\"0x%02x:%.2f\"]",(unsigned)G->lettre,(unsigned)G->lettre,G->freq);
    sprintf(label,"label_%02x",(unsigned)G->lettre);
  }
  else{
    sprintf(label_decl,"label_%lx [label=\"%.2f\"]",(unsigned long)G,G->freq);
    sprintf(label, "label_%lx", (unsigned long)G);
  }
}

static void dot3_arbre (arbre_t G){
  static char label_pere [64], label_fils [64], label_decl [128];
  dot2_noeud_arbre (label_pere, label_decl, G);
  if (! est_feuille (G)){
    dot2_noeud_arbre (label_fils, label_decl, G->left);
    printf ("    %s;\n", label_decl);
    printf ("    %s -> %s [label=\"0\"];\n", label_pere, label_fils);
    dot2_noeud_arbre (label_fils, label_decl, G->right);
    printf ("    %s;\n", label_decl);
    printf ("    %s -> %s [label=\"1\"];\n", label_pere, label_fils);
    dot3_arbre (G->left);
    dot3_arbre (G->right);
  }
  else
    printf ("    %s [shape=box];\n", label_pere);
}

static void dot2_arbre (arbre_t G){
  static char label_pere [64], label_decl [128];
  dot2_noeud_arbre (label_pere, label_decl, G);
  printf ("    %s;\n", label_decl);
  dot3_arbre (G);
}

void dot_arbre (arbre_t G){
  printf ("digraph G {\n");
  dot2_arbre (G);
  printf ("}\n");
}
