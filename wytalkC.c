/*wytalkC.c
 *Lucas Manker
 *COSC 3750 Spring 2020
 *4/1/20
 *Homework 7
 *
 *Basic chat application
*/

#include <stdio.h>
#include <unistd.h>
#define PORT 51100

int request_connection(char *hostname, int port);
ssize_t send(int sockfd, const void *buf, size_t len, int flags);

int main(int argc, char** argv){
    int req;
    if(argc == 2){
        req = request_connection(argv[1], PORT);
        if(req != 3){
            printf("could not connect to %s\n", argv[1]);
            return 1;
        }
    }
    else{
        printf("wytalkC: enter exactly one hostname\n");
        return 1;
    }
    char buffer [1024];
    while(fgets(buffer, sizeof(buffer), stdin)!= NULL){
        int numread, numsent;
        numsent = send(req, buffer, sizeof(buffer),0);
        if(numsent == -1){
            printf("error sending to socket\n");
            break;
        }
        numread = read(req, buffer, sizeof(buffer));
        if(!numread){
            break;
        }
        printf("%s", buffer);
    }
    close(req);
    return 0;
}
