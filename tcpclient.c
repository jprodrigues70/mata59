#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include"netdb.h"
#include"pthread.h"

#define PORT 4444
#define BUF_SIZE 2000

struct sockaddr_in addr, cl_addr;
int sockfd, ret;
char * serverAddr;

void * receiveMessage(void * socket) {
 int sockfd, ret;
 char buffer[BUF_SIZE];
 sockfd = (int) socket;
 memset(buffer, 0, BUF_SIZE);
 for (;;) {
  ret = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);
  if (ret < 0) {
   printf("Erro ao receber mensagens!\n");
   exit(1);
  } else {
   printf("Servidor: ");
   fputs(buffer, stdout);
  }
 }
}

connectToServer() {
  printf("Conectando...\n");

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(serverAddr);
  addr.sin_port = PORT;

  ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));

  if (ret < 0) {
   printf("Erro ao conectar com o servidor!\n");
   exit(1);
  }

  printf("Conectado.\n");
}

createSocket() {
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    printf("Erro ao criar socket!\n");
    exit(1);
  }
  printf("Socket ciado.\n");
}

startClient() {

}

messageMachine() {
  char buffer[BUF_SIZE];
  pthread_t rThread;

  memset(buffer, 0, BUF_SIZE);
  printf("Digite uma mensagem por vez e tecle enter para enviar!\n");

  //creating a new thread for receiving messages from the server
  ret = pthread_create(&rThread, NULL, receiveMessage, (void *) sockfd);
  if (ret) {
    printf("ERROR: Return Code from pthread_create() is %d\n", ret);
    exit(1);
  }

  while (fgets(buffer, BUF_SIZE, stdin) != NULL) {

    if (strcmp(buffer, "obrigado\n") == 0) exit(1);

    ret = sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));
    if (ret < 0) printf("Erro ao enviar mensagem!\n\t-%s", buffer);
  }
}

int main(int argc, char**argv) {

 if (argc < 2) {
  printf("usage: client < ip address >\n");
  exit(1);
 }

 serverAddr = argv[1];

 createSocket();
 connectToServer();
 messageMachine();

 close(sockfd);
 pthread_exit(NULL);

 return 0;
}
