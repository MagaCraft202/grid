#ifndef _GRID_SURF_H_
#define _GRID_SURF_H_

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
         * This method returns the "path" element of the SURF,
         * as a sequence of steps.
         * 
         * @note
         *		If the first step of the path is an empty string,
         *		then the SURF has an absolute path.
         * 
         * @return
         *		The "path" element of the SURF is returned,
         *		as a sequence of steps.
         */
        std::vector<std::string> GetPath() const;
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
