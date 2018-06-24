#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "campo.h"
#include "hashtable.h"
#include "tree.h"

#define MAXSTR 512
#define MAXCHT MAXSTR/2
#define MAXINT 16

int testa_chutes_esq(char * campo, int ** chutes_esq,
                     int * num_chutes_esq, int pos_bola2){
    // testa lado esquerdo
    int gol_esq = 0;
    int j = pos_bola2 - 1;
    *num_chutes_esq = 0;
    if (campo[j] == 'f'){ // eh possivel um chute
      while (j > 0){
          if (campo[j] == '.'){
            (*chutes_esq)[*num_chutes_esq]=j + 1;
            *num_chutes_esq = *num_chutes_esq + 1;
            if (campo[j - 1] == '.'){
              break; // nao ha mais chutes possiveis
            }
          }
        j--;
      }
    }
    if (j == 0 && campo[0] == 'f'){
      (*chutes_esq)[*num_chutes_esq]=j;
      *num_chutes_esq = *num_chutes_esq + 1;
      gol_esq = 1;
    }
   return gol_esq;
}

int testa_chutes_dir(char * campo, int tam_campo,
                     int * chutes_dir[MAXCHT], 
                     int *num_chutes_dir, int pos_bola2){
    // testa lado direito
    int gol_dir = 0;
    int j = pos_bola2 + 1;
    *num_chutes_dir = 0;
    if (campo[j] == 'f'){ // eh possivel um chute
      while (j < tam_campo){
          if (campo[j] == '.'){
            (*chutes_dir)[*num_chutes_dir]= j + 1;
            *num_chutes_dir = *num_chutes_dir + 1;
            if (campo[j + 1] == '.'){
              break; // nao ha mais chutes possiveis
            }
          }
        j++;
      }
    }
    if (j == tam_campo && campo[tam_campo - 1] == 'f'){
      (*chutes_dir)[*num_chutes_dir]=j + 1;
      *num_chutes_dir = *num_chutes_dir + 1;
      gol_dir = 1;
    }
    return gol_dir;
}
void faz_gol(tno * state_tree, thashtable * hash,
             int * chutes, int num_chutes, char lado_jogador, 
             char * campo, int pos_bola2){
    char estado_novo[MAXSTR];
    strcpy(estado_novo, campo);
    int ultima_pos = chutes[num_chutes - 1];
    char lado_gol = 'n';
    if (pos_bola2 > ultima_pos){
      for (int i = pos_bola2; i > 0 ; i--){
        estado_novo[i] = '.'; 
        lado_gol = 'e';
      }
    }
    else{
      for (int i = pos_bola2; i < ultima_pos; i++){
        estado_novo[i] = '.';
        lado_gol = 'd';
      }
    }
    sprintf(estado_novo, "%s%c", estado_novo, lado_jogador);
    tno * novo_no = aloca_filho(state_tree, estado_novo, hash);
    if (novo_no != NULL){
      char buf[MAXSTR];
      char num[MAXINT];
      sprintf(buf, "%c o %d ", lado_jogador, num_chutes);
      for (int i = 0; i < num_chutes; i++){
          sprintf(num, "%d ", chutes[i]);
          strcat(buf, num);
      }
      sprintf(num, "\n");
      strcat(buf, num);
      sprintf(novo_no->acao, "%s", buf);
      novo_no->terminal = 1;
      novo_no->jogador = lado_jogador;
      novo_no->gol = lado_gol;
    }
}
void gera_chutes(int * chutes, int num_chutes, char lado_jogador){
    char buf[MAXSTR];
    char num[MAXINT];
    while (num_chutes > 0){
      sprintf(buf, "%c o %d ", lado_jogador, num_chutes);
      for (int i = 0; i < num_chutes; i++){
            // aplicar offset + 1 para os chutes
            sprintf(num, "%d ", chutes[i]);
            strcat(buf, num);
      }
      sprintf(num, "\n");
      strcat(buf, num);
//      printf("%s", buf);
      num_chutes--;
    }
}

int acha_bola(char * campo, int tam_campo){
    int pos_bola2 = -1;
    for (int i = 0; i < tam_campo; i++){
      if (campo[i] == 'o'){
         pos_bola2 = i;
      }
    }
    return pos_bola2;
}

