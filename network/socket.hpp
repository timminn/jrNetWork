#ifndef SOCKET_H
#define SOCKET_H

#include "log.hpp"
#include "buffer.hpp"
#include <vector>
#include <memory>
#include <utility>
#include <cstring>
#include <cstdlib>

#ifdef __linux__
#include <fcntl.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#elif defined _WIN32
#endif

namespace jrNetWork {
    class IOModel;
    class EventDispatch;
    namespace TCP {
        class Socket {
        friend class jrNetWork::IOModel;
        friend class jrNetWork::EventDispatch;
        friend bool operator==(const TCP::Socket& lhs, const TCP::Socket& rhs);

        public:
            enum IO_MODE {IO_BLOCKING, IO_NONBLOCKING};

        private:
            using uint = unsigned int;

            /* ======== Unix/Windows ======== */
        private:
            IO_MODE blocking_flag;
            Buffer recv_buffer, send_buffer;

            /* ======== Unix ======== */
#ifdef __linux__
        private:
            int socket_fd;
            Socket(int fd, IO_MODE blocking_flag = IO_BLOCKING)  : blocking_flag(blocking_flag), socket_fd(fd){}
#elif defined _WIN32
#endif

        public:
            /* Create socket file description */
            Socket(IO_MODE blocking_flag = IO_BLOCKING);
            /* ========== Client socket API ========= */
            /* Connect to server */
            void connect(const std::string& ip, uint port); // connect BLOCKING
            void connect(const std::string& ip, uint port, uint timeout);   // connect NONBLOCKING
            /* ========== Server socket API ========= */
            /* Bind ip address and port */
            void bind(uint port);
            /* Listen target port */
            void listen(int backlog = 5);
            /* Accept client connection */
            std::shared_ptr<TCP::Socket> accept();
            /* ========== Shared API ========= */
            /* Close current connection */
            void disconnect();
            /* Receive data frome stream by length */
            std::pair<std::string, bool> recv(uint length);
            /* Write data to stream */
            bool send(std::string data);
            /* Determine whether the data has been sent
             * (the return value is only meaningful for non-blocking mode)
             */
            bool is_send_all() const;
            /* Get current socket's ip address */
            std::string get_ip_from_socket() const;
        };

        bool operator==(const TCP::Socket& lhs, const TCP::Socket& rhs);
        bool operator!=(const TCP::Socket& lhs, const TCP::Socket& rhs);
    }
}

#endif
