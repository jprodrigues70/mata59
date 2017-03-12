// camada de transporte

//faz parte da pilha

//UDP não tem sistema de confirmação. Não é orientado à conexão.
//Não é pacote UDP, mas datagrama.
//tamanho do pacote de dados a ser transferido é menor. Cabeçalho tem 8 bytes.

    //Não existe acknowledge (confirmação de chegada de pacote).
    //Transmissor não espera esse envio para enviar próximo pacote.
#include <stdio.h>
#include <stdlib.h>
//include de socket
#include <sys/types.h>
#include <sys/sockets.h>
#include <netinet/in.h>
#include <netdb.h>

//estabelendo a porta desde o inicio
#define PORTA_INICIAL              1
#define PORTA_FINAL             7000
//transmissor
    typedef struct criaHeaderUDP {
        char sourcePort; //porta de origem (16 bits)
        char destinationPort; //porta de destino (16 bits)
        int calculaMessageLenght(); //tamanho do datagrama (16 bits) = 8 + de dados
        int criaChecksumTransmissor(); //(16 bits)
        int data; //dados que vem da camada de aplicação
    } transp_header;

    criaChecksumTransmissor(enderecoIPOrigem, enderecoIPDestino) {
        enderecoIPOrigem; //32 bits - vem da camada de Redes
        enderecoIPDestino; //32 bits - vem da camada de Redes
        zeros; //8 zeros
        protocolo; //Protocolo IP: 17 = UDP
        int calculaMessageLenght();
        //usa ponteiros pra colocar eles em camadas até formar checksum
        return checksum;
    }

    int calculaMessageLenght() { //em bytes
        messageLenght = data.length + 8; //dadosAplicacao.length + cabeçalho é 8bytes
        return messageLenght;
    }

//receptor
    recebeHeaderUDP(datagrama) {
        sourcePort; //porta de origem (16 bits)
        destinationPort; //porta de destino (16 bits)
        messageLenght; //tamanho do datagrama (16 bits) = 8 + de dados
        checksum; //(16 bits)
        data; //dados que vem da camada de aplicação
    }

    criaChecksumReceptor() {
        enderecoIPOrigem; //32 bits - vem da camada de Redes
        enderecoIPDestino; //32 bits - vem da camada de Redes
        zeros; //8 zeros
        protocolo; //Protocolo IP: 17 = UDP
        criaHeaderUDP.messageLenght;
        //usa ponteiros pra colocar eles em camadas até formar checksum
        return checksum;
    }

    calculaComplementoDe1Checksum() {
        /*
         * The width of the CRC calculation and result.
         * Modify the typedef for a 16 or 32-bit CRC standard.
         */
        typedef uint8_t crc;

        #define WIDTH  (8 * sizeof(crc))
        #define TOPBIT (1 << (WIDTH - 1))

        crc
        crcSlow(uint8_t const message[], int nBytes) {
            crc  remainder = 0;
            /*
             * Perform modulo-2 division, a byte at a time.
             */
            for (int byte = 0; byte < nBytes; ++byte){
                /*
                 * Bring the next byte into the remainder.
                 */
                remainder ^= (message[byte] << (WIDTH - 8));
                /*
                 * Perform modulo-2 division, a bit at a time.
                 */
                for (uint8_t bit = 8; bit > 0; --bit) {
                    /*
                     * Try to divide the current data bit.
                     */
                    if (remainder & TOPBIT){
                        remainder = (remainder << 1) ^ POLYNOMIAL;
                    }
                    else{
                        remainder = (remainder << 1);
                    }
                }
            }
            /*
             * The final remainder is the CRC result.
             */
            return (remainder);
        }   /* crcSlow() */
    }

    verificaChecksum(checksum) {
        // soma de verificação
        calculaComplementoDe1();
        //compara com o resultado transmitido
        if (criaChecksumTransmissor.enderecoIPDestino != criaChecksumReceptor.enderecoIPOrigem) {
            return 0;
        } if(criaChecksumTransmissor.checksum) {
            return 1;
        }
        return 0;
    }

    verificarDados(datagrama) {
         if (verificaChecksum(checksum) == 1) {
            ordena_diagramas_recebidos;
         } else {
            //o q faz quando verifica e tá errado?
            return 0;
         }
    }

    void start_transp() {
        printf("%s\n", "Starting transport module..." );

    }

    voi main() {
        start_transp();
    }
    
