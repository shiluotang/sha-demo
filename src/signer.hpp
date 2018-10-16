#ifndef SHA_DEMO_SIGNER_HPP_INCLUDED
#define SHA_DEMO_SIGNER_HPP_INCLUDED

#include "checksum.hpp"
#include "digester.hpp"

namespace org {
    namespace sqg {
        namespace envelope {

            class key;
            class signer : org::sqg::checksum {
            public:
                explicit signer(digester const&);

                virtual ~signer();

                virtual signer& init(key const&);

                virtual signer& update(void const*, std::size_t);

                virtual signer& update(org::sqg::bytes const&);

                virtual signer& finish(org::sqg::bytes&);
            private:
                digester _M_digester;

                digester::context _M_context;
            };
        }
    }
}

#endif // SHA_DEMO_SIGNER_HPP_INCLUDED
