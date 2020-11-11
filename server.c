#include <unistd.h> 
#include <stdio.h>
#include <math.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include "random.h"
#define PORT 8080 
#define LEVELS 12
#define MAX_BUFF 300
#define CLEAR() printf("\033[H\033[J")

const int run_me __attribute__((section(".RUN_ME")));

char * ans = "too_easy";

static char * rsp[LEVELS] = {"entendido\n", "itba\n", "M4GFKZ289aku\n", "fk3wfLCm3QvS\n", "too_easy\n", ".RUN_ME\n", "K5n2UFfpFMUN\n", "BUmyYq5XxXGt\n", "u^v\n", "chin_chu_lan_cha\n", "gdb_rules\n", "normal\n"};

static char * questions[LEVELS] = {"¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?",
"¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?", 
"¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por qué?", 
"¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿se puede utilizar read(2) y write(2) para operar?", 
"¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?", 
"Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?", 
"¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?", 
"¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?", 
"sockets es un mecanismo de IPC. ¿Qué es más eficiente entre sockets y pipes?", 
"¿Cuáles son las características del protocolo SCTP?", 
"¿Qué es un RFC?", 
"¿Fue divertido?"};

int level = 0;

void level1(){
    printf("Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n\nEn este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\nAdemás tendrán que investigar otras preguntas para responder durante la defensa.\nEl desafío final consiste en crear un programa que se comporte igual que yo, es decir, que provea los mismos desafíos y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta.\nAdemás, deberán implementar otro programa para comunicarse conmigo.\n\nDeberán estar atentos a los easter eggs.\n\nPara verificar que sus respuestas tienen el formato correcto respondan a este desafío con la palabra 'entendido\\n'\n");
}

void level2(){
    printf("The Wire S1E5\n5295 888 6288\n\n\n");
}

void level3(){
    printf("https://ibb.co/tc0Hb6w \n\n\n");

}

void level4(){
    printf("EBADF...\n\nwrite: Bad file descriptor\n\n");
    char * resp = "La respuesta es fk3wfLCm3QvS";
    write(13, resp, strlen(resp));
}

void level5(){
    printf("respuesta = strings:51\n");
}

void level6(){
    printf(".data .bss .comment ? .shstrtab .symtab .strtab\n");
}

void level7(){
    printf("Filter error\n\n");
    char * resp = "La respuesta es K5n2UFfpFMUN";
    int len = strlen(resp);
    for(int i=0;i<len;i++){
        write(1, resp+i, 1);
        for(int j=0;j<randInt(1, 6);j++){
            int c[2] = {0};
            c[0] = randInt(33, 125);
            write(2, c, 1);
        }
    }
    putchar('\n');
}

void level8(){
   
    printf("¿?\n\n\033[40;30mLa respuesta es BUmyYq5XxXGt\033[0m\n");

}

void level9(){
    printf("Latexme\n\nSi\n \\mathrm{d}y = u^v{\\cdot}(v'{\\cdot}\\ln{(u)}+v{\\cdot}\\frac{u'}{u})\nentonces\ny = \n");
}


void level10(){
    printf("quine\n\n");
    if(system("gcc quine.c -o quine") != 0){
        printf("ENTER para reintentar\n");
        return;
    }

    printf("¡Genial!, ya lograron meter un programa en quine.c, veamos si hace lo que corresponde.\n");

    if(system("./quine | diff - quine.c") != 0){
        printf("Encontro diferencias\n");
        printf("ENTER para reintentar\n");
    }
    else{
         printf("La respuesta es chin_chu_lan_cha\n");
    }

}

void gdbme(){
    if(getpid() == 0x12345678){
       printf("la respuesta es gdb_rules\n");
    }
}

void level11(){
    printf("b gdbme y encontrá el valor mágico\n\nENTER para reintentar.\n");
    gdbme();
}

void level12(){
    printf("Me conoces\n\n");
    double x, y, aux;;

    for(int i=0;i<1000;i++){
        x = randNormalize();
        y = randNormalize();
        aux = sqrt(-2 * log(x)) * cos(2*3.1416*y);
        printf("%.6f ", aux);
    }
    putchar('\n');
}

int main(int argc, char const *argv[]) 
{ 
    randomize();
    int server_fd, new_socket; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    level++; 

    //GAME
    char buff[MAX_BUFF] = {0};
    while(level <= LEVELS){
        CLEAR();
        printf("------------- DESAFIO -------------\n");
        switch(level){
            case 1: level1();
                    break;
            case 2: level2();
                    break;
            case 3: level3();
                    break;
            case 4: level4();
                    break;
            case 5: level5();
                    break;
            case 6: level6();
                    break;
            case 7: level7();
                    break;
            case 8: level8();
                    break;
            case 9: level9();
                     break;
            case 10: level10();
                    break;
            case 11: level11();
                    break;
            case 12: level12();
                    break;
            default:break;
            
        }
        printf("----- PREGUNTA PARA INVESTIGAR -----\n");
        printf("%s\n", questions[level-1]);
        memset(buff,0,MAX_BUFF);
        read(new_socket, buff, MAX_BUFF);
        if(strcmp(rsp[level-1], buff) != 0){
            printf("\nRespuesta incorrecta: %s\n", buff);
            sleep(1);
        }
        else{
            level++;
        }
    }
    
    return 0; 
}