#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")  // Linkear la librería de sockets en Windows
    typedef int socklen_t;  // En Windows, socklen_t no está definido
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

#define PORT 5005

enum Position {
    BOTTOM,
    DOWN_MID,
    MID,
    TOP_MID,
    TOP
};

enum Position getCurrentPosition(int sockfd, struct sockaddr_in *cliaddr, socklen_t *len) {
    char buffer[1024];
    int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)cliaddr, len);
    if (n < 0) {
        perror("Error en recvfrom");
        exit(1);
    }
    buffer[n] = '\0';  // Asegurarse de que el buffer esté terminado en null

    // Convertir el buffer a un número entero
    int posY = atoi(buffer);

    enum Position position;

    if (posY >= 700)
        position = BOTTOM;
    else if (posY >= 400)
        position = TOP_MID;
    else if (posY >= 300)
        position = DOWN_MID;
    else if (posY >= 200)
        position = MID;
    else if (posY >= 100)
        position = TOP_MID;
    else
        position = TOP;

    return position;
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
#endif

    // Crear socket UDP
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error en socket");
        exit(1);
    }

    // Configurar servidor UDP
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Asociar socket
    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("Error en bind");
        exit(1);
    }

    printf("Esperando datos de MediaPipe...\n");

    while (1) {
        enum Position position = getCurrentPosition(sockfd, &cliaddr, &len);
        switch(position) {
        case BOTTOM:
            printf("bottom\n");
            break;
        case DOWN_MID:
            printf("down_mid\n");
            break;
        case MID:
            printf("mid\n");
            break;
        case TOP_MID:
            printf("top_mid\n");
            break;
        case TOP:
            printf("top\n");
            break;
        }
#ifdef _WIN32
        closesocket(sockfd);
        WSACleanup();
#else
        close(sockfd);
#endif
    }



    return 0;
} // gcc controlxDedos.c -o servidor.exe -lws2_32