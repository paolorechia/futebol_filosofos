#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "tabelahash.h"

tno * aloca_no(char * estado, thashtable * hash,
                   int lim, int prof,
                   tno * pai)
    if (h_insert(hash, estado)){
      return NULL;
    }
    tno * no;
    no = malloc(sizeof(tno));
    no->estado = malloc(sizeof(estado) * strlen(estado));
    no->profundidade = prof;
    no->limite = lim;
    no->pai = pai;
    no->filhos = NULL;
    return no;
}

tno * aloca_raiz(char * estado, thashtable * hash, int lim)
    return aloca_no(estado, hash, lim, 0, NULL);
}

tno * aloca_filho(tno * no_pai){
    if (no_pai->filhos == NULL){
      no_pai->filhos=tl_init();
    }
    int lim = no_pai->limite;
    int prof= no_pai->profundidade++;
    tno * filho = aloca_no(estado, hash, lim, prof, no_pai)
    if (filho != NULL){
      tl_insert(no->pai->filhos, filho);
    }
    return filho;
}

void desaloca_no(tno * no){
    free(no->estado);
    if (no->filhos != NULL){
      tl_free(no->filhos);
    }
    free(no);
}

void desaloca_arvore(tno * no){
    tno * filho = no->filhos->nxt;
    while (filho){
      desaloca_arvore(filho);
      filho = no->filhos->nxt;
    }
    desaloca_no(no);
}

int * devolve_acao_caminho(tno * no){
    tno * aux2 = no;
    tno * aux = no->pai;
    while(aux->pai){
        aux2 = aux;
        aux = aux->pai;
    }
    return aux2->acao;
}

/*************************************************/
/* Estrutura de dados auxiliar - lista encadeada */
/*************************************************/
//Funçao que inicializa a lista usada para achar a diferença e a interseccao.
 t_list * tl_init(){
    t_list * head = malloc(sizeof(t_list));
    head->node = malloc(sizeof(tnode));
    head->node->nxt = NULL;
    head->size = 0;
    head->node = NULL;
    return head;
}

//Funçao usada para inserir os chars (vizinhança) na lista daquele vertice.
 void tl_insert(t_list * head, tno * no){
    tnode * node = head->node;
    while (node->nxt != NULL){
        node = node -> nxt;
    }
    node->nxt=malloc(sizeof(tnode));
//    strcpy(node->nxt->key,new);
    node->nxt-> 
    node->nxt->nxt=NULL;
    head->size += 1;
    return;
}

//Funçao auxiliar para ajudar a debugar o programa.
 void tl_print(t_list * head){
    printf("--------->"); 
    if (head->node->nxt == NULL){
        printf("Empty l\n");
        return;
    }
    tnode * node = head->node->nxt;
    while (node){
        printf("%s ", node->key);
        node = node->nxt;
    }
    putchar('\n');
}

 int tl_size(t_list * head){
    return head->size;
}

/* Funcao recursiva para limpar lista a partir do ultimo no*/
 int rec_clear(tnode * node){
    if (node->nxt != NULL){
        rec_clear(node->nxt);
    }
//    printf("Freeing node of name: %s\n", node->key);
    node->nxt = NULL;
    free(node);
    return 0;
}

//Funçao para limpar a lista.
 int tl_clear(t_list * head){
    tnode * node = head->node;
    if (head->node->nxt == NULL){
        return 0;
    }
    rec_clear(head->node->nxt);
    head->node->nxt = NULL;
    head->size = 0;
    return 1;
}

// Desaloca memoria
 void tl_free(t_list *head){
    tl_clear(head);
    free(head->node);
    free(head);
}
// Busca sequencial de elemento na lista
 int tl_search(t_list* head, char * buscado){
    // if empty list
    if (head->node->nxt == NULL){
        return 0;
    }
    tnode * node = head->node->nxt;
    while (node){
        if (!strcmp(node->key, buscado)) return 1;
        node = node->nxt;
    }   
    return 0;
}
//Funcao que verifica a interseccao entre os dois vertives.
 t_list * tl_intersection(t_list *l1, t_list * l2){
    t_list * inter_l = tl_init();
    // if either list is empty, intersection is empty
    if (l1->node->nxt == NULL || l2->node->nxt == NULL){
        return inter_l;
    } 
    // fetch first element
    tnode * node = l1->node->nxt;
    while (node){
        if (tl_search(l2, node->key)){
            tl_insert(inter_l, node->key);
        }
        node = node->nxt;
    }
    return inter_l;
}

// cria uma copia da lista
 t_list * tl_copy(t_list *list)
{
    // No auxiliar
    t_list* new_list = tl_init();
    tnode * lnode = list->node->nxt;
    while (lnode)
    {
        tl_insert(new_list, lnode->key); // Insere chave na lista nova
        lnode = lnode->nxt;         // Proximo elemento da lista
    }
    return new_list; //Return de head of the copy.
}

/*************************************************/
/* Fim da estrutura de dados lista encadeada     */
/*************************************************/
