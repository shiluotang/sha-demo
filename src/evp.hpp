#ifndef EVP_HPP_INCLUDED
#define EVP_HPP_INCLUDED

#include <openssl/evp.h>

#include "bytes.hpp"
#include "checksum.hpp"

namespace org {
    namespace sqg {

        class evp: public checksum {
        private:
            struct context {
                ::EVP_MD_CTX _M_ctx;

                context() {
                    ::EVP_MD_CTX_init(&_M_ctx);
                }

                virtual ~context() {
                    // FIXME detect failure?
                    ::EVP_MD_CTX_cleanup(&_M_ctx);
                }
            };

        public:
            evp(std::string const&, ::ENGINE* = NULL);

            evp(::EVP_MD const*, ::ENGINE* = NULL);

            virtual ~evp();

            evp& reset(std::string const&, ::ENGINE* = NULL);

            evp& reset(EVP_MD const*, ::ENGINE* = NULL);

            evp& reset();

            evp& update(void const *data, size_t size);

            evp& update(bytes const &data);

            evp& finish(bytes &data);

        private:
            unsigned char _M_md[EVP_MAX_MD_SIZE];

            context _M_ctx;

            ::EVP_MD const *_M_md_type;
        };
    }
}

#endif // EVP_HPP_INCLUDED
