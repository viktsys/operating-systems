#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS     30

void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   //esta funcao imprime o identificador da thread e sai
   printf("Ola mundo! Eu sou a thread #%ld!\n", tid);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  // O programa principal cria as threads e sai
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   for(t=0;t<NUM_THREADS;t++){
     printf("Estou no main: Criando a thread %ld\n", t);
     rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
     // sleep nao eh necessario, eh apenas para dar tempo de analisar
     sleep(1);
     if (rc){
       printf("ERRO; o codigo retornado de pthread_create() eh %d\n", rc);
       exit(-1);
       }
     }

   /* Ultima coisa que o main() tem que fazer */
   pthread_exit(NULL);
}