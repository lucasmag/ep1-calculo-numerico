/*
* 1º Exercício-programa de Cálculo Numérico
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define EPSILON 0.00000001
//Função de substituição de caracteres para base Hexadecimal
void subs(int num){
	if(num==10){
		printf("A");
	}else if(num==11){
		printf("B");
	}else if(num==12){
		printf("C");
	}else if(num==13){
		printf("D");
	}else if(num==14){
		printf("E");
	}else if(num==15){
		printf("F");
	}
}
//Função de conversão de bases
void conversao(double num, int divisor){
	int inteiro = num, novo_int = num, int_frac;
	double decimal = num - inteiro;
	char dec[20];
	int valor[30];
	int valor_frac[20];
	int count_int = 0, count_frac=0, x;
	
	//Cáculo da parte inteira do número
	while(inteiro>=divisor){
		valor[count_int]=inteiro%divisor;
		inteiro=inteiro/divisor;
		count_int++;
	}
	valor[count_int]=inteiro;
	
	//Cálculo da parte fracionária
	while(count_frac < 20){
		//valor_frac[count_frac] = decimal*divisor;
		int_frac = decimal*divisor;
		valor_frac[count_frac]=int_frac;
		decimal=(decimal*divisor)-int_frac;
		count_frac++;
	}
	//Impressão das bases convertidas (binário e octal)
	if(divisor == 2 || divisor == 8){
		printf("\n[%s]: ", (divisor==2)?"BINÁRIO":"OCTAL");
		for(x=count_int; x>=0 ;x--){
			printf("%d", valor[x]);
		}
		printf(",");
		for(x=0; x<20 ;x++){
			printf("%d", valor_frac[x]);
		}
	}
	//Impressão da base convertida (Hexadecimal)
	if(divisor == 16){
		printf("\n[HEXADECIMAL]: ");
		for(x=count_int; x>=0 ;x--){
			if(valor[x]>9){
				subs(valor[x]);
			}
			else{
				printf("%d", valor[x]);
			}
		}
		printf(",");
		for(x=0; x<=count_frac-1 ;x++){
			if(valor_frac[x]>9){
				subs(valor_frac[x]);
			}
			else{
				printf("%d", valor_frac[x]);
			}
		}
	}
}
//Aloca Matriz
double **alocaMatriz(int linha, int coluna){
	int i, j;
	double **M = (double **) malloc(sizeof(double *)*linha);
	if(M==NULL){
		return NULL;
	}
	for(i=0;i<linha;i++){
		M[i]=(double *) malloc(sizeof(double)*coluna);
		if(M[i]==NULL){//Caso falte memória em determinado ponto, é liberada toda memória alocada até o momento
			for(j=0;j<i;j++){
				free(M[j]);
			}
			free(M);
			return NULL;
		}
	}
	return M;
}
//Desaloca Matriz
void desalocaMatriz(double **M, int linhas){
	int i;
	for(i=0;i<linhas;i++){
		free(M[i]);
	}
	free(M);
}
double calc_funcao(int grau,float *vet,float ponto){
	int i;
	double f=0;
	for (i=grau;i>=0;i--){
		f = f + vet[i]*pow(ponto,i);		
	}	
	return f;
}
//Se o SL for determindado coloca em x a solução do SL e devolve 0;
//Se for indeterminado coloca em x uma solução do SL e devolve 1;
//Se for incompatível, devolve 2.
int sretro(double **M, int n, double x[]){
	int i, j, tipo=0;
	double soma;
	
	for(i=n-1; i>=0; i--){
		soma=0;
		for(j=i+1; j<n; j++){
			soma= soma + (M[i][j]*x[j]);
		}
		if(M[i][i]==0){
			if(fabs(M[i][n]-soma) < EPSILON){
			x[i]=0;
			tipo=1;	
			}
			else{
				return(2);
			}
		}
		else{
			x[i]=(M[i][n]-soma)/M[i][i];
		}
	}
	return tipo;
}
void *jordan(double **M, int var){
	double *mX;//multiplicadores das linhas
	double *aux;//auxílio para troca de colunas
	double *result;
	short int haColuna = FALSE;
	short int i, j, k, l, m, n, tipo;
	double a, b, c;
	
	mX = (double *)(malloc(sizeof(double)*var));
	aux = (double *)(malloc(sizeof(double)*var));
	result = (double *)(malloc(sizeof(double)*var));
	
	for(i=0;i<var;i++){
		if(M[i][i] == 0){//Verifica se pivô é nulo e, caso seja, pesquisa nas colunas à direita da atual por pivô não nulo, na mesma linha.
			j=i+1;
			while(!haColuna && j<var){
				if(M[i][j]!=0){
					for(k=0; k<var ; k++){//Troca das variáveis entre colunas
						aux[k]=M[k][i];
						M[k][i] = M[k][j];
						M[k][j] = aux[k];
						haColuna = TRUE;
					}
				}
				j++;
			}
			if(haColuna==FALSE){//Caso não haja coluna que obedeça as especificações anteriores, preenche-se coluna do pivô com 0's
				for(l=0;l<var;l++){
					M[l][i]=(double)0;
				}
			}
		}
		
		//Calculo dos multiplicadores
		for(j=0;j<var;j++){
			if(j!=i){
				mX[j] = (M[j][i]/M[i][i])*(-1);
			}
		}
		//Recalculo de coeficientes a partir da coluna do pivô, da esquerda p/ direita
		for(k=i;k<=var;k++){
			for(l=0;l<var;l++){
				if(l!=i){
					if(M[i][i]!=0){
						M[l][k] = (mX[l] * M[i][k]) + M[l][k];	
					}
				}
			}
		}
		//Impressão da matriz, passo-a-passo
	}
	//Cálculo e impressão da solução
	tipo = sretro(M, var, result);

	if(tipo==2){
		printf("\nSL incompatível.");
	}
	else{
		fflush(stdin);
		for(m=0;m<var;m++){
			for(n=0; n<=var;n++){
				printf(" %10.4lf", M[m][n]);
			}
			printf("\n");
		}
		printf("\n\n");
		printf("\nSL %sdeterminado.", tipo?"In":"");
		printf("\n\n  Solução: \n");
		for(l=0;l<var;l++){
			printf("  x[%i] = %10.4lf\n",l+1, result[l]);
		}
	}
	printf("\n");
}
void cabecalho(void){
	printf("============================================================================\n");
	printf("                 CÁLCULO NUMÉRICO - EXERCÍCIO PROGRAMA Nº 1\n");
	printf("============================================================================\n");
}

void polinomios(int grau, float *P){
	int i;
	for(i=grau;i>=0;i--){
		printf("%3.0f  ",P[i]);
	}
}
int main(void){
	setlocale(LC_ALL, "Portuguese");
	char matriz[20];
	int menu = TRUE;
	int i,j, num, auxb, auxk, grau, n[4], K[4];
	float *vet_coeficientes,*P,*P1,*P2,*P3;
	float An[4], B[4],L[4],de,ate,f_a,f_b,meio;
	double converter, f_c;
	char opcao;
	double **M, *solucao;
	FILE *arquivo;
	
	while(menu){
		cabecalho();
		printf("(C = Conversão | S = Sistema linear | E = Equação algébrica | F = Finalizar)\n\n");
		printf("\nDigite a opção desejada: ");
		opcao = getchar();
		fflush(stdin);
	
	//Escolha de opções
		switch(opcao){
			case 'C':
				system("cls");
				cabecalho();
				printf("\nDigite um numero decimal para conversão: ");
				scanf(" %lf", &converter);
				
				conversao(converter, 2);
				conversao(converter, 8);
				conversao(converter, 16);
				printf("\n\n");
				break;
			case 'S':
				system("cls");
				cabecalho();
				
				printf("Nome do arquivo de texto: ");
				scanf("%s", matriz);
				strcat(matriz,".txt");
				arquivo = fopen(matriz, "r");
				while(arquivo==NULL){
					printf("Arquivo não encontrado!\n");
					printf("Nome do arquivo de texto: ");
					scanf("%s", matriz);
					strcat(matriz,".txt");
					arquivo = fopen(matriz, "r");
				}
				fscanf(arquivo, "%d", &num);//Lê quantidade de linhas(num) do arquivo de texto
				M = alocaMatriz(num, num+1);//Aloca matriz aumentada
				solucao = (double *) malloc(sizeof(double)*num);//Aloca vetor de soluções
				if(M==NULL || solucao==NULL){//Verifica se matriz foi devidamente alocada
					printf("Memória insuficiente!");
					return 1;
				}
				system("cls");
				cabecalho();
				
				printf("MATRIZ:\n");
				for(i=0;i<num;i++){
					for(j=0; j<=num ; j++){
						fscanf(arquivo, "%lf", &M[i][j]);
						printf(" %10.4lf", M[i][j]);
					}
					printf("\n");
				}
				printf("\n-------------------------------------------------\n\n");
				jordan(M, num);
				desalocaMatriz(M,num);//Desaloca toda a matriz ao concluir a execução
				break;
			case 'E':
				system("cls");
				cabecalho();
				printf("Informe o grau do polinômio:");
				scanf("%d",&grau);
				vet_coeficientes = (float *) malloc(sizeof(float)*(grau+1));
				P  = (float *) malloc(sizeof(float)*(grau+1));
				P1 = (float *) malloc(sizeof(float)*(grau+1));
				P2 = (float *) malloc(sizeof(float)*(grau+1));
				P3 = (float *) malloc(sizeof(float)*(grau+1));
				
				for(i=grau;i>=0;i--){
					printf("\na%d: ",i);
					scanf("%f",&vet_coeficientes[i]);
					fflush(stdin);
			
					if(i==grau){
						while(vet_coeficientes[i]<=0){
							printf("a%d deve ser maior que 0!\n",i);
							scanf("%f",&vet_coeficientes[i]);
						}
					}if(i==0){
						while(vet_coeficientes[i]==0){
							printf("a%d deve ser diferente de 0!\n",i);
							scanf("%f",&vet_coeficientes[i]);
						}
					}
				}
				printf("\nO polinômio é: ");
				for(i=grau;i>=0;i--){
					if(i!=0){
						printf("(%1.0f)x^%d + ",vet_coeficientes[i],i);
					}else{
					printf("(%1.0f)x^%d\n",vet_coeficientes[i],i);
					}
				}
				printf("\n\n\n");
				
				printf("Próxima tela: teorema de Lagrange.\n");
				system("pause");
				system("cls");
				cabecalho();
				
				printf(".:TEOREMA DE LAGRANGE:..\n\n");
				auxb=0;
				for(i=0;i<=grau;i++){	
					P[i] = vet_coeficientes[i];
					if(P[i]<=auxb){
						auxb = P[i];
					}
					if(P[i]<0){
						auxk = i;
					}
				}
				printf("Coeficientes dos polinômios:\n");
				printf(" P(x) = ");
				polinomios(grau,P);
				
				An[0]=P[grau];
				n[0]=grau;
				K[0]=auxk;
				B[0]=auxb*(-1);
			
				auxb=0;
				j=grau;
				if(P[0]<0){
					for(i=0;i<=grau;i++){
						P1[i] = P[j]*(-1);
						if(P1[i]<=auxb){
							auxb = P1[i];
						}
						if(P1[i]<0){
							auxk = i;
						}
						j--;
					}
				}else{
					for(i=0;i<=grau;i++){
						P1[i] = P[j];
						if(P1[i]<=auxb){
							auxb = P1[i];
						}
						if(P1[i]<0){
							auxk = i;
						}
						j--;
					}
				}
				printf("\nP1(x) = ");
				polinomios(grau,P1);
			    An[1]=P1[grau];
				 n[1]=grau;
				 K[1]=auxk;
				 B[1]=auxb*(-1);
			
				auxb=0;
				j=grau;
				for(i=0;i<=grau;i++){
					if(j%2==0){
						P2[i] = P1[j];
					}else{
						P2[i] = P1[j]*(-1);
					}
					j--;
				}
				
				if(P2[grau]<0){
					for(i=0;i<=grau;i++){
						P2[i] = P2[i]*(-1);
						if(P2[i]<=auxb){
							auxb = P2[i];
						}
						if(P2[i]<0){
							auxk = i;
						}			
					}
				}else{
					for(i=0;i<=grau;i++){
						if(P2[i]<=auxb){
							auxb = P2[i];
						}
						if(P2[i]<0){
							auxk = i;
						}
					}
				}
				printf("\nP2(x) = ");
				polinomios(grau,P2);
				An[2]=P2[grau];
				 n[2]=grau;
				 K[2]=auxk;
				 B[2]=auxb*(-1);
				j=grau;
				auxb=0;
				if(P2[0]<0){
					for(i=0;i<=grau;i++){
						P3[i] = P2[j]*(-1);
						if(P3[i]<=auxb){
							auxb = P3[i];
						}
						if(P3[i]<0){
							auxk = i;
						}
						j--;
					}
				}else{
					for(i=0;i<=grau;i++){
						P3[i] = P2[j];
						if(P3[i]<=auxb){
							auxb = P3[i];
						}
						if(P3[i]<0){
							auxk = i;
						}
						j--;
					}
				}
				printf("\nP3(x) = ");
				polinomios(grau,P3);
				An[3]=P3[grau];
				 n[3]=grau;
				 K[3]=auxk;
				 B[3]=auxb*(-1);
				/*
				An= Coeficiente de maior indice
				n=maior índice dos coeficientes
				K=maior índice dos coeficientes negativos
				B= maior valor em modulo dos coeficientes negativos
				L será um vetor com os limites
				limite superior positivo L[0],
				limite inferior positivo L[1]
				Limite inferior negativo L[2]
				Limite superior negativo L[3]
				*/
				printf("\n\nTabela:");
				printf("\n    An    n     K     B\n");
				for (i=0;i<4;i++){
					printf("%5.0f %5d %5d %5.0f\n",An[i],n[i],K[i],B[i]);	 
				}
				L[0]=1.0+pow((B[0]/An[0]),1.0/(n[0]-K[0]));
				L[1]=1.0/(1+pow((B[1]/An[1]),1.0/(n[1]-K[1])));
				L[2]=(1.0+pow((B[2]/An[2]),1.0/(n[2]-K[2])))*-1.0;
				L[3]=(1.0/(1.0+pow((B[3]/An[3]),1.0/(n[3]-K[3]))))*-1.0;
				printf("\n\nLimites:\n");
				
				for (i=0;i<4;i++){
					printf("L%d: %f\n",i, L[i]);
				}
				
				printf("\n\n\nPróxima tela: seleção de intervalos.\n");
				system("pause");
				system("cls");
				cabecalho();
				
				printf("Informe um intervalo:\nDe: ");
				scanf("%f",&de);
				printf("Até: ");
				scanf("%f",&ate);
				while(ate<=de){
					printf("\nO intervalo deve ser sempre do menor até maior!\nAté: ");
					scanf("%f",&ate);
				}
				f_a=calc_funcao(grau,vet_coeficientes,de);
				f_b=calc_funcao(grau,vet_coeficientes,ate);
				printf("\n%.4f x %.4f = %.4f\n",f_a,f_b,f_a*f_b);
				//método de Bolzano
				if(f_a*f_b<0){
					printf("O número de raízes em dado intervalo é ímpar (Há pelo meno 1 raiz nesse intervalo).\n\n");
					//Método de Bissecção
					i=0;
					do{
						meio = (ate + de)/2.0;
						f_c = calc_funcao(grau,vet_coeficientes, meio);
						if(f_a*f_c<0){
							ate=meio; 	
						}else{
							de=meio;
						}
						i++;
					}
					while(i<1000 && fabs(f_c) > EPSILON);
					printf("\nRaíz: %f\n\n\n",meio);
					
				}else{
					printf("\nO número de raízes em dado intervalo é par.\n\n\n");
				}	
				break;
			case 'F':
				menu = FALSE;
				printf("FIM DA EXECUÇÃO.");
				return 0;
			default:
				printf("\nDigite uma opção valida!\n");
		}
		fflush(stdin);
		system("pause");
		system("cls");
	}
}
