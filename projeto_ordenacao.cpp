#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void gerar_vetor(int v[], int tam){
	
	for(int i=0; i<tam; i++){
		v[i] = rand() % 1000001;
	}
}

void copiar_vetor(int v1[], int v2[], int ini, int fim){
	for(int i=ini; i<=fim; i++){
		v2[i] = v1[i];
	}
}

void imprimir_vetor(int v[], int tam){
	printf("\n");
	for(int i=0; i<tam; i++){
		printf("V[%d] = %d\n", i, v[i]);
	}
}

void bubble_sort(int v[], int tam){
	
	int var;
	
	for(int i=0; i<tam-1; i++){
		for(int j=0; j<tam-1-i; j++){
			if(v[j]>v[j+1]){
				var = v[j];
				v[j] = v[j+1];
				v[j+1] = var;
			}
		}
	}
}

void selection_sort(int v[], int tam){

	int menor, i=0, j, var, index;
	
	//encontra o menor elemento do vetor
	for(i=0; i<tam-1; i++){
		menor = v[i];
		for(j=i+1; j<tam; j++){
			if(menor > v[j]){
				menor = v[j];
				index = j;
			}
		}
		
		//troca os elementos de lugar
		if(menor < v[i]){
			var = v[i];
			v[i] = menor;
			v[index] = var;
		}
	}

}

void insertion_sort(int v[], int tam){
	
	int var, chave;
	
	for(int i=1; i<tam; i++){
		chave = v[i];
		int j=i-1;
		while((j>=0) && (v[j] > chave)){
			v[j+1] = v[j]; 
			j--;
		}
		
		v[j+1] = chave;
	}

}

void merge_sort(int v[], int ini, int fim, int tam){

	if(ini < fim){
		int meio = ini + ((fim-ini)/2);
		
		//divide o vetor em partes logicas
		merge_sort(v, ini, meio, tam);
		
		merge_sort(v, meio+1, fim, tam);
		
		int i=ini, j=meio+1, k=ini;
	
		int *resultado = (int*) malloc(tam * sizeof(int));
		
		//organiza o "lado esquerdo" e o "lado direito"
		while(i<=meio && j<=fim){
			if(v[i] <= v[j]){
				resultado[k] = v[i];
				i++;
			}else{
				resultado[k] = v[j];
				j++;
			}
			k++;
		}
		
		//caso um dos lados estoure ele copia o resto
		while(i<=meio){
			resultado[k] = v[i];
			i++;
			k++;
		}
		
		while(j<=fim){
			resultado[k] = v[j];
			j++;
			k++;
		}
		
		copiar_vetor(resultado, v, ini, fim);
		
		free(resultado);
	}

}

void quick_sort(int v[], int ini, int fim){
	if(ini < fim){
		//o pivo é o último elemento
		int piv = v[fim], var, z_min=ini-1;
	
		for(int i=ini; i<fim; i++){
			//
			if(v[i] < piv){
				z_min++;
				
				var=v[z_min];
				v[z_min] = v[i];
				v[i] = var;
			}
		}
		
		var = v[z_min+1];
		v[z_min+1] = piv;
		v[fim] = var;
		
		quick_sort(v, ini, z_min);
		
		quick_sort(v, z_min+2, fim);
	}
}

void trocar(int v[], int tam, int atual){
	while(true){
			int maior = atual;
			
			int esq = (2*atual)+1;
			int dir = (2*atual)+2;
		
			//troca o elemento filho da esquerda com o pai
			if(tam > esq && v[esq] > v[maior]){
				maior = esq;
			}
			
			//troca o elemento filho da direita com o pai
			if(tam > dir && v[dir] > v[maior]){
				maior = dir;
			}
			
			//se o atual for ja for maior que seus filhos
			if(maior == atual){
				break;
			}
			
			//troca os elementos no vetor
			int var = v[atual];
			v[atual] = v[maior];
			v[maior] = var;
			
			atual = maior;
	}
}

void heap_sort(int v[], int tam){

	int atual;
	for(int i = tam/2 -1; i>=0; i--){
		atual = i;
		trocar(v, tam, atual);
	}
	
	/* manda o elemento head para o final do vetor*/
	for(int i = tam-1; i>0; i--){
		int var = v[0];
		v[0] = v[i];
		v[i] = var;
		
		//atualiza a raiz
		atual = 0;
		
		trocar(v, i, atual);
	}
	
}

void counting_sort(int v[], int tam){

	
	int maior;
	
	maior = v[0]; 
	
	//busca o maior elemento
	for(int i=1; i<tam; i++){
		if(v[i] > maior){
			maior = v[i];
		}
	}
	
	//vetor de contagem tem os elementos valendo 0
	int *v_cont = (int *)calloc((size_t)(maior + 1), sizeof(int));
	
	//preenche o vetor de contagem
	for(int i=0; i<tam; i++){
		v_cont[v[i]]++;
	}
	
	//soma acumulada
	int *v_soma = (int *)malloc((size_t)(maior + 1) * sizeof(int));
	
	copiar_vetor(v_cont, v_soma, 0, maior);
	
	for(int i=1; i<=maior; i++){
		v_soma[i] = v_soma[i-1] + v_cont[i];
	}
	
	//vetor ordenado
	int *v_ord = (int *) malloc(tam * sizeof(int));
	
	for(int j=tam-1; j>=0; j--){
		v_ord[v_soma[v[j]] - 1] = v[j];
		v_soma[v[j]]--;
	}
	
	copiar_vetor(v_ord, v, 0, tam-1);
	free(v_ord);
	free(v_soma);
	free(v_cont); 
}

