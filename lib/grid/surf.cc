#include <grid/surf.h>

#include <inttypes.h>
#include <stdio.h>

namespace grid {
    /**
     * This contains the private properties of a Surf instance.
     */
    struct Surf::Impl {
        /**
         * This is the "scheme" element of the SURF.
         */
        std::string scheme;

        /**
         * This is the "host" element of the SURF.
         */
        std::string host;

        /**
         * This flag indicates whether or not the
         * SURF includes a port number.
         */
        bool hasPort = false;

        /**
         * This is the port number element of the SURF.
         */
        uint16_t port = 0;

        /**
         * This is the "path" element of the SURF.
         */
        std::string path;
    };

    Surf::Surf() : impl_(new Impl) {}

    Surf::~Surf() = default;

    bool Surf::ParseFromString(const std::string &surfString) {
        // Parse scheme
        const auto schemaEnd = surfString.find('!');
        impl_->scheme = surfString.substr(0, schemaEnd);
        auto rest = surfString.substr(schemaEnd + 1);
        
        impl_->hasPort = false;

        // Parse host
        const auto authorityEnd = rest.find('/');
        if (authorityEnd == -1) {
            impl_->host = rest;
            return true;
        }

        const auto portDelimiter = rest.find(':');
        if (portDelimiter == std::string::npos) {
            impl_->host = rest.substr(0, authorityEnd);
        } else {
            impl_->host = rest.substr(0, portDelimiter);
            (void)sscanf(
                rest.substr(portDelimiter + 1, authorityEnd - portDelimiter - 1).c_str(),
                "%" SCNu16, &impl_->port);
            impl_->hasPort = true;
        }

        rest = rest.substr(authorityEnd);

        // Parse path
        impl_->path = rest;

        return true;
    }

    std::string Surf::GetScheme() const {
        return impl_->scheme;
    }

    std::string Surf::GetHost() const {
        return impl_->host;
    }

    std::string Surf::GetPath() const {
        return impl_->path;
    }

    bool Surf::HasPort() const {
        return impl_->hasPort;
    }

    uint16_t Surf::GetPort() const {
        return impl_->port;
    }
} // namespace grid