void coloca_filosofo(tno * state_tree, thashtable * hash, 
                     char * campo, int tam_campo, char meu_lado){
    char estado_novo[MAXSTR];
    strcpy(estado_novo, campo);
    for (int i = 0; i <= tam_campo; i++){
      if (campo[i] == '.'){
        estado_novo[i] = 'f';
        sprintf(estado_novo, "%s%c", estado_novo, meu_lado);
        tno * novo_no = aloca_filho(state_tree, estado_novo, hash);
        if (novo_no != NULL){
          sprintf(novo_no->acao, "%c f %d\n", meu_lado, i + 1);
//          printf("%s\n", novo_no->estado);
        }
        strcpy(estado_novo, campo);
      }
    }
}

void gera_acoes(tno * state_tree, thashtable * hash, 
                char * campo, int tam_campo, char lado){
    int pos_bola2;
    int num_chutes_esq;
    int num_chutes_dir;
    int gol_esq;
    int gol_dir;
    int * chutes_esq = malloc(sizeof(int) * MAXCHT);
    int * chutes_dir = malloc(sizeof(int) * MAXCHT);
    // acha bola
    pos_bola2 = acha_bola(campo, tam_campo);
    if (pos_bola2 == -1){
//      printf("Jogo encerrado\n");
      return;
    }
    // testar se eh possivel chutar ao gol para algum lado
    gol_esq = testa_chutes_esq(campo, &chutes_esq, &num_chutes_esq, pos_bola2);
    gol_dir = testa_chutes_dir(campo, tam_campo, &chutes_dir, &num_chutes_dir, pos_bola2);
    if (gol_esq && lado == 'd') faz_gol(state_tree, hash, 
                                        chutes_esq, num_chutes_esq, lado,
                                        campo, pos_bola2);
    else gera_chutes(chutes_esq, num_chutes_esq, lado);
    if (gol_dir && lado == 'e') faz_gol(state_tree, hash, 
                                        chutes_dir, num_chutes_dir, lado,
                                        campo, pos_bola2);
    else gera_chutes(chutes_dir, num_chutes_dir, lado);
    coloca_filosofo(state_tree, hash, campo, tam_campo, lado);
    free(chutes_esq);
    free(chutes_dir);
}

int f_utilidade2(tno * atual, char jogador){
  // le campo e lado do estado
  char campo[MAXSTR];
  strcpy(campo, atual->estado);
  int tam_campo = strlen(campo);
  char lado = campo[tam_campo -1];
  campo[tam_campo - 1]='\0';
  tam_campo--;

  int multiplicador;
  if (jogador == lado)
    multiplicador = 1;
  else multiplicador = -1;

  // Jogo encerrado
  if (atual->terminal == 1){
    if (atual->gol == jogador)
      return -1000;
    else if (atual->gol == 'e' || atual->gol == 'd')
       return 1000;
  }

  int pos_bola2;
  int num_chutes_esq = 0;
  int num_chutes_dir = 0;
  int gol_esq;
  int gol_dir;
  int * chutes_esq = malloc(sizeof(int) * MAXCHT);
  int * chutes_dir = malloc(sizeof(int) * MAXCHT);
  int valor = 0;
  // acha bola
  pos_bola2 = acha_bola(campo, tam_campo);
  if (pos_bola2 == -1){
//    printf("Jogo encerrado\n");
    free(chutes_esq);
    free(chutes_dir);
    return valor;
  }
  // testar se eh possivel chutar ao gol para algum lado
  gol_esq = testa_chutes_esq(campo, &chutes_esq, &num_chutes_esq, pos_bola2);
  gol_dir = testa_chutes_dir(campo, tam_campo, &chutes_dir, &num_chutes_dir, pos_bola2);
  if (lado == 'd'){
    if (gol_esq) valor = tam_campo*10;
    if (gol_dir) valor = -tam_campo*10;
  }
  else{
    if (gol_esq) valor = -tam_campo*10;
    if (gol_dir) valor = tam_campo*10;
  }
  free(chutes_esq);
  free(chutes_dir);
  return multiplicador * valor;
}

