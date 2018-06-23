#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "tabelahash.h"

/* Arvore */
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

/* Lista Encadeada */
 t_list * tl_init(){
    t_list * head = malloc(sizeof(t_list));
    head->node = malloc(sizeof(tnode));
    head->node->nxt = NULL;
    head->size = 0;
    head->node = NULL;
    return head;
}

// Insere novo no na lista
 void tl_insert(t_list * head, tno * no){
    tnode * node = head->node;
    while (node->nxt != NULL){
        node = node -> nxt;
    }
    node->nxt=malloc(sizeof(tnode));
    node->no_atual = no;
    node->nxt-> 
    node->nxt->nxt=NULL;
    head->size += 1;
    return;
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
