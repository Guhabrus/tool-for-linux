#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <errno.h>
#include <debug.h>
#include <string.h>
#include "tcp_srv.h"
#define set_errno(error_value) (errno = (error_value))

int readn(const SOCKET fd, const uint8_t* buf, const size_t size)
{
    int cnt = size;
    int rc = 0;

    while (cnt > 0)
    {
        rc = recv(fd, (void*)buf, cnt, 0 );

        if(rc < 0){
            if(errno == EINTR){ ///< Если не удучное чтение было из за сигнала 
                continue;
            }
            return -1;
        }

        if(rc == 0){
            return size-cnt;
        }
        buf  += rc;
        cnt -= rc;
    }
    return size;
}

int readrvec(const SOCKET fd, const uint8_t* buff, size_t size)
{
    u_int32_t reclen;    ///< Длинна тела сообщения

    int rc = readn(fd, (uint8_t*)&reclen,sizeof(reclen) );

    if(rc != sizeof(reclen)){
        return rc < 0 ? -1 : 0;
    }

    reclen = ntohl(reclen);

    if(reclen > size){

        while (reclen > 0)
        {
            rc = readn(fd, buff, size);

            if(rc != (int)size){
                return rc < 0 ? -1: 0;
            }

            reclen -= size;

            if(reclen < size){
                size = reclen;
            }
        }

        set_errno(EMSGSIZE);
        return -1;
    }

    rc = readn(fd, buff, reclen);

    if(rc != (int)reclen){
        return rc < 0 ? -1:0;
    }

    return rc;

    
}

server_error_t set_addres(char* h_name, char* s_name, struct sockaddr_in* sk_in, char* protocol)
{
    bzero(sk_in, sizeof(*sk_in));

    struct hostent *hp;
    struct servent *sp;
    sk_in->sin_family = DOMEN;

    if(h_name)
    {
        if(! inet_aton(h_name, &sk_in->sin_addr))
        {
            if(NULL == (hp = gethostbyname(h_name)) ){
                print_error("[TCP_SRV] --- неизвестный хост %s\n", h_name);
                return ERR_UNKNOWN_HOST;
            }

            sk_in->sin_addr = *(struct in_addr*)hp->h_addr_list;
        }
    }
    else{        ///< Если не указанно имя хоста то слушаем все
        sk_in->sin_addr.s_addr = htonl(INADDR_ANY);
    }

    char *end_ptr;
    short port = strtol(s_name, &end_ptr, 0);

    if(*end_ptr == '\0'){
        sk_in->sin_port = htons(port);
    }
    else{
        if( NULL == (sp = getservbyname(s_name, protocol))){
            print_error("[TCP_SRV] --- неизвестное имя сервера %s\n", s_name);
            return ERR_UNKNOWN_SERVER;
        }

        sk_in->sin_port = port;
    }

    return SUCCES;   
}



// void server(SOCKET fd_s,struct sockaddr_in *peerp){
//     if(NULL == peerp){
//         print_debug("sacsacqsa\n");
//         return; 
//     }

//     uint8_t buf[10];
//     int res = 0;

//     while (1)
//     {
//         res = readrvec(fd_s, buf, sizeof(buf));
    
//         if(res < 0){
//             print_debug(" readvrec  завершилась с ошибкой\n");
            
//         }
//         else if(res == 0){
//             print_debug("клиент отключился\n");
//             return;
//         } 
//         else{
//             // send( fd_s, "hello, world\n", 13, 0);
//             print_debug("data = %s\n", (char*)buf );
//         }  
        
//         bzero(buf, sizeof(buf));
//     }
    
// }

void server(SOCKET fd_s,int rcvbufsz){
 
    char *buf;
    int res = 0;

    if((buf = (char*)malloc(rcvbufsz)) == NULL){
       return; 
    }

    while (1)
    {
        res = recv(fd_s, buf, rcvbufsz, 0);
    
        if(res < 0){
            print_debug(" readvrec  завершилась с ошибкой\n");
            goto exit;
        }
        else if(res == 0){
            print_debug("клиент отключился\n");
            goto exit;
        } 
        else{
            // send( fd_s, "hello, world\n", 13, 0);
            print_debug("data = %s\n", buf );
        }  
        
    }

    exit:
        if(buf!=NULL){
            free(buf);
            return;
        }
}


server_error_t tcp_server(char* hname, char* sname, SOCKET *fd_socket)
{
    struct sockaddr_in local;

    const int value_option = 1;

    int res = set_addres(hname, sname, &local, "tcp");
    print_debug("port = %d ip = %d\n", local.sin_port, local.sin_addr.s_addr );
    #define fd_s (*fd_socket)

    if(res){
        print_error("[USER] --- error fill socket %d\n", res);
        return 1;
    }

    fd_s = socket(AF_INET, SOCK_STREAM, 0);

    if(!CHECK_SOCK(fd_s)){
        print_error("[USER] --- ошибка создания сокета\n");
        return ERR_SET_SOCKET;
    }


    if(setsockopt(fd_s, SOL_SOCKET, SO_REUSEADDR, &value_option, sizeof(value_option) ))
    {
        print_error("[USER] --- ошибка задания опций\n");
        return ERR_SET_OPTION;
    }
	
    if(bind(fd_s, (struct sockaddr*)&local, sizeof(local) )){
        print_error("[USER] --- ошибка bind\n");
        return ERR_BIND;
    }

    if(listen(fd_s, NLISTEN) ){
        print_error("[USER] --- ошибка listen\n");
        return ERR_LISTEN;
    }

    return SUCCES;
}