int f_utilidade(tno * atual, char jogador){
  // le campo e lado do estado
  char campo[MAXSTR];
  strcpy(campo, atual->estado);
  int tam_campo = strlen(campo);
  char lado = campo[tam_campo -1];
  campo[tam_campo - 1]='\0';
  tam_campo--;

  int multiplicador;
  if (jogador == lado)
    multiplicador = 1;
  else multiplicador = -1;

  // Jogo encerrado
  if (atual->terminal == 1){
    if (atual->gol == jogador)
      return -1000;
    else if (atual->gol == 'e' || atual->gol == 'd')
       return 1000;
  }

  int pos_bola2;
  int num_chutes_esq = 0;
  int num_chutes_dir = 0;
  int gol_esq;
  int gol_dir;
  int * chutes_esq = malloc(sizeof(int) * MAXCHT);
  int * chutes_dir = malloc(sizeof(int) * MAXCHT);
  int valor = 0;
  // acha bola
  pos_bola2 = acha_bola(campo, tam_campo);
  if (pos_bola2 == -1){
//    printf("Jogo encerrado\n");
    free(chutes_esq);
    free(chutes_dir);
    return valor;
  }
  // testar se eh possivel chutar ao gol para algum lado
  gol_esq = testa_chutes_esq(campo, &chutes_esq, &num_chutes_esq, pos_bola2);
  gol_dir = testa_chutes_dir(campo, tam_campo, &chutes_dir, &num_chutes_dir, pos_bola2);
  if (lado == 'd'){
    if (gol_esq) valor = tam_campo*10;
    if (gol_dir) valor = -tam_campo*10;
  }
  else{
    if (gol_esq) valor = -tam_campo*10;
    if (gol_dir) valor = tam_campo*10;
  }
  free(chutes_esq);
  free(chutes_dir);
  return multiplicador * valor;
}


int valor_max(tno * state_tree, thashtable * hash, char jogador);
int valor_min(tno * state_tree, thashtable * hash, char jogador);

int valor_max(tno * state_tree, thashtable * hash, char jogador){
  if (state_tree->terminal || state_tree->filhos == NULL) return f_utilidade(state_tree, jogador);
  int max = -99999;
  l_node * no = state_tree->filhos->head->nxt;
  while (no){
      tno * atual = (tno *) no->no_atual;
      char campo[MAXSTR];
      strcpy(campo, atual->estado);
      int tam_campo = strlen(campo);
      campo[tam_campo - 1]='\0';
      if (atual->estado[tam_campo - 1] == 'd')
        gera_acoes(atual, hash, campo, tam_campo -2, 'e');
      else
        gera_acoes(atual, hash, campo, tam_campo -2, 'd');
      int v = valor_min(atual, hash, jogador);
      if (v > max) {
        max = v;
      }
      no = no->nxt;
  printf("%d %s %d\n (max)", atual->profundidade, atual->estado, f_utilidade(atual, jogador));
  }
  printf("%d %s %d\n (MAX)", state_tree->profundidade, state_tree->estado, f_utilidade(state_tree, jogador));
  return max;
}

int valor_min(tno * state_tree, thashtable * hash, char jogador){
  if (state_tree->terminal || state_tree->filhos == NULL) return f_utilidade(state_tree, jogador);
  l_node * no = state_tree->filhos->head->nxt;
  int min = 999999;
  while (no){
//    printf("%d %s %d\n", atual->profundidade, atual->estado, f_utilidade(atual->estado));
      tno * atual = (tno *) no->no_atual;
      char campo[MAXSTR];
      strcpy(campo, atual->estado);
      int tam_campo = strlen(campo);
      campo[tam_campo - 1]='\0';
      if (atual->estado[tam_campo - 1] == 'd')
        gera_acoes(atual, hash, campo, tam_campo -2, 'e');
      else
        gera_acoes(atual, hash, campo, tam_campo -2, 'd');
      int v = valor_max(atual, hash, jogador);
      if (v < min) {
        min = v;
      }
      no = no->nxt;
  printf("%d %s %d\n (min)", atual->profundidade, atual->estado, f_utilidade(atual, jogador));
  }
  printf("%d %s %d\n (MIN)", state_tree->profundidade, state_tree->estado, f_utilidade(state_tree, jogador));
  return min;
}

