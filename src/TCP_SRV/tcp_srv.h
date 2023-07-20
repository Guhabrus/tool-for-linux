#ifndef _TCP_SERV_H
#define _TCP_SERV_H

#include <stdbool.h>
#include <netinet/in.h>

#define DOMEN       AF_INET
#define CHECK_SOCK(socket)  ((socket) >= 0)     ///< Проверка валидности сокета

#define NLISTEN 1
typedef int SOCKET;



typedef enum 
{
    SUCCES = 0, 
    ERR_UNKNOWN_HOST,       ///< Неизвестное имя хостя
    ERR_UNKNOWN_SERVER,      ///< Неизвестное имя сервера
    ERR_SET_SOCKET,
    ERR_SET_OPTION,
    ERR_BIND,
    ERR_LISTEN,
}server_error_t;

/**
 * @brief Заполнение сокета сервера
 * 
 * @param h_name [in] - имя хоста
 * @param s_name [in] - имя сервера 
 * @param protocol [in] - протокол обмена
 * @param sk_in [out] - протокол обмена
 * @return server_error_t - результат заполнения сокета
 */

server_error_t set_addres(char* h_name, char* s_name, struct sockaddr_in* sk_in, char* protocol);

/**
 * @brief 
 * 
 * @param fd_s [in] декриптор принятого сокета
 * @param rcvbufsz [in] размер принимающего буфера
 */
void server(SOCKET fd_s,int rcvbufsz);


/**
 * @brief Инициализация tcp сервера
 * 
 * @param hname[in] - имя хоста
 * @param sname[in] - имя сервера
 * @param fd_s[out]  - указатель на дескриптор сокета 
 * @return server_error_t 
 */
server_error_t tcp_server(char* hname, char* sname, SOCKET *fd_s);


/**
 * @brief Чтения N байт по указанному дескриптору сокета
 * 
 * @param fd [in] - указатель на файловый десткриптор сокета 
 * @param buf [out] - указатель на буфер для чтения
 * @param size [in] - размер который необходимо  прочитать
 * @return int [out] - размер прочитанный из сокета. Возвращает -1 в случае ошибки
 */
int readn(const SOCKET fd, const uint8_t* buf, const size_t size);

/**
 * @brief Чтения сообщения переменной длинны с первоначальным считыванием заголовка сообщения
 * 
 * @param fd [in] - указатель на файловый десткриптор сокета
 * @param buf [out] - указатель на буфер для чтения
 * @param size [in] - размер который необходимо  прочитать
 * @return int [out] - размер прочитанный из сокета. Возвращает -1 в случае ошибки
 */
int readrvec(const SOCKET fd, const uint8_t* buff, const size_t size);

#endif  /*_TCP_SERV_H*/