/* Comunicacao de processos atraves de pipes.
 * Autor: Elgio Schlemer
 * Data: 17/12/2000
 * Ultima revisao: 30/12/2000
 *
 * Paginas:
 * 	http://www.ulbra.tche.br/~elgios/linux
 *	http://www.inf.ufrgs.br/~elgios/linux
 *
 * Pre-requisito: estude o exemplo de fork antes, no arquico c de nome
 *      forki.c, do mesmo autor.
 * Referencias: 
 *      Linux A-Z, Phil Cornes, Prentice Hall: 1997. Pg 274.
 *      Sistemas Operacionais Modernos, Andrew Tanembaum, LTC.
 *
 * Comentario: 
 *      O Unix (representado aqui pelo Linux) é um sistema multitarefa e
 *      multiusuario. Multiusuário por permitir vários usuários usando-o ao
 *      mesmo tempo e multitarefa pela existência de vários processos
 *      concorrendo por uma única CPU, em um sistema de Time Sharing.
 *      Existem dispositivos para tornar possível a comunicação entre
 *      estes vários processos. Um destes são os chamados 'pipes', usados,
 *      por exemplo, pelo shell quando cria dois processos e faz com que a
 *      saida padrão de um seja a entrada de outro, como no exemplo:
 *      
 *              ls | wc
 *              
 *      Não se trata aqui de executar primeiro o ls, capturar a saida, ou
 *      seja, o que ele gerou, e depois chamar o wc. O DOS (segundo
 *      Tanembaum, em Sistemas Operacionais Modernos) implementa este
 *      recurso desta forma, fazendo uso de arquivos temporários, onde o ls
 *      escreveria sua saída em um arquivo temporário e DEPOIS DE TERMINAR
 *      o interpretador de comandos inicia o wc, lendo deste arquivo.
 *
 *      No Unix ambos os processos iniciam juntos e disputam a cpu. O que
 *      um escreve, neste caso, pode ser lido imediatamente pelo outro,
 *      diferente da solução DOS, sem existir um arquivo temporário. A
 *      comunicação é através de pipes.
 *
 *      Pipes são descritores de arquivos especiais gerenciados pelo SO.
 *      Tira proveito da facilidade do Unix de manipular dispositivos,
 *      mesmo periféricos, como se fossem arquivos, ou seja, usando as
 *      mesmas funções ou chamadas de sistema usadas para arquivos. Os pipes
 *      funcionam desta forma. Depois de criados, podem ser lidos e
 *      escritos como se fossem arquivos, mas não são.
 *
 *      Só é possível a comunicação através de pipes entre processos
 *      'parentes', ou seja, aqueles que tem uma relação de pai para filho,
 *      ou de 'irmão' para irmão. Isso significa que só é possível usá-los
 *      em processos criados com a chamada fork(). Isso porque a tabela de
 *      descritores de arquivos é individual para cada processo e faz parte
 *      do seu BCP. Ao criar um novo processo pelo fork(), o processo
 *      criado, chamado de filho, tem, inicialmente, o mesmo contexto do
 *      seu pai, quem o criou. Voltando ao exemplo do 'ls|wc', temos que
 *      ambos os processos (wc e ls) foram criados pelo shell, usando fork,
 *      e, portanto, ambos tem o mesmo cunjunto de descritores de arquivos
 *      que o shell tinha antes de executar os dois forks.
 *
 *      Para se utilizar pipes, então, é necessário que um processo os
 *      crie, para depois fazer a comunicação. A chamada de sistema
 *      pipe(), cria DOIS descritores de arquivos (MAS NÃO SÃO ARQUIVOS!!),
 *      um onde os dados serão lidos e outro onde serão escritos. Estes
 *      descritores ocuparão os dois números disponíveis no vetor de
 *      descritores de arquivos do processo atual. Vale lembrar que TODO O
 *      PROCESSO, ao ser iniciada sua execução, já possui TRÊS DESCRITORES
 *      pré-definidos: um para a saída padrão, um para a entrada padrão e
 *      outro para a saída padrão de erro:
 *      
 *              0 - entrada padrão de dados. Por padrão é o teclado.
 *              1 - saída padrão de dados. Por padrão é o monitor de vídeo,
 *              ou no caso mais específico do Linux em ambiente gráfico, a
 *              janela do terminal onde o programa foi executado.
 *              2 - saída padrão de erros. Por padrão, o mesmo que a saída
 *              padrão de dados.
 *
 *      Pelo exemplo acima, caso nenhum outro arquivo tenha sido aberto
 *      pelo nosso processo, os pipes ocuparam o descritor 3 e 4.
 *
 *      É necessário, portanto, guardar este valores (3 e 4, neste caso,
 *      mas não necessariamente) em variáveis para quando se desejar ler ou
 *      escrever, conheça-se o valor dos mesmos. O primeiro descritor do
 *      pipe serve para ler e o segundo para escrever.
 *
 *      Depois de criado, pode-se usar as chamadas de sistema write() para
 *      escrever e read() para ler.
 *
 *      Acompanhe comentários junto ao programa.
 */