void radix_sort(int v[], int tam){
	
	int maior;
	
	maior = v[0]; 
	
	//busca o maior elemento
	for(int i=1; i<tam; i++){
		if(v[i] > maior){
			maior = v[i];
		}
	}
	
	for(int exp=1; (maior/exp) > 0; exp*=10){
		
		int *v_cont = (int *) calloc(10, sizeof(int));
		int *v_soma = (int *) malloc(10 * sizeof(int));
		int *v_ord = (int *) malloc(tam * sizeof(int));
	
		//armazena repetiçao de cada digito
		for(int i=0; i<tam; i++){
			int dig = (v[i] / exp) % 10;
			v_cont[dig]++;
		}
		
		//calculo das posiçoes finais
		v_soma[0] = v_cont[0];
        for(int i = 1; i < 10; i++) {
            v_soma[i] = v_soma[i - 1] + v_cont[i];
        }
        
        
        //ordena o vetor de acordo com a soma
        for(int j = tam - 1; j >= 0; j--) {
            int digito = (v[j] / exp) % 10;
            v_ord[v_soma[digito] - 1] = v[j]; // Guarda o número inteiro v[j]
            v_soma[digito]--;
        }
        
        copiar_vetor(v_ord, v, 0, tam-1);
        free(v_ord);
		free(v_soma);
		free(v_cont); 
	}
}

void bucket_sort(int v[], int tam){
	int min = v[0];
    int max = v[0];
    
    //achar o maior e menor valor
    for(int i = 1; i < tam; i++) {
        if (v[i] < min) min = v[i];
        if (v[i] > max) max = v[i];
    }
    
    //se o todos os números forem iguais
    if(min == max){
    	return;
	}

	//define qtd de baldes
	int num_baldes = tam / 10;
	
    if(num_baldes < 1){
		num_baldes = 1;
	}

	//verifica quantos elementos cada balde vai ter
	int *capacidade = (int *)calloc(num_baldes, sizeof(int));
    for(int i = 0; i < tam; i++) {
        int indice = (int)(((long long)(v[i] - min) * (num_baldes - 1)) / (max - min));
        capacidade[indice]++;
    }
    
    
    //armazena o ponteiro para cada balde
    int **baldes = (int **)malloc(num_baldes * sizeof(int *)); 
    
    //vai servir como controlador e índice dentro de cada balde
    int *qtd_baldes = (int *)calloc(num_baldes, sizeof(int));

    for (int i = 0; i < num_baldes; i++) {
        if (capacidade[i] > 0) {
        	/*cada índce vai armazenar o tamanho necessário para cada balde 
			armazenar seus elementos*/
            baldes[i] = (int *)malloc(capacidade[i] * sizeof(int));
        } else {
            baldes[i] = NULL;
        }
    }
    free(capacidade);
    
    //colocar os elementos nos baldes
    for (int i = 0; i < tam; i++) {
        int indice = (int)(((long long)(v[i] - min) * (num_baldes - 1)) / (max - min));
        int pos = qtd_baldes[indice];
        
        //o indice representa o balde e o pos a posição dentro dele
        baldes[indice][pos] = v[i];
        
        //vai atualizar de índice 0->1 e assim sucessivamente
        qtd_baldes[indice]++;
    }
	
	int k = 0;
    for (int i = 0; i < num_baldes; i++) {
        if (qtd_baldes[i] > 0) {
            //organiza cada balde
            insertion_sort(baldes[i], qtd_baldes[i]);

			//inserindo elementos do balde no vetor original
            for (int j = 0; j < qtd_baldes[i]; j++) {
                v[k] = baldes[i][j];
                k++;
            }
            free(baldes[i]); 
        }
    }

	free(baldes);
	free(qtd_baldes);
}

