#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "tree.h"
#include "hashtable.h"

/* Arvore */
tno * aloca_no(char * estado, thashtable * hash,
                   int lim, int prof,
                   tno * pai){
    if (h_insert(hash, estado)){
      return NULL;
    }
    tno * no;
    no = malloc(sizeof(tno));
    no->estado = malloc(sizeof(estado) * strlen(estado));
    strcpy(no->estado, estado);
    no->profundidade = prof;
    no->limite = lim;
    no->pai = pai;
    no->filhos = NULL;
    return no;
}

tno * aloca_raiz(char * estado, thashtable * hash, int lim){
    return aloca_no(estado, hash, lim, 0, NULL);
}

tno * aloca_filho(tno * no_pai, char * estado, thashtable * hash){
    if (no_pai->filhos == NULL){
      no_pai->filhos=tl_init();
    }
    int lim = no_pai->limite;
    int prof= no_pai->profundidade + 1;
    tno * filho = aloca_no(estado, hash, lim, prof, no_pai);
    if (filho != NULL){
      tl_insert(no_pai->filhos, filho);
    }
    return filho;
}

void desaloca_no(tno * no){
    tl_free(no->filhos);
    free(no);
}

void desaloca_arvore(tno * no){
    if (no == NULL){
      return;
    }
    if (no->filhos == NULL){
      desaloca_no(no);
      return;
    }
    l_node * filho = no->filhos->head->nxt;
    while (filho){
      desaloca_arvore(filho->no_atual);
      filho = filho->nxt;
    }
    desaloca_no(no);
}

char * devolve_acao_caminho(tno * no){
    tno * aux2 = no;
    tno * aux = no->pai;
    while(aux->pai){
        aux2 = aux;
        aux = aux->pai;
    }
    return aux2->acao;
}

/* Lista Encadeada */
 t_list * tl_init(){
    t_list * list = malloc(sizeof(t_list));
    list->head = malloc(sizeof(l_node));
    list->head->nxt = NULL;
    list->size = 0;
    return list;
}

// Insere novo no na lista
 void tl_insert(t_list * list, tno * no){
    l_node * node = list->head;
    while (node->nxt != NULL){
        node = node->nxt;
    }
    node->nxt=malloc(sizeof(l_node));
    node->nxt->no_atual = (void *) no;
    node->nxt->nxt=NULL;
    list->size += 1;
    return;
}

int tl_size(t_list * head){
    return head->size;
}

/* Funcao recursiva para limpar lista a partir do ultimo no*/
 int tl_rec_clear(l_node * node){
    if (node->nxt != NULL){
        tl_rec_clear(node->nxt);
    }
//    printf("Freeing node of name: %s\n", node->key);
    node->nxt = NULL;
    free(node);
    return 0;
}

//Funçao para limpar a lista.
 int tl_clear(t_list * list){
    l_node * node = list->head;
    if (node->nxt == NULL){
        return 0;
    }
    tl_rec_clear(node->nxt);
    list->head->nxt = NULL;
    list->size = 0;
    return 1;
}

// Desaloca memoria
 void tl_free(t_list * list){
    if (list == NULL){
      return;
    }
    tl_clear(list);
    free(list->head);
    free(list);
}
