#include <stdexcept>

#include <openssl/evp.h>

#include "bytes.hpp"
#include "signer.hpp"

namespace org {
    namespace sqg {
        namespace envelope {

            signer::signer(digester const &d) :_M_digester(d) { }

            signer::~signer() {}

            signer& signer::init(key const &k) {
                return *this;
            }

            signer& signer::update(void const *data, std::size_t size) {
                if (!::EVP_DigestSignUpdate(_M_context._M_ctx, data, size))
                    throw std::runtime_error("EVP_DigestSignUpdate ailed!");
                return *this;
            }

            signer& signer::update(bytes const &b) {
                if (!::EVP_DigestSignUpdate(_M_context._M_ctx, b.address(), b.size()))
                    throw std::runtime_error("EVP_DigestSignUpdate failed!!!");
                return *this;
            }

            signer& signer::finish(bytes &b) {
                unsigned char md[EVP_MAX_MD_SIZE] = {0};
                size_t size = sizeof(md);

                if (!::EVP_DigestSignFinal(_M_context._M_ctx, &md[0], &size))
                    throw std::runtime_error("EVP_DigestSignFinal failed!!!");
                b.assign(&md, size);
                return *this;
            }
        }
    }
}
