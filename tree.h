#ifndef __TREE_H__
#define __TREE_H__ 

// Define uma lista de nos
typedef struct list_cell{
    void * no_atual;
    struct list_cell * nxt;
} node;

typedef struct node_list{
  node * head; 
  int size;
} t_list;

// Define um no externo, com um no interno e uma lista de nos (filhos)
typedef struct no{
  char * estado;
  char acao[20];
  int util; 
  int profundidade;
  int limite;
  t_list * filhos;
  struct no * pai;
} tno;


tno * aloca_raiz(char * estado, thashtable * hash, int lim);
tno * aloca_filho(tno * no_pai);
void aloca_k_filhos(tno * no_atual, int k);
void expande_no(tno * no);
void desaloca_no(tno * no);
void desaloca_arvore(tno * no);
int * devolve_solucao(tno * no);

/*************************************************/
/* Lista encadeada de nos */
/*************************************************/
//Funçao que inicializa a lista usada para achar a diferença e a interseccao.
static t_list* tl_init();
//Funçao usada para inserir os chars (vizinhança) na lista daquele vertice.
static void tl_insert(t_list * list, tno * no);
//Funçao auxiliar para ajudar a debugar o programa.
static void tl_print(t_list * list);
static int tl_size(t_list * list);
/* Funcao recursiva para limpar lista a partir do ultimo no*/
static int rec_clear(node * no);
//Funçao para limpar a lista.
static int tl_clear(t_list * list);
// Desaloca memoria
static void tl_free(t_list *list);
// Busca sequencial de elemento na lista
static int tl_search(t_list* list, tno * no);

#endif
