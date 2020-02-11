/*wytalkD.c
 *Lucas Manker
 *COSC 3750 Spring 2020
 *4/1/20
 *Homework 7
 *
 *Basic chat application
*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 51100

int request_connection(char *hostname, int port);
int serve_socket(char *hostname, int port);
int accept_connection(int sockfd);

int main(int argc, char** argv){
    char hostbuffer [256];
    int sfd;
    int acc;
    gethostname(hostbuffer, sizeof(hostbuffer));
    sfd = serve_socket(hostbuffer, PORT);
    if(sfd == -1){
        return 1;
    }
    acc = accept_connection(sfd);
    if(acc == -1){
        return 1;
    }
    char buffer [1024];
    read(acc, buffer, sizeof(buffer));
    printf("%s", buffer);
    while(fgets(buffer, sizeof(buffer), stdin)!=NULL){
        int numread, numsent;
        numsent = send(acc, buffer, sizeof(buffer),0);
        if(numsent == -1){
            printf("error sending to socket\n");
            break;
        }
        numread = read(acc, buffer, sizeof(buffer));
        if(!numread){
            break;
        }
        printf("%s", buffer);
    }
    close(acc);
    return 0;
}

