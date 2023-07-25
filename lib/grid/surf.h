#ifndef _GRID_SURF_H_
#define _GRID_SURF_H_

#ifdef _WIN32
    #define _CRT_SECURE_NO_WARNINGS
#endif // _WIN32

#include <memory>
#include <string>
#include <vector>

// SURF - Standard Unique Resource Finder
/*
 * If the protocol is the same as the hostname it can be omitted.
 * With grid!domain.com the client will first try to connect to grid.domain.com and later try domain.com 
 * if the previous domain does not exists.
 * 
 * grid!domain.com:port/path?query#fragment
 * and
 * grid!grid.domain.com:port/path?query#fragment
 * are therefore the same.
 * 
 * Surf as individual parts:
 * scheme!host/path?query#fragment
 * 
 * Draft by Dylan Beattie, "The web that never was"
 */

namespace grid {
    /**
    * This class represents a Standard Unique Resource Finder (SURF),
    * as described above.
    */
    class Surf {
    public:
        /**
         * This is the default constructor
         */
        Surf();

        // Lifecycle management
        Surf(const Surf&) = delete;
        Surf(Surf&&) = delete;
        ~Surf();

        Surf &operator=(const Surf&) = delete;
        Surf &operator=(Surf&&) = delete;

        /**
         * This method builds the SURF from the elements parsed
         * from the given string rendering of a SURF.
         * 
         * @param[in] surfString
         *		This is the string rendering of the SURF to parse.
         * 
         * @return
         *		An indication of whether or not the SURF was
         *		parsed successfully is returned.
         */
        bool ParseFromString(const std::string &surfString);

        /**
         * This method returns the "scheme" element of the SURF.
         * 
         * @return
         *		The "scheme" element of the SURF is returned.
         * 
         * @retval ""
         *		This is returned if there is no "scheme" element in the SURF.
         */
        std::string GetScheme() const;

        /**
         * This method returns the "host" element of the SURF.
         * 
         * @return
         *		The "host" element of the SURF is returned.
         * 
         * @retval ""
         *		This is returned if there is no "host" element in the SURF.
         */
        std::string GetHost() const;

        /**
         * This method returns the "path" element of the SURF.
         * 
         * @note
         *		If the first step of the path is an empty string,
         *		then the SURF has an absolute path.
         * 
         * @return
         *		The "path" element of the SURF is returned.
         */
        std::string GetPath() const;

        /**
         * This method returns an indication of whether or not the
         * SURF includes a port number.
         * 
         * @return
         *      An indication of whether or not the
         *      SURF includes a port number is returned.
         */
        bool HasPort() const;

        /**
         * This method returns the port number element of the SURF,
         * if it has one.
         * 
         * @return
         *      The port number element of the SURF is returned.
         * 
         * @note
         *      The retuend port number is only valid if the
         *      HasPort method returns true.
         */
        uint16_t GetPort() const;
    private:
        /**
         * This is the type of structure that contains the private
         * properties of the instance. It is defined in the implementation
         * and declared here to ensure that it is scoped inside the class.
         */
        struct Impl;

        /**
         * This contains the private properties of the instance
         */
        std::unique_ptr<struct Impl> impl_;
    };
} // namespace grid

#endif // _GRID_SURF_H_
