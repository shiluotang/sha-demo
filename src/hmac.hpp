#ifndef HMAC_HPP_INCLUDED
#define HMAC_HPP_INCLUDED

#include <openssl/hmac.h>

#include "bytes.hpp"
#include "checksum.hpp"

namespace org {
    namespace sqg {

        class hmac: public checksum {
            private:
                struct context {
                    HMAC_CTX _M_ctx;

                    context() { init(); }

                    virtual ~context() { cleanup(); }

                    void init() {
                        ::HMAC_CTX_init(&_M_ctx);
                    }

                    void cleanup() {
                        ::HMAC_CTX_cleanup(&_M_ctx);
                    }
                };

            public:
                hmac(EVP_MD const*, bytes const&, ENGINE* = NULL);

                virtual ~hmac();

                hmac& reset(EVP_MD const*, bytes const&, ENGINE* = NULL);

                hmac& reset();

                hmac& update(void const* data, size_t size);

                hmac& update(bytes const &data);

                hmac& finish(bytes &value);

            private:
                context _M_ctx;
                unsigned char _M_md[EVP_MAX_MD_SIZE];
        };
    }
}

#endif // HMAC_HPP_INCLUDED
