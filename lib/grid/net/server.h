#ifndef _GRID_NET_SERVER_H_
#define _GRID_NET_SERVER_H_

#include <memory>
#include <string>

#include <grid/net/transport.h>

namespace grid {
    class Server {
    public:
        /**
         * This is the default constructor
         */
        Server();

        // Lifecycle management
        Server(const Server&) = delete;
        Server(Server&&) = delete;
        ~Server();

        Server &operator=(const Server&) = delete;
        Server &operator=(Server&&) = delete;

        bool Start(std::shared_ptr<ServerTransport> transport, uint16_t port);
        void Stop();
    private:
        struct Impl;

        std::unique_ptr<struct Impl> impl_;
    };
} // namespace grid

#endif
