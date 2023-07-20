#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "TCP_SRV/tcp_srv.h"
#include <debug.h>
#include <string.h>
#include <getopt.h>

void client(SOCKET fd_s){
    char buf[1024] = {};
    int rc;
    write(fd_s, "hello too\n", 13);
    while ((rc = recv(fd_s, buf, sizeof(buf), 0) > 0))
    {
        print_info(" get %s\n", buf);
        // write(fd_s, "hello too\n", 13);
    }
    
}


typedef int (*stng_func_t)(SOCKET s);

SOCKET tcp_client( char *hname, char *sname, stng_func_t stng_fun)
{
    struct sockaddr_in peer;

    SOCKET s;

    set_addres( hname, sname, &peer, "tcp" );
    
    s = socket( AF_INET, SOCK_STREAM, 0 ) ;

    if ( !CHECK_SOCK( s ) ){
        print_error("error1\n");
    }

    stng_fun(s);

    if ( connect( s, ( struct sockaddr * )&peer,sizeof( peer ) ) ){
        print_error("error2\n");
    }

    return s;
}


// int stng_bf_sz(SOCKET s)
// {
//     if(setsockopt(s, SOL_SOCKET, SO_SNDBUF, ))
// }

int main(int argc, char* argv[])
{
   
    char *buff;
    SOCKET s;
    int blsk = 5000;
    int sndbufsz = 32*1024;
    int sndsz = 1440;

    int c = 0;

    while ((c = getopt(argc, argv, "s:b:c")) != EOF)
    {
        switch (c)
        {
        case 's':   {sndsz = atoi(optarg);} break;

        case 'b':   {sndbufsz = atoi(optarg);} break;

        case 'c':   {blsk = atoi(optarg);} break;
        
        default:    {print_info("??????\n");}  break;
        }

    }

    if(argc <= optind){
        print_error("[KLIENT] --- error input argumrnt\n");        
    }

    if((buff = (char*)malloc(sndsz)) == NULL){
        print_error("malloc error line - %d\n", __LINE__);
    }

    struct sockaddr_in peer;

    
    print_debug("%s %s\n",argv[optind], argv[optind+1] );

    set_addres( argv[optind], argv[optind+1], &peer, "tcp" );
    
    s = socket( AF_INET, SOCK_STREAM, 0 ) ;

    if ( !CHECK_SOCK( s ) ){
        print_error("error1\n");
    }

    if(setsockopt(s, SOL_SOCKET, SO_SNDBUF,(char*)&sndbufsz, sizeof(sndbufsz) )){
        print_error("error setsoketkorp\n");
        return 1;
    }
    

    if ( connect( s, ( struct sockaddr * )&peer,sizeof( peer ) ) ){
        print_error("error2\n");
        return 1;
    }


    while (blsk-- >0)
    {
        send(s, buff, sndsz, 0);
    }
    



    return 0;

    // s = tcp_client(argv[optind], argv[optind+1]);

    // while (fgets(packet.buf, sizeof(packet.buf), stdin) != NULL)
    // {
    //     n = strlen(packet.buf);
    //     packet.reclen = htonl(n);

    //     if(send(s, (char*)&packet, n + sizeof(packet.reclen), 0) < 0 ){
    //         print_error("error send\n");
    //     }
    // }
    
    
    

    return 0;
}