#include <unistd.h>
#include <stdio.h>

/* Definição de uma função para imprimir msg de erros graves, abortando o
 * código */
char erro(char *m)
{
	fprintf(stderr, "ERRO: %s\n", m);
	exit(1);
}


main()
{
	int fda[2];
	/* Será usado para guardar o número descritor dos pipes */

	/* Cria o pipe (dois descritores) e armazena seus valores no vetor
	 * fda. Agora: fda[0] para ler, fda[1] para escrever. Testa se deu
	 * erro. */
	if (pipe(fda) == -1) {
		erro("Criando pipe");
	}

	/* Imprime os valores na tela. Acompanhe: como não existe nenhum
	 * outro arquivo aberto por este processo, só os três que são
	 * padrões: stdin, stdout e stderr, ele deve assumir os próximos
	 * disponíveis: 3 e 4. */

	fprintf(stderr, "%d %d\n", fda[0], fda[1]);

	/* Agora o processo é dividido em dois pelo fork. O fork foi 
         * estudado no laboratório 2  */

	switch (fork()) {
	case -1:
		erro("fork");
		break;
	case 0:
		close(1);	/* ver *1a */
		dup(fda[1]);
		close(fda[1]);
		close(fda[0]);
		execlp("ls", "ls", 0);	/* ver *1b */
		erro("Voltou do ls");
		break;
	default:
		close(0);	/* ver *2a */
		dup(fda[0]);
		close(fda[0]);
		close(fda[1]);
		execlp("wc", "wc", 0);	/* ver *2b */
		erro("Voltou do wc");
		break;
	}
/* Comentários:
 * 1a e 2a: Agora complicou um pouquinho!! 
 *      A princípio a comunicação se daria através dos descritores. Um
 *      processo poderia simplesmente fazer:
 *              write(fda[1], "Teste", 5);  onde 5 é o número de bytes.
 *              
 *      E o outro faria:
 *              read(fda[0], buff, 5); onde buff seria uma cadeia de
 *              caracteres com espaço para armazenar 5 caracteres (cuidado
 *              com o controle do \0, não feito pelo read!
 *
 *      E isso efetivamente funciona. Mas não é algo tão 'simples' assim
 *      que queremos neste nosso exemplo. Queremos aqui simular o que o
 *      shell faz ao executar um ls|wc. Então, executamos um fork, e cada
 *      um deles executa um dos processos (1b e 2b). Para isso, não é
 *      apenas uma simples comunicação entre processos que queremos, mas
 *      sim que a saída padrão do ls seja a entrada padrão do wc, tal como
 *      acontece em ls|wc!
 *
 *      Para isso, faz-se uso de uma malandragem, a chamada de sistema
 *      dup(). O dup duplica um descritor, copiando-o para uma posição
 *      livre do nosso vetor de descritores, AGORA um para cada processo,
 *      pois existem DOIS rodando na máquina. Se simplesmente executar-mos
 *      dup(fda[1]), teriamos uma cópia do descritor 4 (conforme explicado
 *      acima) no descritor 5, pois é o próximo disponível. Desta forma,
 *      teríamos, neste caso:
 *      
 *              0 - entrada padrão
 *              1 - saída padrão
 *              2 - saída padrão de erros.
 *              3 - fda[0], pipe para leitura
 *              4 - fda[1], pipe para escrita
 *              5 - cópia de fda[1], ou seja, cópia do descritor 4.
 *
 *      Mas observe um PORÉM no exemplo do código que MUDA TUDO: antes de
 *      se fazer o dup em 1a, fechou-se o descritor 1, tornando-o
 *      disponível. Como o dup pega o PRIMEIRO descritor livre, nossa
 *      tabelinha não é como a mostrada acima, mas sim:
 *
 *              0 - entrada padrão
 *              1 - cópia de fda[1], ou seja, cópia do descritor 4.
 *              2 - saída padrão de erros.
 *              3 - fda[0], pipe para leitura
 *              4 - fda[1], pipe para escrita
 *
 *      Qual a implicação disto? Como todo e qualquer processo irá
 *      "escrever na tela" usando o descritor 1, agora ele escreverá no
 *      pipe!!! Redirecionamos a saida padrão deste processo para o pipe.
 *      Em seguida o pipe original é fechado. O mesmo acontece em 2a, só
 *      que agora quem é fechado é o descritor 0, entrada padrão, sendo
 *      redirecionado para o pipe de leitura. 
 *      
 *      No final, temos para os dois processos do fork(), pai e filho, cujo
 *      filho executa o case 0: e o pai o default (novamente, ver exemplo
 *      do laboratorio 2), terão seus descritores assim:
 *
 *      Processo filho, executa o case 0:
 *              0 - entrada padrão
 *              1 - cópia de fda[1], ou seja, cópia do pipe de escrita.
 *              2 - saída padrão de erros.
 *              3 - Disponível, pois foi fechado
 *              4 - Disponível, pois foi fechado 
 *
 *
 *      Processo filho, executa o default:
 *              0 - cópia de fda[0], ou seja, cópia do pipe de leitura.
 *              1 - saída padrão 
 *              2 - saída padrão de erros.
 *              3 - Disponível, pois foi fechado 
 *              4 - Disponível, pois foi fechado 
 *
 *      Agora, sempre que o filho "imprimir na tela", estará, na verdade,
 *      escrevendo no pipe de escrita, fda[1] e sempre que o pai "ler do
 *      teclado", estará, na verdade, lendo do pipe de leitura, fda[0]. Os
 *      dois processos estão ligados, com a saída de um concatenada na
 *      entrada do outro! "Bingo"!!!
 *
 * 1b e 2b:
 *      O comando exec, com suas várias sintaxes, sendo a usada aqui o
 *      execlp, tem como característica substituir a imagem do processo
 *      atual pela do processo passado por parâmetro. É muito diferente da
 *      chamada system(), existente também no dos. No system executa-se um
 *      comando externo e espera-se pelo resultado. Aqui, no exec, o
 *      processo que o executou é substituido pelo passado por parâmetro.
 *      
 *      Ou seja, ao executar exec, o processo atual deixa de existir e dá
 *      lugar ao processo requisitado, conservando os mesmos pids dos
 *      processos. Continuam sendo filhos do processo que executou o fork e
 *      herdam destes o descritor de arquivo. 
 *      
 *      Em 1b, o processo filho tem sua imagem substituida pelo processo
 *      'ls' e em 2b, o processo pai é substituido pelo processo 'wc'. Ambos
 *      ficam com seus descritores como descrito acima, de forma que wc ira
 *      ler o que ls gerar. Como a saida padrao de wc nao foi mudada, o
 *      resultado (no caso o numero de linhas, palavras e letras que o ls
 *      resultou) saira na tela.
 *
 *      Note que, como o processo que executou o exec deixa de existir, no
 *      sentido que seu código não é mais o mesmo, a única forma do
 *      processo executar a chamada da função 'erro', logo após o exec, é se
 *      o exec FALHAR!
 *
 *      Este é o princípio básico de um shell do Unix (interpretador de
 *      comandos). Sempre que escrevemos algo na linha de comando, ele
 *      executa um ou mais forks, pega a string digitada, acerta os
 *      descritores de cada um e chama exec para executar o comando
 *      especifico. (claro, isto de forma simplista, pois um shell faz
 *      muito mais que apenas isso e eu posso concatenar vários processos,
 *      como no exemplo: 
 *      	ls -la | grep root| sort |wc 
 *      onde são QUATRO processos criados AO MESMO tempo, ligando 
 *      	entrada padrao -> ls -> grep -> sort -> wc -> saida padrao ).
 *
 */
}
