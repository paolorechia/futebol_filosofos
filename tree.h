#ifndef __TREE_H__
#define __TREE_H__ 

#include "hashtable.h"

#define MAXSTR 512

// Define uma lista de nos
typedef struct list_cell{
    void * no_atual;
    struct list_cell * nxt;
} l_node;

typedef struct node_list{
  l_node * head; 
  int size;
} t_list;

typedef struct no{
  char * estado;
  char acao[MAXSTR];
  int util; 
  int profundidade;
  int limite;
  t_list * filhos;
  struct no * pai;
} tno;


tno * aloca_raiz(char * estado, thashtable * hash, int lim);
tno * aloca_filho(tno * no_pai, char * estado, thashtable * hash);
void aloca_k_filhos(tno * no_atual, int k);
void expande_no(tno * no);
void desaloca_no(tno * no);
void desaloca_arvore(tno * no);
int * devolve_solucao(tno * no);

/*************************************************/
/* Lista encadeada de nos */
/*************************************************/
//Funçao que inicializa a lista usada para achar a diferença e a interseccao.
t_list* tl_init();
//Funçao usada para inserir os chars (vizinhança) na lista daquele vertice.
void tl_insert(t_list * list, tno * no);
//Funçao auxiliar para ajudar a debugar o programa.
int tl_size(t_list * list);
/* Funcao recursiva para limpar lista a partir do ultimo no*/
int tl_rec_clear(l_node * no);
//Funçao para limpar a lista.
int tl_clear(t_list * list);
//Desaloca memoria
void tl_free(t_list *list);
// Busca sequencial de elemento na lista

#endif
