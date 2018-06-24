#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************************************************/
/* Estrutura de dados auxiliar - lista encadeada */
/*************************************************/
//Funçao que inicializa a lista usada para achar a diferença e a interseccao.
 thead * l_init(){
    thead * head = malloc(sizeof(thead));
    head->node = malloc(sizeof(tnode));
    head->node->nxt = NULL;
    head->size = 0;
    strcpy(head->node->key,"#HEAD#");
    return head;
}

//Funçao usada para inserir os chars (vizinhança) na lista daquele vertice.
 void l_insert(thead * head, char * new){
    tnode * node = head->node;
    while (node->nxt != NULL){
        node = node -> nxt;
    }
    node->nxt=malloc(sizeof(tnode));
    strcpy(node->nxt->key,new);
    node->nxt->nxt=NULL;
    head->size += 1;
    return;
}

//Funçao auxiliar para ajudar a debugar o programa.
 void l_print(thead * head){
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

 int l_size(thead * head){
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
 int l_clear(thead * head){
//    tnode * node = head->node;
    if (head->node->nxt == NULL){
        return 0;
    }
    rec_clear(head->node->nxt);
    head->node->nxt = NULL;
    head->size = 0;
    return 1;
}

// Desaloca memoria
 void l_free(thead *head){
    l_clear(head);
    free(head->node);
    free(head);
}
// Busca sequencial de elemento na lista
 int l_search(thead* head, char * buscado){
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
 thead * l_intersection(thead *l1, thead * l2){
    thead * inter_l = l_init();
    // if either list is empty, intersection is empty
    if (l1->node->nxt == NULL || l2->node->nxt == NULL){
        return inter_l;
    } 
    // fetch first element
    tnode * node = l1->node->nxt;
    while (node){
        if (l_search(l2, node->key)){
            l_insert(inter_l, node->key);
        }
        node = node->nxt;
    }
    return inter_l;
}

// cria uma copia da lista
 thead * l_copy(thead *list)
{
    // No auxiliar
    thead* new_list = l_init();
    tnode * lnode = list->node->nxt;
    while (lnode)
    {
        l_insert(new_list, lnode->key); // Insere chave na lista nova
        lnode = lnode->nxt;         // Proximo elemento da lista
    }
    return new_list; //Return de head of the copy.
}

/*************************************************/
/* Fim da estrutura de dados lista encadeada     */
/*************************************************/
