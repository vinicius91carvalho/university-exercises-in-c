#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 5  

/*
        Integrantes do grupo:
        
        Nome: Vinicius de Almeida Carvalho
        RA: 111010909
        
        Nome: Lucas Rocha
        RA: 11101483
*/


typedef struct _pessoa {
        char Nome[255];
        char Sexo;
        int Idade;
        float Altura;
        float Peso;
        
} PESSOA;
PESSOA ficha[MAX];
int main(int argc, char *argv[])
{
  int x, n, k, j;
  float imc[5], inter, medi, aria;
  char aux[255];
  for (x=0;x<=4;x++) {
      printf("\n Digite o Nome da pessoa %d: ",x+1);
      scanf("%254[^\n]",&ficha[x].Nome);
      while (getchar()!= '\n'){}
      printf("\n Digite o Sexo (M ou F) de %s: ",ficha[x].Nome);
      scanf("%c",&ficha[x].Sexo);
      while (getchar()!= '\n'){}
      printf("\n Digite a Idade de %s: ",ficha[x].Nome);
      scanf("%d",&ficha[x].Idade);
      while (getchar()!= '\n'){}
      printf("\n Digite a Altura de %s: ",ficha[x].Nome);
      scanf("%f",&ficha[x].Altura);
      while (getchar()!= '\n'){}
      printf("\n Digite o Peso de %s: ",ficha[x].Nome);
      scanf("%f",&ficha[x].Peso);
      while (getchar()!= '\n'){}  
      printf("\n\n");    
  }    
  printf("\n Ordernar por nome \n\n");
  for (n=0;n<=3;n++) {
    for (k=0;k<=3;k++) {
        if (strcmp(ficha[k].Nome, ficha[k+1].Nome) > 0) {
           strcpy(aux,ficha[k].Nome);
           strcpy(ficha[k].Nome,ficha[k+1].Nome);
           strcpy(ficha[k+1].Nome,aux);  
           inter = ficha[k].Sexo;
           ficha[k].Sexo =  ficha[k+1].Sexo;
           ficha[k+1].Sexo = inter;
           j = ficha[k].Idade;
           ficha[k].Idade = ficha[k+1].Idade;
           ficha[k+1].Idade = j;
           medi = ficha[k].Altura;
           ficha[k].Altura = ficha[k+1].Altura;
           ficha[k+1].Altura = medi;
           aria = ficha[k].Peso;
           ficha[k].Peso = ficha[k+1].Peso;
           ficha[k+1].Peso = aria;
        }
    }  
  }
  for (n=0;n<=4;n++) {
      printf("%d - Nome: %s, Sexo: %c, Idade: %d anos, Altura: %.2fm, Peso: %.2fkg  \n",n,ficha[n].Nome,ficha[n].Sexo,ficha[n].Idade,ficha[n].Altura,ficha[n].Peso);
  }
  printf("\n\n");
  system("PAUSE");
  printf("\n Ordernar por pessoas que estao abaixo do peso \n\n");
  for (n=0;n<5;n++) {
      imc[n] = ficha[n].Peso / powf(ficha[n].Altura,2);
      if (ficha[n].Sexo = 'M') {
         if (imc[n] < 20.7) {
            printf("%d - Nome: %s, Sexo: %c, IMC: %2.f  \n",n,ficha[n].Nome,ficha[n].Sexo,imc[n]);
         }
      }
      else if (imc[n]< 19.1) {
           printf("%d - Nome: %s, Sexo: %c, IMC: %2.f  \n",n,ficha[n].Nome,ficha[n].Sexo,imc[n]);
      }
  }
  printf("\n\n");
  system("PAUSE");
  printf("\n Ordernar por pessoas que estao com peso ideal \n\n");
  for (n=0;n<5;n++) {
      imc[n] = ficha[n].Peso / powf(ficha[n].Altura,2);
      if (ficha[n].Sexo = 'M') {
         if (imc[n] > 20.6 && imc[n] < 26.1) {
            printf("%d - Nome: %s, Sexo: %c, IMC: %2.f  \n",n,ficha[n].Nome,ficha[n].Sexo,imc[n]);
         }
      }
      else if (imc[n] > 19.1 && imc[n] < 25.8) {
           printf("%d - Nome: %s, Sexo: %c, IMC: %2.f  \n",n,ficha[n].Nome,ficha[n].Sexo,imc[n]);
      }
  }
  printf("\n\n");
  system("PAUSE");
  printf("\n Ordernar por pessoas que estao acima peso ideal \n\n");
  for (n=0;n<5;n++) {
      imc[n] = ficha[n].Peso / powf(ficha[n].Altura,2);
      if (ficha[n].Sexo = 'M') {
         if (imc[n] > 26.1) {
            printf("%d - Nome: %s, Sexo: %c, IMC: %2.f  \n",n,ficha[n].Nome,ficha[n].Sexo,imc[n]);
         }
      }
      else if (imc[n] > 25.8) {
           printf("%d - Nome: %s, Sexo: %c, IMC: %2.f  \n",n,ficha[n].Nome,ficha[n].Sexo,imc[n]);
      }
  }
  printf("\n\n");
  system("PAUSE");
  return 0;
}
