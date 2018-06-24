#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "campo.h"

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
void faz_gol(int * chutes, int num_chutes, char lado_jogador){
    char buf[MAXSTR];
    char num[MAXINT];
    sprintf(buf, "%c o %d ", lado_jogador, num_chutes);
    for (int i = 0; i < num_chutes; i++){
        sprintf(num, "%d ", chutes[i]);
        strcat(buf, num);
    }
    sprintf(num, "\n");
    strcat(buf, num);
    printf("%s", buf);
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
      printf("%s", buf);
      num_chutes--;
    }
}

void coloca_filosofo(char * campo, int tam_campo, char meu_lado){
    char buf[MAXSTR] = "";
    for (int i = 0; i < tam_campo; i++){
      if (campo[i] == '.'){
        sprintf(buf, "%c f %d\n", meu_lado, i);
        printf("%s", buf);
      }
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

void gera_acoes(char * campo, int tam_campo, char lado){
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
      printf("Jogo encerrado\n");
      return;
    }
    // testar se eh possivel chutar ao gol para algum lado
    gol_esq = testa_chutes_esq(campo, &chutes_esq, &num_chutes_esq, pos_bola2);
    gol_dir = testa_chutes_dir(campo, tam_campo, &chutes_dir, &num_chutes_dir, pos_bola2);
    if (gol_esq && lado == 'd') faz_gol(chutes_esq, num_chutes_esq, lado);
    else gera_chutes(chutes_esq, num_chutes_esq, lado);
    if (gol_dir && lado == 'e') faz_gol(chutes_dir, num_chutes_dir, lado);
    else gera_chutes(chutes_dir, num_chutes_dir, lado);
    coloca_filosofo(campo, tam_campo, lado);
    free(chutes_esq);
    free(chutes_dir);
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

  // conecta com o controlador do campo
  campo_conecta(argc, argv);

  srand(time(NULL));
  while(1){
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
    gera_acoes(campo, tam_campo, lado_meu);
    sprintf(buf, "%c n\n", lado_meu);
    printf("%s\n", buf);
    campo_envia(buf);  
  }
}
