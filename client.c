#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 
#define MAX_BUFF 300
   
int main(int argc, char const *argv[]) 
{ 
    int sock = 0; 
    struct sockaddr_in serv_addr; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    char buff[MAX_BUFF];
    int index = 0;
    while(strcmp(buff, "quit") != 0){
        index = 0;
        while((buff[index++]=getchar()) != '\n' && index < MAX_BUFF){
            if(index>=MAX_BUFF){
                printf("The message is too long\n");

            }
            else{
                buff[--index]=0; 
                write(sock,buff, index+1);
            }
        }
        
    }
  
    return 0; 
} 