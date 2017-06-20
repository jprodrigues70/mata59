#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include"pthread.h"
#include <time.h>

#define PORT 4444
#define BUFFER_SIZE 2000
#define CLADDR_LEN 100

struct sockaddr_in addr, cl_addr;
int sockfd, len, ret, newsockfd;
time_t rawtime;
struct tm * timeinfo;

void listenConnection();
void messageMachine();

void sendMessage(char* buffer) {
  ret = sendto(newsockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &cl_addr, len);
  if (ret < 0) {
    printf("Erro ao enviar mensagem!\n");
    exit(1);
  }
}

void autoResponse(char* text) {
  for (char *p = text; *p; ++p) *p = *p >= 'A' && *p <='Z' ? *p|0x60 : *p;

  if (strcmp(text, "boa tarde\n") == 0 || strcmp(text, "bom dia\n") == 0 || strcmp(text, "boa noite\n") == 0) {
    text[0] = ('a' <= text[0] && text[0] <= 'z') ? text[0]^0x20 : text[0];
    sendMessage(text);
    printf("Mensagem automática \"%s\" enviada.\n", text);
  } else if (strcmp(text, "que horas são?\n") == 0) {
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    char buffer[7];
    strftime(buffer, 7, "%H:%M", timeinfo);
    printf("Mensagem automática \"%s\" enviada.\n", buffer);
    sendMessage(strcat(buffer, "\n"));
  } else if (strcmp(text, "obrigado\n") == 0) {
    
  }
}

void * receiveMessage(void * socket) {
  int sockfd, ret;
  char buffer[BUFFER_SIZE];
  sockfd = (int) socket;
  memset(buffer, 0, BUFFER_SIZE);
  for (;;) {
    ret = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);
    if (ret < 0) {
      printf("Erro ao receber mensagens!\n");
    } else if(ret > 0) {
      printf("client: ");
      fputs(buffer, stdout);
      autoResponse(buffer);
    } else {
      printf("Todos os clientes estão desconectados\n");
      listenConnection();
      messageMachine();
    }
  }
}

void startServer() {
  int server;

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = PORT;

  server = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
  if (server < 0) {
    printf("Erro ao iniciar servidor!\n");
    exit(1);
  }
  printf("Servidor iniciado.\n");
}

void createSocket() {
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    printf("Erro ao criar socket!\n");
    exit(1);
  }
  printf("Socket criado...\n");
}

void listenConnection() {
  char client[CLADDR_LEN];

  printf("Aguardando conexão...\n");
  listen(sockfd, 5);


  len = sizeof(cl_addr);
  newsockfd = accept(sockfd, (struct sockaddr *) &cl_addr, &len);
  if (newsockfd < 0) {
    printf("Erro ao aceitar conexão!\n");
    exit(1);
  }

  inet_ntop(AF_INET, &(cl_addr.sin_addr), client, CLADDR_LEN);
  printf("Conectado com %s.\n", client);
}

void messageMachine() {
  char buffer[BUFFER_SIZE];
  pthread_t rThread;

  memset(buffer, 0, BUFFER_SIZE);
  printf("Digite uma mensagem por vez e aperte enter para enviar!\n");

  //creating a new thread for receiving messages from the client
  ret = pthread_create(&rThread, NULL, receiveMessage, (void *) newsockfd);
  if (ret) {
    printf("ERROR: Return Code from pthread_create() is %d\n", ret);
    exit(1);
  }

  while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
    sendMessage(buffer);
  }
}

void main() {
  createSocket();
  startServer();
  listenConnection();
  messageMachine();

  close(newsockfd);
  close(sockfd);

  pthread_exit(NULL);
  return;
}
