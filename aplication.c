#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 2000
#define TIME_SIZE 25
#define CONTENT_D_SIZE 10
#define SENDER_SIZE 50

typedef struct app_header {
  char sender[SENDER_SIZE];
  char message[BUF_SIZE];
  char date[TIME_SIZE];
  int content_length;
  char content_type[CONTENT_D_SIZE];
} app_header;

app_header header;

void send_message();

void get_current_date() {
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  char time_string[TIME_SIZE];
  strcpy(time_string, asctime(tm));
  int length = strlen(time_string);
  time_string[length - 1] = '\0';
  strcpy(header.date, time_string);
}

void verify_quit(char* text) {
  if (strlen(text) == 2 && text[0] == '\\' && text[1] == 'q') {
    printf("Quiting... OK\n");
    exit(0);
  }
}

void read_message() {
  char buffer[BUF_SIZE];
  printf("you: ");
  fgets(buffer, BUF_SIZE, stdin);
  int length = strlen(buffer);
  buffer[length - 1] = '\0';
  strcpy(header.message, buffer);
  verify_quit(header.message);
}

//parametro: ex: meuchat <ip> <porta> <tamanho> //validação
//definir regras de limitação de caractere e sintaxe: posso dizer q só aceita letra :)

void get_message_length() {
  int length = strlen(header.message);
  header.content_length = length;
}

void get_content_type() {
  strcpy(header.content_type, "plain/text");
}

void get_sender() {
  printf("%s\n", "Please, what's your name?");
  fgets(header.sender, SENDER_SIZE, stdin);
  int length = strlen(header.sender);
  header.sender[length - 1] = '\0';
  verify_quit(header.sender);
}

void mount_header() {
  read_message();
  get_current_date();
  get_message_length();
  get_content_type();
}

void print_header() {
  printf("\nSender: %s\n", header.sender);
  printf("Date: %s\n", header.date);
  printf("Message: %s\n", header.message);
  printf("Content-Length: %d\n", header.content_length);
  printf("Content-Type: %s\n", header.content_type);
}

void transformaTextoParaBinario() {
	//TODO
} 

void transformaBinarioEmTexto() {
	//TODO
} 

void enviarParaTransporte() {
	//aplicação solicita conexão
	//TODO
}

void receive_data(app_header received_header) {
  // TODO: This function receives data from server; - recebe de transporte
}

void start_app() {
  printf("%s\n", "Starting aplication module...");
  printf("%s\n\n", "Para sair, tecle '\\q'.");
  get_sender();
  printf("%s\n", "Now you can talk with someone...");

  while (1) {
    mount_header();
  }
}

//chat simples ??broadcast - determinar endereco
//tratamento de recebimento de pacotes. pode pedir reenvio de pacote não recebido
//definir tamanho máximo de pacote - pode ser variável baseado no meio físico (pode ser restritivo) - segmentação
//tvz udp não seja ideal. entrega-receber necessario. meios de conferir chegada dos pacotes.
//configuração: usuário coloca ip e porta de destino
//estabelecimento de conexão.
//cabeçalho camada de transporte.
//checksum - contar apenas 0 e 1. bit de paridade (decidir se em enlace-bit bit bit- ou transporte)