#ifndef SOCKET_H
#define SOCKET_H

#include "buffer.hpp"
#include <vector>
#include <memory>
#include <utility>
#include <cstring>
#include <cstdlib>

#include <fcntl.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

namespace jrNetWork {
    class EventDispatch;
    namespace TCP {
        class Socket {
        friend class jrNetWork::EventDispatch;
        friend bool operator==(const TCP::Socket& lhs, const TCP::Socket& rhs);

        public:
            enum Flag {BLOCKING, NONBLOCKING};

        private:
            using uint = unsigned int;

            /* ======== Unix/Windows ======== */
        private:
            Flag blocking_flag;
            Buffer buffer;

            /* ======== Unix ======== */
        private:
            int socket_fd;
            Socket(int fd, Flag blocking_flag = BLOCKING);

        public:
            /* Create socket file description */
            Socket(Flag blocking_flag = BLOCKING);
            /* ========== Client socket API ========= */
            /* Connect to server */
            void connect(const std::string& ip, uint port, uint timeout);
            /* ========== Server socket API ========= */
            /* Bind ip address and port */
            void bind(uint port);
            /* Listen target port */
            void listen(int backlog = 5);
            /* Accept client connection */
            std::shared_ptr<TCP::Socket> accept();
            /* ========== Shared API ========= */
            /* Close current socket */
            void close();
            /* Receive data frome stream by length */
            std::pair<std::string, bool> recv(uint length);
            /* Write data to stream */
            bool send(std::string data);
            /* Get current socket's ip address */
            std::string get_ip_from_socket() const;

        public:
            Socket(const TCP::Socket& s);
            Socket(TCP::Socket&& s);
            TCP::Socket& operator=(const TCP::Socket& s);
            TCP::Socket& operator=(TCP::Socket&& s);
        };

        bool operator==(const TCP::Socket& lhs, const TCP::Socket& rhs);
        bool operator!=(const TCP::Socket& lhs, const TCP::Socket& rhs);
    }
}

#endif