#include <stdexcept>

#include "evp.hpp"

namespace org {
    namespace sqg {

        evp::evp(::EVP_MD const *hasher, ::ENGINE *engine) {
            reset(hasher, engine);
        }

        evp::~evp() {}

        evp& evp::reset(::EVP_MD const *hasher, ENGINE *engine) {
            if (!EVP_DigestInit_ex(&_M_ctx._M_ctx, hasher, engine))
                throw std::runtime_error("EVP_DigestInit_ex failed!");
            return *this;
        }

        evp& evp::reset() { return reset(NULL, NULL); }

        evp& evp::update(void const *data, size_t size) {
            if (!EVP_DigestUpdate(&_M_ctx._M_ctx, data, size))
                throw std::runtime_error("EVP_DigestUpdate failed!");
            return *this;
        }

        evp& evp::update(bytes const &data) {
            return update(data.address(), data.size());
        }

        evp& evp::finish(bytes &data) {
            unsigned int len = 0;
            if (!EVP_DigestFinal_ex(&_M_ctx._M_ctx, &_M_md[0], &len))
                throw std::runtime_error("EVP_DigestFinal_ex failed!");
            data.assign(&_M_md[0], len);
            return *this;
        }
    }
}
