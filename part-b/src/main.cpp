#include "tcp_server.h"

int main() {
    TCPServer server(9001);
    server.start();
    return 0;
}

