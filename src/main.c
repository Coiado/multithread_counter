/* Contador de palavras
 *
 * Este programa recebera uma serie de caracteres representando palavras em sua
 * entrada. Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de palavras separadas que recebeu e, apos, encerrar.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#define TAMANHO 1000

#define WORKERS 4


int resposta = 0;
pthread_mutex_t trava;
int numeros[TAMANHO];
int pos = 0;

int primo(int num)
{
    if (num == 1 || num == 0 ) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0 && num > 2) return 0;
    for(int i = 3; i < num; i+= 1)
    {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

void* worker(void *arg) {
    int *N = (int*)(arg);
    int M = (*N);
    while (1) {
        
        pthread_mutex_lock(&trava);
        if (pos >= M) break;
        int valor = numeros[pos];
        pos++;
        pthread_mutex_unlock(&trava);
        resposta += primo(valor);
    }
    return NULL;
}




int main() {
    pthread_t workers[WORKERS];
    char text[TAMANHO];
    
    /* Pegando input */
    scanf("%[^\n]",text);
    
    char *token = strtok(text, " ");
    
    int tam = 0;
    
    while(token != NULL)
    {
        numeros[tam] = atoi(token);
        token = strtok(NULL, " ");
        tam++;
        
    }
    /* Disparanto threads */
    for (int i=0; i<WORKERS; i++) {
        pthread_create(&(workers[i]), NULL, worker, (void*) (&tam));
    }
    
    /* Esperando threads */
    for (int i=0; i<WORKERS; i++) {
        pthread_join(workers[i], NULL);
    }
    
    /* Escrevendo resposta */
    printf("%d\n", resposta);
    
    return 0;
}
