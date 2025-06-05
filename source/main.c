/*
** showip.c -- show IP addresses for a host given on the command line
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define OK 0

int main(int argc, char *argv[]) {
    struct addrinfo hints;
    struct addrinfo *result;
    struct addrinfo *ip_ptr;

    int status = OK;
    char ip[INET6_ADDRSTRLEN];

    if (argc != 2) {
        fprintf(stderr, "Wrong usage\n");
        return 1;
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(argv[1], NULL, &hints, &result);
    if (status != OK) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 1;
    }

    printf("IP addresses for %s:\n", argv[1]);
    size_t ip_counter = 0;
    for (ip_ptr = result; ip_ptr != NULL; ip_ptr = ip_ptr->ai_next) {
        void *addr;
        char *ip_version;

        if (ip_ptr->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *) ip_ptr->ai_addr;
            addr = &(ipv4->sin_addr);
            ip_version = "IPv4";
        }
        else if (ip_ptr->ai_family == AF_INET6) {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *) ip_ptr->ai_addr;
            addr = &(ipv6->sin6_addr);
            ip_version = "IPv6";
        }

        ip_counter++;

        inet_ntop(ip_ptr->ai_family, addr, ip, INET6_ADDRSTRLEN);
        printf("%lu. %s: %s\n", ip_counter, ip_version, ip);
    }

    freeaddrinfo(result);

    return 0;
}