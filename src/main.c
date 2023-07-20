#include <stdio.h>
#include <stdint.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "TCP_SRV/tcp_srv.h"
#include <debug.h>


int main(int argc, char* argv[])
{

    char* hname;
    char* sname;
    struct sockaddr_in peer;
    

    if(argc == 2){
        hname = NULL;
        sname = argv[1];
    }
    else{
        hname = argv[1];
        sname = argv[2];
    }

    SOCKET fd_s;

    tcp_server(hname, sname, &fd_s);

    SOCKET fd_sin;
    uint32_t peer_len;

    int rcvbufsz = 32*1024;
    


    do
    {   
        
        peer_len = sizeof(peer);
        fd_sin = accept(fd_s,(struct sockaddr*)&peer, &peer_len );
        print_info("%d is connected\n", peer.sin_addr.s_addr);
        
        if(! CHECK_SOCK(fd_sin) ){
            print_error("[USER] --- Кривой дескриптор принятого сокета, я пожалуй все\n");
            return 1;
        }


        server(fd_sin, &peer);

        if(close(fd_sin) ){
            print_error("[USER] --- Не могу закрыть сокет\n");
            return 1;
        }
    } while (1);
    
  
  
  return 0;
}




