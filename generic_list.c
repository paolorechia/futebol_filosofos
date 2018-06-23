#include "generic_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************************************************/
/* Lista encadeada generica                      */
/*************************************************/
//Funçao que inicializa a lista usada para achar a diferença e a interseccao.
 tgenhead * genl_init(){
    tgenhead * head = malloc(sizeof(tgenhead));
    head->node = malloc(sizeof(tnode));
    head->node->nxt = NULL;
    head->size = 0;
    head->node->key = NULL;
    return head;
}

//Funçao usada para inserir os chars (vizinhança) na lista daquele vertice.
 void genl_insert(tgenhead * head, void * data){
    tnode * node = head->node;
    while (node->nxt != NULL){
        node = node -> nxt;
    }
    node->nxt=malloc(sizeof(tnode));
    node->next->key = data;
    node->nxt->nxt=NULL;
    head->size += 1;
    return;
}

//Funçao auxiliar para ajudar a debugar o programa.
int genl_size(tgenhead * head){
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
 int genl_clear(tgenhead * head){
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
void genl_free(tgenhead *head){
    genl_clear(head);
    free(head->node);
    free(head);
}
// Busca sequencial de elemento na lista
 int genl_search(tgenhead* head, void * data){
    // if empty list
    if (head->node->nxt == NULL){
        return 0;
    }
    tnode * node = head->node->nxt;
    while (node){
        if (node->key== data) return 1;
        node = node->nxt;
    }   
    return 0;
}
// cria uma copia da lista
 tgenhead * genl_copy(tgenhead *list)
{
    // No auxiliar
    tgenhead* new_list = genl_init();
    tnode * lnode = list->node->nxt;
    while (lnode)
    {
        genl_insert(new_list, lnode->key); // Insere chave na lista nova
        lnode = lnode->nxt;         // Proximo elemento da lista
    }
    return new_list; //Return de head of the copy.
}

/*************************************************/
/* Fim da estrutura de dados lista encadeada     */
/*************************************************/

int main(){
  tgenhead * list = genl_init();  
  genl_insert(list, 2;

  return 0;
}