int main(){
	
	clock_t inicio, fim;
	
	double tmp_gasto;
	
	int tam; 
	
	printf("Quantos elementos no vetor deseja: ");
	scanf("%d", &tam);
	
	int *v1 = (int *)malloc((size_t)tam * sizeof(int));
	int *v2 = (int *)malloc((size_t)tam * sizeof(int));
	double *tempos = (double *)calloc(9, sizeof(double));
	
	gerar_vetor(v1, tam);
	
	for(int i=0; i<3; i++){
		int k=0;
		copiar_vetor(v1, v2, 0, tam-1);
	
		inicio = clock();
		bubble_sort(v2, tam);
		fim = clock();
		
		//printf("\n---- Bubble Sort ----\n");
		tmp_gasto = (double) (fim - inicio)/CLOCKS_PER_SEC;
		//printf("\nTempo: %f segundos\n\n", tmp_gasto);
		fflush(stdout);
		
		tempos[k] += tmp_gasto;
		k++;
		
		copiar_vetor(v1, v2, 0, tam-1);
		
		inicio = clock();
		selection_sort(v2, tam);
		fim = clock();
			
		//printf("\n---- Selection Sort ----\n");
		tmp_gasto = (double) (fim - inicio)/CLOCKS_PER_SEC;
		//printf("\nTempo: %f segundos\n\n", tmp_gasto);
		fflush(stdout);
		
		tempos[k] += tmp_gasto;
		k++;
		
		copiar_vetor(v1, v2, 0, tam-1);
		
		inicio = clock();
		insertion_sort(v2, tam);
		fim = clock();
		
		//printf("\n---- Insertion Sort ----\n");
		tmp_gasto = (double) (fim - inicio)/CLOCKS_PER_SEC;
		//printf("\nTempo: %f segundos\n\n", tmp_gasto);	
		fflush(stdout);
		
		tempos[k] += tmp_gasto;
		k++;
		
		copiar_vetor(v1, v2, 0, tam-1);
		
		inicio = clock();
		merge_sort(v2, 0, tam-1, tam);
		fim = clock();
		
		//printf("\n---- Merge Sort ----\n");
		tmp_gasto = (double) (fim - inicio)/CLOCKS_PER_SEC;
		//printf("\nTempo: %f segundos\n\n", tmp_gasto);
		fflush(stdout);
		
		tempos[k] += tmp_gasto;
		k++;
	
		copiar_vetor(v1, v2, 0, tam-1);
		
		inicio = clock();
		quick_sort(v2, 0, tam-1);
		fim = clock();
		
		//printf("\n---- Quick Sort ----\n");
		tmp_gasto = (double) (fim - inicio)/CLOCKS_PER_SEC;
		//printf("\nTempo: %f segundos\n\n", tmp_gasto);
		fflush(stdout);
		
		tempos[k] += tmp_gasto;
		k++;
		
		copiar_vetor(v1, v2, 0, tam-1);
		
		inicio = clock();
		heap_sort(v2, tam);
		fim = clock();
		
		//printf("\n---- Heap Sort ----\n");
		tmp_gasto = (double) (fim - inicio)/CLOCKS_PER_SEC;
		//printf("\nTempo: %f segundos\n\n", tmp_gasto);
		fflush(stdout);
		
		tempos[k] += tmp_gasto;
		k++;
	
		copiar_vetor(v1, v2, 0, tam-1);
	
		inicio = clock();
		counting_sort(v2, tam);
		fim = clock();
		
		//printf("\n---- Counting Sort ----\n");
		tmp_gasto = (double) (fim - inicio)/CLOCKS_PER_SEC;
		//printf("\nTempo: %f segundos\n\n", tmp_gasto);
		fflush(stdout);
		
		tempos[k] += tmp_gasto;
		k++;
		
		copiar_vetor(v1, v2, 0, tam-1);
		
		inicio = clock();
		radix_sort(v2, tam);
		fim = clock();
		
		//printf("\n---- Radix Sort ----\n");
		tmp_gasto = (double) (fim - inicio)/CLOCKS_PER_SEC;
		//printf("\nTempo: %f segundos\n\n", tmp_gasto);
		fflush(stdout);
		
		tempos[k] += tmp_gasto;
		k++;
		
		copiar_vetor(v1, v2, 0, tam-1);
		
		inicio = clock();
		bucket_sort(v2, tam);
		fim = clock();
		
		//printf("\n---- Bucket Sort ----\n");
		tmp_gasto = (double) (fim - inicio)/CLOCKS_PER_SEC;
		//printf("\nTempo: %f segundos\n\n", tmp_gasto);
		fflush(stdout);
		
		tempos[k] += tmp_gasto;
		k++;
	}
	
	for(int i=0; i<9; i++){
		tempos[i] = (tempos[i]/3) * 1000;
	}
	
	printf("\n---- Bubble Sort ----");
	printf("\nTempo Medio: %.4fms\n", tempos[0]);
	
	printf("\n---- Selection Sort ----");
	printf("\nTempo Medio: %.4fms\n", tempos[1]);
	
	printf("\n---- Insertion Sort ----");
	printf("\nTempo Medio: %.4fms\n", tempos[2]);
	
	printf("\n---- Merge Sort ----");
	printf("\nTempo Medio: %.4fms\n", tempos[3]);
	
	printf("\n---- Quick Sort ----");
	printf("\nTempo Medio: %.4fms\n", tempos[4]);
	
	printf("\n---- Heap Sort ----");
	printf("\nTempo Medio: %.4fms\n", tempos[5]);
	
	printf("\n---- Counting Sort ----");
	printf("\nTempo Medio: %.4fms\n", tempos[6]);
	
	printf("\n---- Radix Sort ----");
	printf("\nTempo Medio: %.4fms\n", tempos[7]);
	
	printf("\n---- Bucket Sort ----");
	printf("\nTempo Medio: %.4fms\n", tempos[8]);
	
	free(tempos);
	free(v2);
	free(v1);
	
	return 0;
}
