#include <grid/surf.h>

#include <iostream>

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
		 * This is the "path" element of the SURF,
		 * as a sequence of steps.
		 */
		std::vector<std::string> path;
	};

	Surf::Surf() : impl_(new Impl) {}

	Surf::~Surf() = default;

	bool Surf::ParseFromString(const std::string &surfString) {
		// Parse scheme
		const auto schemaEnd = surfString.find('!');
		impl_->scheme = surfString.substr(0, schemaEnd);
		auto rest = surfString.substr(schemaEnd + 1);

		// Parse host
		const auto authorityEnd = rest.find('/');
		impl_->host = rest.substr(0, authorityEnd);
		rest = rest.substr(authorityEnd);

		// Parse path
		// ""  -> []
		// "/" -> [""]
		// "foo/" -> ["foo", ""]
		// "/foo" -> ["", "foo"]
		impl_->path.clear();
		while (!rest.empty()) {
			auto pathDelimiter = rest.find('/');
			if (pathDelimiter == std::string::npos) {
				impl_->path.push_back(rest);
				break;
			} else {
				impl_->path.emplace_back(rest.begin(), rest.begin() + pathDelimiter);
				rest = rest.substr(pathDelimiter + 1);
			}
		}

		return true;
	}

	std::string Surf::GetScheme() const {
		return impl_->scheme;
	}

	std::string Surf::GetHost() const {
		return impl_->host;
	}

	std::vector<std::string> Surf::GetPath() const {
		return impl_->path;
	}
} // grid
