#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Inicializa a tabela hash
thashtable * h_init(int table_s){
  thashtable * hash = malloc(sizeof(thashtable));
  hash->table_size = table_s;
  hash->table_p = (thead **) malloc(sizeof(thead) * table_s);
  return hash;
}
// Funcao hash: traduz o estado para uma chave
/* Importante: estado deve conter o lado do jogador atual na ultima posicao
  da string
*/
int h_genkey(char * state, int table_s){
  int key = 0;
  int field_size = ((int) strlen(state)) - 2;
  char lado = state[field_size + 1];
  for (int i = 0; i < field_size; i++){
    if (state[i] == 'f'){
      key = key + i;
    }
    else if (state[i] == 'o'){
      key = key + (2 * i);
    }
  }
  if (lado == 'e'){
    key = key *2;
  }
  if (key < table_s) return key;
  else return key % table_s;
}
// Insere estado na tabela hash
void h_insert(thashtable *hash, char * state){
  int key = h_genkey(state, hash->table_size);
  thead * list = h_getlist(hash, key);
  if (list== NULL){
    list = l_init();
    hash->table_p[key] = list;
  }
  l_insert(list, state); 
}
thead * h_getlist(thashtable *hash, int key){
  return hash->table_p[key];
}
// Verifica se estado esta na tabela hash
int h_findstate(thashtable * hash, char * state){
  int key = h_genkey(state, hash->table_size);
  thead * list = h_getlist(hash, key);
  if (list != NULL){
    return l_search(list, state);
  }
  else return 0;
}

// Limpa da memoria a tabela hash
void h_free(thashtable * hash){
  for (int i = 0; i < hash->table_size; i++){
    if (hash->table_p[i] != NULL){
      l_free(hash->table_p[i]);
    }
  }
  free(hash->table_p);
  free(hash);
}



int main(){
  int table_size = 20;
  printf("Testando init... \n");
  thashtable * hash = h_init(table_size);
  printf("Testando funcao hash... \n");
  printf("%d\n", h_genkey("f...fo...fe", table_size));
  printf("%d\n", h_genkey("f.fo.f...fe", table_size));
  printf("%d\n", h_genkey("f.f......fe", table_size));
  printf("%d\n", h_genkey("f...fo...fd", table_size));
  printf("%d\n", h_genkey("f.fo.f...fd", table_size));
  printf("%d\n", h_genkey("f.f......fd", table_size));

  printf("Testando insercao \n");
  h_insert(hash, "f.f.......fe");
  h_insert(hash, "f.f.o.....fe");
  h_insert(hash, "f.f...f...fd");
  h_insert(hash, "f.f.....f.fd");

  printf("Testando busca\n");
  printf("%d\n", h_findstate(hash, "f.f.......fe"));
  printf("%d\n", h_findstate(hash, "f.f.o.....fe"));
  printf("%d\n", h_findstate(hash, "f.f...f...fd"));
  printf("%d\n", h_findstate(hash, "f.f.....f.fd"));

  printf("%d\n", h_findstate(hash, "f.f...f...fe"));
  printf("%d\n", h_findstate(hash, "f.f.....f.fe"));
  printf("%d\n", h_findstate(hash, "f.f...o...fd"));
  printf("%d\n", h_findstate(hash, "f.f.....f.fe"));

  printf("Testando free\n");
  h_free(hash);
}
