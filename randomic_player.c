#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "campo.h"

#define MAXSTR 512
#define MAXINT 16

int main(int argc, char **argv) {
  char buf[MAXSTR];
  char campo[MAXSTR]; 
  char lado_meu;
  char lado_adv;
  char mov_adv;
  int tam_campo;
  int pos_filo;
  int pos_bola[MAXINT];
  int pos_bola2;
  int num_saltos;
  int i;
  int j;
  int num_chutes_pos;
  int rand_pos;

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

    printf("%s\n", campo);
    for (i = 0; i < tam_campo; i++){
      if (campo[i] == 'o'){
         pos_bola2 = i;
      }
    }
    printf("Bola na pos: %d\n", pos_bola2);
    // testar se eh possivel chutar ao gol
    // se sim, chutar

    // testa lado esquerdo
    j = pos_bola2 - 1;
    num_chutes_pos = 0;
    if (campo[j] == 'f'){ // eh possivel um chute
      while (j > 0){
          if (campo[j] == '.'){
            printf("Possivel chutar para: %d\n", j);
            num_chutes_pos++;
            if (campo[j - 1] == '.'){
              break; // nao ha mais chutes possiveis
            }
          }
        j--;
      }
    }
    if (j == 0){
      printf("Eh possivel fazer gol! (chutar para %d)\n", j);
    }

    j = pos_bola2 + 1;
    num_chutes_pos = 0;
    if (campo[j] == 'f'){ // eh possivel um chute
      while (j < tam_campo){
          if (campo[j] == '.'){
            printf("Possivel chutar para: %d\n", j);
            num_chutes_pos++;
            if (campo[j + 1] == '.'){
              break; // nao ha mais chutes possiveis
            }
          }
        j++;
      }
    }
    printf("%d\n", j);
    printf("%d\n", tam_campo);
    printf("%c\n", campo[tam_campo - 1]);
    if (j == tam_campo && campo[tam_campo - 1] == 'f'){
      printf("Eh possivel fazer gol! (chutar para %d)\n", j);
    }
      
    
    // prepara um string com o movimento
    // de inserir um filosofo em posicao aleatoria do campo
    rand_pos = rand() % (tam_campo + 1);
    sprintf(buf, "%c f %d\n", lado_meu, rand_pos);

    // envia o movimento para o controlador do campo
    campo_envia(buf);  
  }
}
