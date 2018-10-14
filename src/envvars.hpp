#ifndef SHA_DEMO_ENVVARS_HPP_INCLUDED
#define SHA_DEMO_ENVVARS_HPP_INCLUDED

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

#endif // SHA_DEMO_ENVVARS_HPP_INCLUDED
