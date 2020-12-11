#include <string.h>    // memset ...
#include <unistd.h>    // sockaddr_in, read, write ...
#include <arpa/inet.h> // htonl, htons, INADDR_ANY, sockaddr)in ...
#include <iostream>
#include <sys/socket.h>

#define PORT 7290 // I set this number as a port but it didn't applied so i had to find the port this server use.

void error_handler(char const *message, char const *num = 0);

int main()
{
    int serv_sock;
    int cli_sock;

    // sockaddr_in은 소켓 주소의 틀을 만들어주는 구조체로 AF_INET일 때 씀(ip protocol)
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    socklen_t cli_addr_size;

    std::cout << "execute" << std::endl;

    // create a socket for TCP, IPv4 domain
    serv_sock = socket(AF_INET, SOCK_STREAM, 0); // ip주소, tcp type, default tcp protocol
    if (serv_sock == -1)
        error_handler("socket error", "0");

    // set IP, port after clear address
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = PORT;

    // binding socket and server IP
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 1)
        error_handler("bind error", "0");

    // create 5 connection queue
    if (listen(serv_sock, 5) == -1)
        error_handler("listen error");
    else
        error_handler("listening at", "7290");

    // accept connection request from client
    cli_addr_size = sizeof(cli_addr);
    cli_sock = accept(serv_sock, (struct sockaddr *)&cli_addr, &cli_addr_size);
    if (cli_sock == -1)
        error_handler("accept error", "0");

    // send data
    char msg[] = "Hello this is server!\n";
    write(cli_sock, msg, sizeof(msg));

    close(cli_sock);
    close(serv_sock);

    std::cout << "exit" << std::endl;

    return 0;
}

void error_handler(char const *mes, char const *num)
{
    const char *s;
    if (num == 0)
    {
        s = "";
        std::cout << mes
                  << s
                  << std::endl;
        _exit(1);
    }
    else
    {
        s = num;
        std::cout << mes
                  << s
                  << std::endl;
    };
}