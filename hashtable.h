#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include "list.h"



typedef struct hash_struct{
  int table_size;
  thead ** table_p;
} thashtable;


// Inicializa a tabela hash
thashtable * h_init(int table_s);
// Funcao hash: traduz o estado para uma chave
int h_genkey(char * state, int table_s);
// Insere estado na tabela hash
int h_insert(thashtable * hash, char * state);
// Retorna a lista encadeada onde o estado pode estar
thead * h_getlist(thashtable * hash, int key);
// Verifica se estado esta na tabela hash
int h_findstate(thashtable * hash, char * state);
// Limpa da memoria a tabela hash
void h_free(thashtable * hash);

#endif
