#include <grid/net/server.h>

#include <set>

namespace {
    /**
     * This structure holds onto all state information the server has
     * about a single connection from a client.
     */
    struct ConnectionState {
        /**
         * This is the transport interface of the connection.
         */
        std::shared_ptr<grid::Connection> connection;

        /**
         * This buffer is used to reassemble fragmented GRID requests
         * received from the client.
         */
        std::string reassemblyBuffer; 
    };
}

namespace grid {
    struct Server::Impl {
        /**
         * This is the currently bound transport layer.
         */
        std::shared_ptr<ServerTransport> transport;

        /**
         * These are the currently active client connections.
         */
        std::set<std::shared_ptr<ConnectionState>> activeConnections;

        /**
         * This method is called when new data is received from a connection.
         * 
         * @param[in] connectionState
         *      This is the state of the connection from which data was received.
         * 
         * @param[in] data
         *      This is a copy of the data received.
         */
        void DataReceived(std::shared_ptr<ConnectionState> connectionState, std::vector<uint8_t> data) {
            connectionState->reassemblyBuffer += std::string(data.begin(), data.end());
        }

        /**
         * This method is called when a new connection has been
         * established to the server.
         * 
         * @param[in] connection
         *      This is the new connection which has been established to the server.
         */
        void NewConnection(std::shared_ptr<Connection> connection) {
            const auto connectionState = std::make_shared<ConnectionState>();
            connectionState->connection = connection;
            (void)activeConnections.insert(connectionState);
            std::weak_ptr<ConnectionState> weakConnectionState(connectionState);
            connection->SetDataReceivedDelegate([this, weakConnectionState](std::vector<uint8_t> data) {
                const auto connectionState = weakConnectionState.lock();
                if (connectionState == nullptr) {
                    return;
                }

                DataReceived(connectionState, data);
            });
        }
    };

    Server::Server() : impl_(new Impl) {}

    Server::~Server() {
        Stop();
    }

    bool Server::Start(std::shared_ptr<ServerTransport> transport, uint16_t port) {
        impl_->transport = transport;
        if (!impl_->transport->BindNetwork(port, [this](std::shared_ptr<Connection> connection) {
            impl_->NewConnection(connection);
        })) {
            impl_->transport = nullptr;
            return false;
        }

        return true;
    }

    void Server::Stop() {
        if (impl_->transport != nullptr) {
            impl_->transport->ReleaseNetwork();
            impl_->transport = nullptr;
        }
    }
} // namespace grid
