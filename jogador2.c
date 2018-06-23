#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "campo.h"

#define MAXSTR 512
#define MAXCHT MAXSTR/2
#define MAXINT 16

int testa_chutes_esq(char ** resultado){
    // testa lado esquerdo
    int gol_esq;
    j = pos_bola2 - 1;
    num_chutes_esq = 0;
    if (campo[j] == 'f'){ // eh possivel um chute
      while (j > 0){
          if (campo[j] == '.'){
            chutes_esq[num_chutes_esq]=j + 1;
            num_chutes_esq++;
            if (campo[j - 1] == '.'){
              break; // nao ha mais chutes possiveis
            }
          }
        j--;
      }
    }
    if (j == 0 && campo[0] == 'f'){
      chutes_esq[num_chutes_esq]=j;
      num_chutes_esq++;
      gol_esq = 1;
    }
  return gol_esq;
}

char * testa_chutes_dir(char ** resultado){
    // testa lado direito
//    chutes_dir[i] = 0; 
    j = pos_bola2 + 1;
    num_chutes_dir = 0;
    if (campo[j] == 'f'){ // eh possivel um chute
      while (j < tam_campo){
          if (campo[j] == '.'){
            chutes_dir[num_chutes_dir]= j + 1;
            num_chutes_dir++;
            if (campo[j + 1] == '.'){
              break; // nao ha mais chutes possiveis
            }
          }
        j++;
      }
    }
    if (j == tam_campo && campo[tam_campo - 1] == 'f'){
      chutes_dir[num_chutes_dir]=j + 1;
      num_chutes_dir++;
      gol_dir = 1;
    }
}
int conta_chutes(chutes){


}
void faz_gol(chutes, lado_meu){
    char buf[MAXSTR];
    int num_chutes = conta_chutes(chutes);
    sprintf(buf, "%c o %d ", lado_meu, num_chutes);
    for (i = 0; i < num_chutes; i++){
        sprintf(num, "%d ", chutes[i]);
        strcat(buf, num);
    }
    sprintf(num, "\n");
    strcat(buf, num);
    printf("%s\n", buf);
}
void gera_chutes(chutes){
    char buf[MAXSTR];
    num_chutes = conta_chutes(chutes); 
    if (num_chutes > 0){
      sprintf(buf, "");
      for (i = 0; i < num_chutes; i++){
            // aplicar offset + 1 para os chutes
            sprintf(num, "%d ", chutes[i]);
            strcat(buf, num);
      }
      printf("%s\n", buf);
    }
}

void coloca_filosofo(campo, tam_campo, meu_lado){
    char buf[MAXSTR];
    for (int i = 0; i < tam_campo){
      if (campo[i] == '.'){
        sprintf(buf, "%c f %d\n", lado_meu, i);
      }
    }
    printf("%s\n", buf);
}
int acha_bola(campo, tam_campo){
    int pos_bola2 = -1;
    for (i = 0; i < tam_campo; i++){
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
    int i, j;
    int espaco_vazio;
    char chutes_esq[MAXCHT];
    char chutes_dir[MAXCHT];
    // acha bola
    pos_bola = acha_bola(campo, tam_campo);
    if (pos_bola2 == -1){
      printf("Jogo encerrado\n");
      return;
    }
    // testar se eh possivel chutar ao gol para algum lado
    gol_esq = testa_chutes_esq(chutes_esq);
    gol_dir = testa_chutes_dir(chutes_dir);
    if (gol_esq) faz_gol(chutes_esq);
    else gera_chutes(chutes_esq);
    if (gol_dir) faz_gol(chutes_dir);
    else gera_chutes(chutes_dir);

    if (lado_meu == 'e' && gol_dir == 1){
    // chutar_gol_dir
    }
    else if (lado_meu == 'd' && gol_esq == 1){
    // nao eh possivel fazer gol, inserir filosofos
    else{
      coloca_filosofo(campo, tam_campo, pos_bola2, meu_lado);
    }
  }
}
int main(int argc, char **argv) {

  char buf[MAXSTR];
  char campo[MAXSTR]; 
  char lado_meu;
  char lado_adv;
  char mov_adv;
  char num[MAXINT];
  int tam_campo;
  int pos_filo;
  int pos_bola[MAXINT];
  int num_saltos;
  int i;
  int j;

  // conecta com o controlador do campo
  campo_conecta(argc, argv);

  srand(time(NULL));
  while(1){
    gol_esq = 0;
    gol_dir = 0;
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
    strcpy(buf, "n\n");
    campo_envia(buf);  
  }
}
