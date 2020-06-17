#include <stdio.h>
#include <string.h>
#define MAX 50

/* Estrutura _Item criada */
typedef struct _Item{
	char 	Nome[255];
	char 	Tel[10+1];
	int 	Idade;
}ITEM;
/* ITEM � o nome dado a estrutura _Item pelo comando typedef*/

/* A Matriz Agenda com 50 indices no eixo Y (0 � 49) � criada como do tipo da estrutura */
ITEM agenda[MAX]; //VETOR DE ITENS DA AGENTA
/* Vari�vel que ser� utilizada para controlar os indices da matriz Agenda */
int indice = 0; //ITEM DO PRIMEIRO ITEM VAZIO

/* Prot�tipo das fun��es */
void Adicionar(void);
void Captura(char *perg, char *scanset, void *dado);
void Menu(void);
void Listar(void);
void BuscarNome(void);
void RemoverInd(void);
void Importar(void);
void ImportOpen(void);
void Fechar(void);
void Ordenar(int tam);

int main(void)
{
  int aux;	
  /* A fun��o memset configura o espa�o da mem�ria com o valor 0. Ou seja, praticamente ele 
  preenche todo o endere�o da matriz agenda com o valor 0. */
  memset(agenda, 0,(MAX * sizeof(ITEM))); //INICIALIZA A AGENDA
  /* Fun��o para importar os contatos do arquivo bin�rio */
  ImportOpen();
  /* Estrutura de repeti��o infinita, pois a condi��o sempre ser� verdadeira */
  while (1)
	{
    system("cls"); //limpa tela
    aux = 0;
    /* Chama a fun��o Menu */
    Menu();	
    /* Chama a fun��o Captura passando como par�metros a frase que ser� exibida na tela
    O par�metro da fun��o scanf para filtragem de dados e o endere�o da vari�vel aux. */
    Captura("\nEntre com a opcao e digite <ENTER>: ","%d",&aux);
  	switch (aux)
  	{
  		case 1://Adiciona
      		/* Verifica se a agenda j� est� cheia ou seja se j� possui 50 cadastros. */
            if(indice == MAX)
            {
              printf("Agenda cheia!!!\n");
              break;
            }
            /* Chama a fun��o adicionar */
            Adicionar();
 			break;
  			
  		case 2: //Remover          
  			RemoverInd();
     	  break;
	       
  		case 3://Lista
        Listar();
        break;
  		
  		case 4: //Busca Nome
  			BuscarNome();
  			break;
       	case 5: // Importar
       	     Importar();
       	     break;
        case 6: // Ordenar
             Ordenar(indice-1);
             printf("\n\n A ordenacao da matriz foi realizada com sucesso! \n\n");
             system("PAUSE");
             break;
  		case 7://Sair				
  			printf("\nSelecionou SAIR\n");
  			Fechar();
  			return(0);
  			break;
  
  		default:
  			printf("\nOpcao Invalida!!!\n");
  			break;
  	}
    system("cls");								
	}
	
}
/* Fun��o para Ordenar os ind�ces da agenda, por meio da idade de cada registro. 
Em ordem decrescente. */
void Ordenar(int tam) {
     /* Se a vari�vel tam (que representa o tamanho do vetor agenda em quantidade de cadastros, 
     mas ser� alterada por causa da recursividade empregada dentro da fun��o.), for igual a 0, 
     significa que se chegou � ordena��o do ultimo cadastro, ent�o retorna at� a fun��o mestra.
     */
     if (tam == 0) {
        return;
     }
     /* Cria as vari�veis num e temp */
     int num, trocou = 0;
     ITEM temp;
     /* Cria a vari�vel x que ser� utilizada no Loop */
     int x = 0;
     /* Estrutura de repeti��o que ser� utilizada para ordenar os indices */
     for (x=0;x<tam;x++) {
         /* Se a idade do indice anterior for menor que a idade do indice maior, 
         mova-a para um item acima e aloca a de idade maior uma posi��o a menos. (abaixo) */
         if (agenda[x].Idade < agenda[x+1].Idade) {
            temp = agenda[x+1];
            agenda[x+1] = agenda[x];
            agenda[x] = temp;
            trocou = 1;
         }
     }
     /* Se foi executada alguma troca chama a recurs�o*/
     if (trocou) {
        /* Provoca a recurs�o na fun��o, chama ela mesma com o tamanho reduzido em um. */
        Ordenar(tam-1);
     }
}
/* Fun��o Importar na abertura do arquivo */
void ImportOpen(void) { 
    int read = 0, contatos = 0;
    /* Cria a vari�vel fileopen do tipo Arquivo */
    FILE *fileopen;
    /* L� o arquivo dados.bin que � do tipo bin�rio */
    fileopen = fopen("dados.bin","r+b");
    /* Verifica se o arquivo existe */
    if (!fileopen)
    {
        printf("\n\n Arquivo Dados.bin inexistente \n\n");
        system("pause");
        return;
    }
    /* Estrutura de repeti��o para leitura das linhas do arquivo */
    for(read=0; read<MAX; read++)
    {
        /* Se a leitura de cada contato for realizada com sucesso e a idade � diferente de 0 */
        if(fread(&agenda[read],sizeof(struct _Item),1,fileopen) == 1 && agenda[read].Idade != 0)
        {
               /* N�mero de contatos adicionados */                              
               contatos++;
        }
        /* Caso a leitura dos contatos n�o for realizada com suceso exibe uma mensagem de erro e o 
        n�mero de contatos adicionados at� aquele momento e sai do arquivo */
        else if (agenda[read].Idade != 0) {
             printf("\n\n Foi detectado um erro na leitura do arquivo! \n\n");
             printf("\n\n Foram carregados %d contatos dentro da agenda \n\n",contatos);
             system("PAUSE");
             fclose(fileopen);
             return;
        }  
    }
    /* Mostra a mensagem de quantos contatos foram adicionados, mostra a pausa de tela e fecha
    o arquivo  */
    printf("\n\n Foram adicionados %d contatos dentro da agenda \n\n",contatos);
    system("PAUSE");
    indice = contatos;  
    fclose(fileopen);
}
/* Fun��o Importar */
void Importar(void) {
     /* Cria a vari�vel que conter� o nome do arquivo */
     char arquivo[100];
     /* Cria o ponteiro do tipo do arquivo */
     FILE *file = malloc(sizeof(FILE));
     /* Captura o nome do arquivo que o usu�rio deseja importar */
     Captura("\n\nDigite o nome do arquivo que deseja importar: ","%100[^\n]",arquivo);
     /* Armazena o resultado "arquivo" dentro do ponteiro file */
     file = fopen(arquivo,"r");    
     /* Verifica se o arquivo foi encontrado com sucesso */
     if (file) {
        int cont = indice;
        /* Enquanto n�o chegar no final do arquivo */
        /* Para alocar as informa��es as suas respectivas vari�veis. */
        int contadd = 0;
        while (!feof(file) && cont < 50) {
                //Cria uma matriz bidimensional para capturar as linhas do arquivo
                char matriz[280];
                //Captura a linha e adiciona na matriz
                fgets(matriz,280,file);
                /* Cria os ponteiros e os define com o valor nulo */
                char *p1 = NULL;
                char *p2 = NULL;
                char *p3 = NULL;
                /* A fun��o strchr captura a localiza��o do caracter passado como segundo argumento.
                Ent�o se a primeira linha do arquivo de texto, por exemplo for: Vinicius;35994331;12 
                A vari�vel matriz ter� exatamente essa linha Vinicius;35994331;12\0\n
                p1 ter� esse valor ;35994331;12 */
                p1 = strchr(matriz,';');
                /* Verifica se o ponteiro p1 permanece nulo, caso esteja para e sai da estrutura. */ 
                if (p1 == NULL){printf("\n Ocorreu um erro no upload dos registros. \n\n");break;} 
                /* A fun��o memcpy copia o conte�do de um endere�o na mem�ria (uma vari�vel) para outra vari�vel */
                /* Sendo que a sua sintaxe � memcpy(destinatario,remetente,endere�o na mem�ria do remetente */
                memcpy(agenda[cont].Nome,matriz,(p1-matriz));
                /* se p1 cont�m ;35994331;12 ent�o pega-se novamente p2 que conter� ;12 */
                p2 = strrchr(p1,';');
                if (p2 == NULL || p1 == p2){printf("\n Ocorreu um erro no upload dos registros. \n\n");break;} 
                /* Subtrai-se p2 - p1 (lembrando que s�o endere�os), sendo que p1 � somado para sair o primeiro
                ponto e v�rgula, depois se subtrai 1 para tirar o �ltimo ponto e virgula existente. */                                    
                memcpy(agenda[cont].Tel,p1,(p2-(p1++))-1);
                /* A fun��o strtok quebra a string que est� no endere�o de p1 at� o \n e armazena no ponteiro p3 */
                p3 = strtok((p2+1),"\n");
                if (sizeof(p3) > 4 || p3 == NULL){printf("\n Ocorreu um erro no upload dos registros. \n\n");break;} 
                /* Com o valor do ponteiro p3 que � do tipo char, transforma-se em inteiro pela fun��o atoi. */
                agenda[cont].Idade = atoi(p3);         
                cont++;
                contadd++;
        }
        if (cont == 50) {
           printf("\n\nAgenda cheia!\n");
        }
        printf("\n\n Foram adicionados %d contatos na agenda.\n\n",contadd);
        system("PAUSE");
        /* Adiciono o total de cadastros ao Indice total do programa */
        indice = cont;
        /* Fecha o arquivo */
        fclose(file);        
     }
     /* Caso contr�rio exibe na tela que o arquivo n�o foi encontrado */
     else {
          printf("\n\n Arquivo nao encontrado! \n\n");
          system("PAUSE");
          return;
     }
    
}
/* Fun��o Menu */
void Menu(void)
{
  printf("MENU PRINCIPAL  Itens[%d]\n",indice);
  printf("--------------\n\n");
  printf("1 - Adicionar\n");
  printf("2 - Remover\n");
  printf("3 - Listar\n");
  printf("4 - Buscar\n");
  printf("5 - Importar\n");
  printf("6 - Ordenar\n");
  printf("7 - Sair\n");
  printf("\n");
}
/* Fun��o de captura de caracteres */ 
void Captura(char *perg, char *scanset, void *dado)
{

    printf(perg);
    scanf(scanset,dado);
    //� necess�rio esvaziar o buffer de entrada de dados porque o scanf coloca o \n no endere�o e isso pode
    //ser utilizado como um inteiro e as op��es n�o ser�o mais capturadas.
    while (getchar()!= '\n'){} // esvazia o buffer de entrada  

}
/* Fun��o adicionar, adiciona 1 item no eixo Y na matriz agenda */
void Adicionar(void)
{
  //CAPTURA NOME
  Captura("Nome: ","%254[^\n]",agenda[indice].Nome);

  //CAPTURA TELEFONE
  Captura("\nTelefone: ","%10[0-9]",agenda[indice].Tel);

  //CAPTURA IDADE
  Captura("\nIdade: ","%d",&agenda[indice].Idade);
  
  indice++;//incrementa o �ndice de primeiro item vazio

}
/* Fun��o Listar que lista os itens no eixo Y da matriz agenda */
void Listar(void)
{
  int aux = 0;
  
  printf("\nIND NOME%45s TEL%7s IDADE\n"," "," ");
  
  while ((aux < indice))
  {
    printf("%3d %-49s %-10s %-3d \n", aux, agenda[aux].Nome, agenda[aux].Tel, agenda[aux].Idade);
    
    //faz a quebra no 20.o item impresso
    if(((aux+1)%20) == 0)//tenho que somar +1 por causa do 0
    {
      system("pause");
      system("cls");
      printf("\nIND NOME%45s TEL%7s IDADE\n"," "," ");          
    }
    aux ++;
  }
  system("pause"); 
}
/* Fun��o Buscar o nome do contato na agenda */
void BuscarNome(void)
{
  int ind = 0;
  char nomeP[254+1];
  char *p;

  memset(nomeP, 0, sizeof(nomeP));

  Captura("Nome Procurado: ","%254[^\n]",nomeP);

  printf("\nIND NOME%45s TEL%7s IDADE\n"," "," ");

  while(ind != indice)
  {
    p = strstr(agenda[ind].Nome, nomeP);

    if (p == agenda[ind].Nome)
    {
      printf("%3d %-49s %-10s %-3d \n", ind, agenda[ind].Nome, agenda[ind].Tel, agenda[ind].Idade);
    }

    ind++;
  }
  system("pause");

}
/* Fun��o criada para remover os indices da matriz */
void RemoverInd(void)
{
  int atual = 0;
  int post = 0;
  int ind = 0;

  Captura("\n\nIndice a ser retirado: ", "%d", &ind);

  if (ind >= indice)
  { 
    printf("\nIndice n�o existe");
    return;
  }
  while(atual < indice)
  {
    if (ind == atual)
    {
      printf("Confirma remocao de %s, caso sim pressione S: ",agenda[atual].Nome);
      if(getchar() != 'S')
      {
        return;
      }
      
      while(post != indice)
      {
        post = atual+1;
        agenda[atual] = agenda[post];
        atual++;
      }
      
      indice --;

    }  
    atual++;   
  }
}
/* Fun��o fechar para criar ou sobrescrever o arquivo bin�rio */
void Fechar() {
    /* Cria o ponteiro do tipo de arquivo*/ 
    FILE *fileclose;
    /* Cria ou sobrescreve o arquivo dados.bin */
    fileclose = fopen("dados.bin","w+b");
    /* Estrutura para escrever dentro do arquivo bin�rio que � aberto no inicio 
    do programa */
    int cont = 0;
    for(cont=0; cont<MAX; cont++)
    {
        /* Escreve os dados no arquivo bin�rio */    
        if(fwrite(&agenda[cont],sizeof(struct _Item),1,fileclose) != 1)
        {
               /* Caso ocorra algum erro na escrita mostre uma mensagem de erro */                               
               printf("\n\n Erro na escrita do arquivo! O armazenamento ser� cancelado \n\n");
               system("PAUSE");
               return;
        }
    }
    fclose(fileclose);
}
