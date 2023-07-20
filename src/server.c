#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "include/addr.h"

int main()
{
    struct sockaddr_in peer = {
        .sin_family       = DOMEN,
        .sin_port         = htons(PORT),
        .sin_addr.s_addr  = inet_addr(IP)
    };

    char buf[1];

    SOCKET fd_s = socket(DOMEN,SOCKET_TYPE, 0 );

    if(-1 >= fd_s){
        fprintf(stderr, "[SERVER] --- error create socket\n");
        return 1;
    }

    if(-1 >= bind(fd_s, (struct sockaddr*)&peer, sizeof(peer))){
        fprintf(stderr,"\r[SERVER] --- bind error\n");
        return 1;
    }

    if(-1 >= listen(fd_s, 5)){
        fprintf(stderr,"\r[SERVER] --- listen error\n");
        return 1;
    }

    fprintf(stdout,"\r[SERVER] --- listen succes \n");
    SOCKET fd_s_in = accept(fd_s, NULL, NULL );

    if(-1 >= fd_s_in){
        fprintf(stderr,"\r[SERVER] --- accept error\n");
        return 1;
    }

    int rec = recv(fd_s_in, buf, 1,0);

    if(-1 >= rec){
        fprintf(stderr,"\r[SERVER] --- receive error\n");
        return 1;
    }

    printf("\r[SERVER] --- get = %d\n", buf[0]);

    // rec = send(fd_s_in, "2", 1, 0);
    rec = write(fd_s_in, "2", 1);

    if(-1 >= rec){
        fprintf(stderr,"\r[SERVER] --- send error\nd");
        return 1;
    }

    return 0;
}