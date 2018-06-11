#ifndef ENVVARS_HPP_INCLUDED
#define ENVVARS_HPP_INCLUDED

#include <cstdlib>
#include <string>

namespace org {
    namespace sqg {
        class envvars {
            public:
                static std::string var(std::string const&);
        };
    }
}

#endif // ENVVARS_HPP_INCLUDED
