#include <stdexcept>

#include "envvars.hpp"

namespace org {
    namespace sqg {

        std::string envvars::var(std::string const &name) {
            char const *p = std::getenv(name.c_str());
            if (!p)
                throw std::runtime_error("No environment variable \"" + name + "\"");
            return p;
        }
    }
}
