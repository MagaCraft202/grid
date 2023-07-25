#ifndef _GRID_NET_CONNECTION_H_
#define _GRID_NET_CONNECTION_H_

#include <functional>
#include <memory>
#include <vector>

namespace grid {
    /**
     * This represents a single connection between a GRID server and
     * a GRID client on a transport layer.
     */
    class Connection {
    public:
        typedef std::function<void(std::vector<uint8_t> data)> DataReveivedDelegate;
        typedef std::function<void()> BrokenDelegate;

        virtual void SetDataReceivedDelegate(DataReveivedDelegate delegate) = 0;
        virtual void SetBrokenDelegate(BrokenDelegate delegate) = 0;
        virtual void SendData(std::vector<uint8_t> data) = 0;
        virtual void Break(bool clean) = 0;
    };
} // namespace grid

#endif // _GRID_NET_CONNECTION_H_
