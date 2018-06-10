#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "campo.h"

#define MAXSTR 512
#define MAXCHT MAXSTR/2
#define MAXINT 16

int main(int argc, char **argv) {
  char buf[MAXSTR];
  char campo[MAXSTR]; 
  char lado_meu;
  char lado_adv;
  char mov_adv;
  char num[MAXINT];
  int chutes_esq[MAXCHT];
  int chutes_dir[MAXCHT];
  int tam_campo;
  int pos_filo;
  int pos_bola[MAXINT];
  int pos_bola2;
  int num_saltos;
  int i;
  int j;
  int num_chutes_esq;
  int num_chutes_dir;
  int gol_esq;
  int gol_dir;
  int rand_pos;
  int espaco_vazio;

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

    // mostra o que recebeu
    printf("%c %d %s\n", lado_meu, tam_campo, campo);
    printf("%c %c", lado_adv, mov_adv);
    if(mov_adv != 'n') {
      if(mov_adv == 'f')
        printf(" %d", pos_filo);
      else {
        printf(" %d", num_saltos);
        for(i = 0; i < num_saltos; i++)
      printf(" %d", pos_bola[i]);
      }
    }
    printf("\n");

    for (i = 0; i < tam_campo; i++){
      printf("%c ", campo[i]);
      if (campo[i] == 'o'){
         pos_bola2 = i;
      }
    }
    printf("\n");
//    printf("Bola na pos: %d\n", pos_bola2 + 1);
    // testar se eh possivel chutar ao gol
    // se sim, chutar

    for (i = 0; i < MAXCHT; i++){
      chutes_esq[i] = 0; 
      chutes_dir[i] = 0; 
    }
    // testa lado esquerdo
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
//      printf("Eh possivel fazer gol no lado esquerdo! (chutar para %d)\n", j);
    }
    // testa lado direito
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
//    printf("%d\n", j);
//    printf("%d\n", tam_campo);
//    printf("%c\n", campo[tam_campo - 1]);
    if (j == tam_campo && campo[tam_campo - 1] == 'f'){
  //    printf("Eh possivel fazer gol no lado direito! (chutar para %d)\n", j+1);
      chutes_dir[num_chutes_dir]=j + 1;
      num_chutes_dir++;
      gol_dir = 1;
    }

    if (num_chutes_esq > 0){
      sprintf(buf, "");
      for (i = 0; i < num_chutes_esq; i++){
            // aplicar offset + 1 para os chutes
            sprintf(num, "%d ", chutes_esq[i]);
            strcat(buf, num);
      }
 //     printf("Eh possivel os seguintes chutes para a esquerda: %s\n", buf);
    }

    if (num_chutes_dir > 0){
      sprintf(buf, "");
      for (i = 0; i < num_chutes_dir; i++){
            // aplicar offset + 1 para os chutes
            sprintf(num, "%d ", chutes_dir[i]);
            strcat(buf, num);
      }
//      printf("Eh possivel os seguintes chutes para a direita: %s\n", buf);
    }

    if (lado_meu == 'e' && gol_dir == 1){
//      chutar_gol_dir
      sprintf(buf, "%c o %d ", lado_meu, num_chutes_dir);
      for (i = 0; i < num_chutes_dir; i++){
          sprintf(num, "%d ", chutes_dir[i]);
          strcat(buf, num);
 //         printf("Buf: %s\n", buf);
        }
//      printf("Chute teste: %s\n", buf);
    }
    else if (lado_meu == 'd' && gol_esq == 1){
//      chutar_gol_esq
      sprintf(buf, "%c o %d ", lado_meu, num_chutes_esq);
      for (i = 0; i < num_chutes_esq; i++){
          sprintf(num, "%d ", chutes_esq[i]);
          strcat(buf, num);
  //        printf("Buf: %s\n", buf);
        }
//      printf("Chute teste: %s\n", buf);
    }
  // nao eh possivel fazer gol, inserir filosofo aleatorio
    else{
      // verifica se ha espaco vazio em campo para filosofo
      espaco_vazio = -1;
      for (i = 0; i < tam_campo; i++){
        if (campo[i] == '.') espaco_vazio = i;
      } 
      // se nao ha espaco, enviar mensagem de fazer nada
      if (espaco_vazio == -1){
        sprintf(buf, "%c n\n", lado_meu);
      }
      // se ha espaco
      // prepara um string com o movimento
      // de inserir um filosofo em posicao aleatoria do campo
      else{
        rand_pos = (rand() % tam_campo);
        while (campo[rand_pos] != '.'){
          rand_pos = (rand() % tam_campo);
        }
        sprintf(buf, "%c f %d\n", lado_meu, rand_pos + 1);
      }
    }
    // envia o movimento para o controlador do campo
    printf("Msg enviada: %s\n", buf);
    campo_envia(buf);  
  }
}
