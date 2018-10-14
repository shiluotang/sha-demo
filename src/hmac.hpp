#ifndef SHA_DEMO_HMAC_HPP_INCLUDED
#define SHA_DEMO_HMAC_HPP_INCLUDED

#include <openssl/hmac.h>

#include "bytes.hpp"
#include "checksum.hpp"

namespace org {
    namespace sqg {

        class hmac: public checksum {
            private:
                struct context {
                    context() { init(); }

                    virtual ~context() { cleanup(); }

                    void init() {
                        ::HMAC_CTX_init(&_M_ctx);
                    }

                    void cleanup() {
                        ::HMAC_CTX_cleanup(&_M_ctx);
                    }

                    ::HMAC_CTX _M_ctx;
                };

            public:
                hmac(::EVP_MD const*, bytes const&, ::ENGINE* = NULL);

                virtual ~hmac();

                hmac& reset(::EVP_MD const*, bytes const&, ::ENGINE* = NULL);

                hmac& reset();

                hmac& update(void const* data, size_t size);

                hmac& update(bytes const &data);

                hmac& finish(bytes &value);

            private:
                unsigned char _M_md[EVP_MAX_MD_SIZE];
                context _M_ctx;
        };
    }
}

#endif // SHA_DEMO_HMAC_HPP_INCLUDED
