#include "tcp_server.h"

TCPServer::TCPServer(int port) {
    struct sockaddr_in server_addr{};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, SOMAXCONN);

    epoll_fd = epoll_create1(0);
    struct epoll_event event{};
    event.events = EPOLLIN;
    event.data.fd = server_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event);
}

void TCPServer::start() {
    struct epoll_event events[MAX_EVENTS];

    std::cout << "Server listening on port 9001...\n";
    
    while (true) {
        int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        for (int i = 0; i < num_events; i++) {
            if (events[i].data.fd == server_fd) {
                int client_fd = accept(server_fd, nullptr, nullptr);
                struct epoll_event event{};
                event.events = EPOLLIN;
                event.data.fd = client_fd;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event);
            } else {
                handle_client(events[i].data.fd);
            }
        }
    }
}

void TCPServer::handle_client(int client_socket) {
    char buffer[1024];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytes_received <= 0) {
        close(client_socket);
        return;
    }

    buffer[bytes_received] = '\0';
    std::string request(buffer);
    std::vector<std::string> args = parse_resp2(request);

    std::string response;
    if (args.empty()) {
        response = "-ERR Invalid command\r\n";
    } else {
        std::string cmd = args[0];

        if (cmd == "SET" && args.size() == 3) {
            db.set(args[1], args[2]);
            response = "+OK\r\n";
        } else if (cmd == "GET" && args.size() == 2) {
            std::string value = db.get(args[1]);
            response = value.empty() ? "$-1\r\n" : "$" + std::to_string(value.size()) + "\r\n" + value + "\r\n";
        } else if (cmd == "DEL" && args.size() == 2) {
            db.del(args[1]);
            response = ":1\r\n";
        } else {
            response = "-ERR Unknown command\r\n";
        }
    }

    send(client_socket, response.c_str(), response.size(), 0);
}

