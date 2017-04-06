// camada de transporte

//faz parte da pilha

//TCP não tem sistema de confirmação. Não é orientado à conexão.
//Não é pacote TCP, mas datagrama.
//tamanho do pacote de dados a ser transferido é menor. Cabeçalho tem 8 bytes.

    //Não existe acknowledge (confirmação de chegada de pacote).
    //Transmissor não espera esse envio para enviar próximo pacote.
#include <stdio.h>
#include <stdlib.h>

//estabelendo a porta desde o inicio
#define PORTA_INICIAL              1
#define PORTA_FINAL             7000
//transmissor
    typedef struct criaHeaderTCP {
        char sourcePort; //porta de origem (16 bits)
        char destinationPort; //porta de destino (16 bits)
        int calculaMessageLenght(); 
        int data; //dados que vem da camada de aplicação
    } transp_header;

    void conexao(destinationIP, destinationPort) {
        //TODO id da conexão -> identifica a conexão
    }

    void timeoutConexao() {
        //TODO
    }

    void escutaAplicacao() {
        //TODO
    }

    void confereVelocidadeRemetenteTransmissor() {
        //TODO
    }
    
    fragmentaMensagem() {
        //TODO
    }

    remontarMensagem() {
        //TODO
    }

    controleCongestionamento(){
        //TODO - origem regula sua velocidade
    }

    void conferePacoteTransmissor(enderecoIPOrigem, enderecoIPDestino) {
        enderecoIPOrigem; //32 bits - vem da camada de Redes
        enderecoIPDestino; //32 bits - vem da camada de Redes
        //?
        protocolo; //Protocolo IP: ? = TCP
        int calculaMessageLenght();
        //usa ponteiros pra colocar eles em camadas
    }

    int calculaMessageLenght() { //em bytes
        messageLenght = data.length + //cabeçalho TCP;
        return messageLenght;
    }

    void aguardaACK() {
        //TODO
        //pode estourar
    }

    void timeoutACK() {
        //TODO envia de novo
        //retransmissão: envia mensagem
    }

//receptor
    recebeHeaderTCP(datagrama) {
        sourcePort; //porta de origem (16 bits)
        destinationPort; //porta de destino (16 bits)
        messageLenght; //tamanho do datagrama (16 bits) = 8 + de dados
        data; //dados que vem da camada de aplicação
    }

    void enviaACK(datagrama) {
        //TODO
        //definir como identificar se é ACK != mensagem; não tem dados, só cabeçalho
    }    

    verificarDados(datagrama) {
         //TODO
    }

    void start_transp() {
        printf("%s\n", "Starting transport module..." );

    }

    voi main() {
        start_transp();
    }
    
