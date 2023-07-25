#ifndef _GRID_NET_TRANSPORT_H_
#define _GRID_NET_TRANSPORT_H_

#include <functional>
#include <memory>
#include <vector>

#include <grid/net/connection.h>

namespace grid {
    class ServerTransport {
    public:
        typedef std::function<void(std::shared_ptr<Connection> connection)> NewConnectionDelegate;

        virtual bool BindNetwork(uint16_t port, NewConnectionDelegate delegate) = 0;
        virtual void ReleaseNetwork() = 0;
    };
}; // namespace grid

#endif
