#include <stdio.h>
#include <unistd.h>

int main () {
 	int fda[2];
 	int retorno;
 	int  envio = 10;
 	pipe( fda );
        pid_t pid = fork();
 	if (pid ==0 ) {
 		close ( fda[0] );
 		write ( fda[1], &envio, 4);
 	}else {
 		close ( fda[1] );
 		read ( fda[0], &retorno, 4);
 		printf ("PAI: O retorno do filho é %d \n", retorno);
 	}
}

