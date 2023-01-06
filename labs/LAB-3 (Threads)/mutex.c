#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int id;
} thread_arg;

void *thread(void *vargp);

pthread_mutex_t mutex;
int var;

int main()
{
    int n_threads = 50;
    pthread_t tid[n_threads];
    thread_arg a[n_threads];
    int i = 0;

    var = 0;

    // Cria o mutex
    pthread_mutex_init(&mutex, NULL);

    //Cria as threads
    for(i=0; i<n_threads; i++)
    {
        a[i].id = i;
        pthread_create(&(tid[i]), NULL, thread, (void *)&(a[i]));
    }

    // Espera que as threads terminem
    for(i=0; i<n_threads; i++)
    {
        pthread_join(tid[i], NULL);
    }

    printf("Valor de var no fim do programa: %d\n", var);
    // Destroi o mutex
    pthread_mutex_destroy(&mutex);

   pthread_exit((void *)NULL);
}

void *thread(void *vargp)
{
    // Converte a estrutura recebida
    thread_arg *a = (thread_arg *) vargp;

    // Como vamos acessar uma variavel global, deve-se protege-la com uma fechadura
    pthread_mutex_lock(&mutex);
    printf("Thread %d: valor de var antes da conta: %d\n", a->id+1, var);
    int j = 0;
    for(j=0; j<1000; j++)
                    var = var + 1;
    printf("Thread %d: valor de var depois da conta: %d\n", a->id+1, var);
    pthread_mutex_unlock(&mutex);

    pthread_exit((void *)NULL);
}