char * minimax2(tno * state_tree, thashtable * hash, char jogador){
  int max = -99999;
/*
  if (state_tree->filhos == NULL){
    return 0;
  }
*/
  l_node * no = state_tree->filhos->head->nxt;
  tno * maximo;
  while (no){
      tno * atual = (tno *) no->no_atual;
      char campo[MAXSTR];
      strcpy(campo, atual->estado);
      int tam_campo = strlen(campo);
      campo[tam_campo - 1]='\0';
      if (atual->estado[tam_campo - 1] == 'd')
        gera_acoes(atual, hash, campo, tam_campo -2, 'e');
      else
        gera_acoes(atual, hash, campo, tam_campo -2, 'd');
      int v = valor_min(atual, hash, jogador);
      if (v > max) {
        max = v;
        maximo = atual;
      }
      no = no->nxt;
      printf("(max)%d %s %d\n", atual->profundidade, atual->estado, f_utilidade(atual, jogador));
  }
  printf("(ESCOLHIDO)%d %s %d\n", maximo->profundidade, maximo->estado, f_utilidade(maximo, jogador));
  return maximo->acao;
}


// negamax
int minimax(tno * state_tree, thashtable * hash, char jogador){
/*
  if (state_tree->filhos == NULL){
    return;
  }
*/
  if (state_tree->profundidade >= state_tree->limite || state_tree->terminal == 1){
    printf("%s %d\n", state_tree->estado, f_utilidade(state_tree, jogador));
    return f_utilidade(state_tree, jogador);
  }
  else{
    int max = -99999;
    l_node * no = state_tree->filhos->head->nxt;
    while (no){
        tno * atual = (tno *) no->no_atual;
  //    printf("%d %s %d\n", atual->profundidade, atual->estado, f_utilidade(atual->estado));
        char campo[MAXSTR];
        strcpy(campo, atual->estado);
        int tam_campo = strlen(campo);
        campo[tam_campo - 1]='\0';
        if (atual->estado[tam_campo - 1] == 'd')
          gera_acoes(atual, hash, campo, tam_campo -2, 'e');
        else
          gera_acoes(atual, hash, campo, tam_campo -2, 'd');
        int v = minimax(atual, hash, jogador);
        if (v > max) max = v;
        no = no->nxt;
    }
    state_tree->util = max;
    return max;
  }
}

char * acao_max(tno * state_tree){
  if (state_tree->filhos == NULL){
    return state_tree->acao;
  }
  else{
    l_node * no = state_tree->filhos->head->nxt;
    while (no){
      tno * atual = (tno *) no->no_atual;
      if (atual->util < state_tree->util){
        return atual->acao;
      }
      no = no->nxt;
    }
  }
  return NULL;
}

int main(int argc, char **argv) {

  char buf[MAXSTR];
  char campo[MAXSTR]; 
  char lado_meu;
  char lado_adv;
  char mov_adv;
  int tam_campo;
  int pos_filo;
  int pos_bola[MAXINT];
  int num_saltos;
  int i;
  int limite_arvore = 5;
  

  // conecta com o controlador do campo
  campo_conecta(argc, argv);

//  while(1){
    // recebe o campo inicial e o movimento do adversario
    campo_recebe(buf);
    // separa os elementos do string recebido
    sscanf(strtok(buf, " \n"), "%c", &lado_meu);
    sscanf(strtok(NULL, " \n"), "%d", &tam_campo);
    sscanf(strtok(NULL, " \n"), "%s", campo);
    sscanf(strtok(NULL, " \n"), "%c", &lado_adv);
    sscanf(strtok(NULL, " \n"), "%c", &mov_adv);
    if(mov_adv != 'n') {
      if(mov_adv == 'f')
        sscanf(strtok(NULL, " \n"), "%d", &pos_filo);
      else {
        sscanf(strtok(NULL, " \n"), "%d", &num_saltos);
        for(i = 0; i < num_saltos; i++)
      sscanf(strtok(NULL, " \n"), "%d", &(pos_bola[i]));
      }
    }
    if (acha_bola(campo, tam_campo) == -1){
//      continue;
      return;
    }
    thashtable * hash = h_init(MAXSTR);
    char estado_atual[MAXSTR];
    strcpy(estado_atual, campo);
    sprintf(estado_atual, "%s%c", estado_atual, lado_meu);
    tno * state_tree = aloca_raiz(estado_atual, hash, limite_arvore);
    gera_acoes(state_tree, hash, campo, tam_campo, lado_meu);
//    minimax(state_tree, hash, lado_meu);
    char * acao = minimax2(state_tree, hash, lado_meu);
//    printf("%d\n", state_tree->util);
//    sprintf(buf, "%s", acao_max(state_tree));
    printf("%s", acao);
    campo_envia(acao);
    // Libera da memoria as estruturas auxiliares
    h_free(hash);
    desaloca_arvore(state_tree);
// }
}
