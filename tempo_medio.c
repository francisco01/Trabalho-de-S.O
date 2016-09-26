#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int nome;
	int tmp_exec;
	int deadline;
	int tmp_chegada;
	int tmp_final;
	int tmp_parcial;
}tp_processo;
typedef struct tp_celula *apont;
typedef struct tp_celula{
	tp_processo item;
	apont prox;
	apont ant;
}tp_celula;

typedef struct{
	apont primeiro, ultimo;
	int tam;
}tp_lista;

void flv (tp_lista *l);
void inserir_fim (tp_lista *l);
void calcular_tmp_medio_FIFO (tp_lista l, int n);
void inserir_ordenado_SJF (tp_lista *l);
void calcular_tmp_medio_RR(tp_lista l, int n);


int main(){
	
	tp_lista l;
	int i, n = 4;
	flv (&l);
	for (i = 0; i < n; i++){
		inserir_fim (&l);
		//system ("cls");
	}
	//calcular_tmp_medio_FIFO (l, n);
	calcular_tmp_medio_RR(l, n);
	return 0;
}

void flv (tp_lista *l){
	l->primeiro = (apont) malloc (sizeof(tp_celula));
	l->ultimo = l->primeiro;
	l->tam = 0;
	l->ultimo->prox = NULL;
}
void inserir_fim (tp_lista *l){
	int n_proce, tmp_exec, tmp_chegada;
	printf ("Informe o numero do processo: ");
	scanf ("%d", &n_proce);
	printf ("Informe o tempo de execucao do processo: ");
	scanf ("%d", &tmp_exec);
	printf ("Informe o tempo de chegada do processo: ");
	scanf ("%d", &tmp_chegada);
	l->ultimo->prox = (apont) malloc (sizeof(tp_celula));
	l->ultimo->prox->ant = l->ultimo;
	l->ultimo = l->ultimo->prox;
	l->ultimo->item.nome = n_proce;
	l->ultimo->item.tmp_chegada = tmp_chegada;
	l->ultimo->item.tmp_exec = tmp_exec;
	l->ultimo->prox = l->primeiro->prox;
}
void inserir_ordenado_SJF (tp_lista *l){
	int n_proce, tmp_exec, tmp_chegada;
	apont aux, aux2;
	printf ("Informe o numero do processo: ");
	scanf ("%d", &n_proce);
	printf ("Informe o tempo de execucao do processo: ");
	scanf ("%d", &tmp_exec);
	printf ("Informe o tempo de chegada do processo: ");
	scanf ("%d", &tmp_chegada);
	if (l->tam < 2){
		l->ultimo->prox = (apont) malloc (sizeof(tp_celula));
		l->ultimo = l->ultimo->prox;
		l->ultimo->item.nome = n_proce;
		l->ultimo->item.tmp_chegada = tmp_chegada;
		l->ultimo->item.tmp_exec = tmp_exec;
		l->tam++;
		l->ultimo->prox = NULL;
	}
	else{
		aux = l->primeiro->prox;
		aux2 = (apont) malloc (sizeof(tp_celula));
		aux2->item.nome = n_proce;
		aux2->item.tmp_chegada = tmp_chegada;
		aux2->item.tmp_exec = tmp_exec;
		aux2->prox = NULL;
		while (aux->prox != NULL){
			if (tmp_exec < aux->prox->item.tmp_exec){
				aux2->prox = aux->prox;
				aux->prox = aux2;
				return;
			}
			else{
				aux = aux->prox;
			}
		}
		aux->prox = aux2;
	}
		
			

}
void calcular_tmp_medio_FIFO (tp_lista l, int n){
	int tmp_medio ,cont = 1;
	float soma = 0;
	apont aux;
	aux = l.primeiro->prox;

	while (n > 0){
		if (cont == 1){
		
			tmp_medio = aux->item.tmp_exec - aux->item.tmp_chegada;
			aux->item.tmp_final = tmp_medio;
			aux->item.tmp_parcial = tmp_medio;
		}
		else{
			aux->item.tmp_parcial = tmp_medio + aux->item.tmp_exec;
			aux->item.tmp_final = aux->item.tmp_parcial - aux->item.tmp_chegada;
			tmp_medio =  aux->item.tmp_parcial;
		}
		soma += aux->item.tmp_final;
		cont++;
		aux = aux->prox;
		n--;
		
	}
	printf ("Tempo medio e: %.2f\n", soma/4);
}
void calcular_tmp_medio_RR(tp_lista l, int n){
	int qntum = 2, tmp = 0, guard_exec, cont = 0, flag = 0, i , m , x;
	float soma = 0;
	apont aux, aux2, aux3;
	aux = l.primeiro->prox;
	while (n > 0){
		m = n-1;
		x = aux->item.tmp_exec;
		printf ("nome do processo %d\n", aux->item.nome);
		//if (aux->prox == l.primeiro->prox){
			
		//}
		if (x > qntum){
			aux->item.tmp_exec = aux->item.tmp_exec - qntum;
			tmp += qntum+1;
			//printf ("1\n");
		}
		if (x <= qntum){
			guard_exec = aux->item.tmp_exec;
			aux->item.tmp_exec = 0;
			//printf ("2\n");
		}
			
		if (aux->item.tmp_exec > 0){
			aux->item.tmp_parcial = tmp;
			//printf ("3\n");
			
		}
		if (aux->item.tmp_exec == 0){
			//printf ("jkfvfhsdkjhfd\n");
			n--;
			tmp += guard_exec;
			aux->item.tmp_parcial = tmp;
			printf ("tmp corrido %d e nome do processo %d\n", aux->item.tmp_parcial, aux->item.nome);
			aux->item.tmp_final = aux->item.tmp_parcial - aux->item.tmp_chegada;
		}
		aux2 = aux;
		//printf ("nome do processo %d\n", aux2->item.nome);
		aux2 = aux2->prox;
		while (m > 0){
	
			if (aux->item.tmp_parcial >= aux2->item.tmp_chegada && aux->item.tmp_exec != 0 ){
				cont++;	
			}
			m--;
			aux2 = aux2->prox;
		}
		aux3 = aux->ant;
		aux2 = aux;
		while (cont > 0){
			aux2 = aux2->prox;
			cont--;
			if (cont == 0){
				printf ("nome do processo      %d\n", aux2->item.nome);
				if (aux2 == l.ultimo){
					aux->ant->prox = aux->prox;
					aux->prox->ant = aux->ant;
					aux->prox = aux2->prox;
					aux2->prox->ant = aux;
					aux2->prox = aux;
					aux->ant = aux2;
					l.ultimo = aux;
					l.ultimo->prox = l.primeiro->prox;
					printf ("1\n");
					printf ("nome do ultimo processo %d\n", l.ultimo->item.nome);
					
				}
				else{
					aux->ant->prox = aux->prox;
					aux->prox->ant = aux->ant;
					aux->prox = aux2->prox;
					aux2->prox->ant = aux;
					aux2->prox = aux;
					aux->ant = aux2;
					l.ultimo->prox = l.primeiro->prox;
					printf ("2\n");
				}
				//n--;
			}
			flag = 1;
		}
		if (aux == l.ultimo && aux->item.tmp_exec > 0 && l.primeiro->prox->item.tmp_exec == 0 && !flag){
			aux = aux;
			//n--;
			printf ("t\n");
		}
		else if (flag){
			aux = aux3->prox;;
			flag = 0;
			//n--;
		}
		else{
			aux = aux->prox;
			//n++;
			printf ("valor n %d\n", n);
		}

	}			
	aux = l.primeiro->prox;
	n = 4;
	while (n > 0){
		soma += aux->item.tmp_final;
		printf ("nome %d\n", aux->item.nome);
		printf ("tempo final %d\n", aux->item.tmp_final);
		aux = aux->prox;
		n--;
	}
	printf ("Tempo medio e: %.2f\n", soma/4);


}
