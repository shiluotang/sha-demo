#include <stdexcept>

#include "hmac.hpp"

namespace org {
    namespace sqg {
        hmac::hmac(EVP_MD const* hasher, bytes const &key, ENGINE *engine) {
            reset(hasher, key, engine);
        }

        hmac::~hmac() { }

        hmac& hmac::reset(EVP_MD const *hasher, bytes const &key,
                ENGINE *engine) {
            ::HMAC_Init_ex(&_M_ctx._M_ctx,
                    key.address(), key.size(),
                    hasher,
                    engine);
            return *this;
        }

        hmac& hmac::reset() {
            ::HMAC_Init_ex(&_M_ctx._M_ctx, NULL, 0, NULL, NULL);
            return *this;
        }

        hmac& hmac::update(void const *data, size_t size) {
            if (!::HMAC_Update(&_M_ctx._M_ctx,
                    reinterpret_cast<unsigned char const*>(data),
                    size))
                throw std::runtime_error("hmac update failed!");
            return *this;
        }

        hmac& hmac::update(bytes const &data) {
            return update(data.address(), data.size());
        }

        hmac& hmac::finish(bytes &value) {
            unsigned int len = 0;
            if (!::HMAC_Final(&_M_ctx._M_ctx,
                    &_M_md[0],
                    &len))
                throw std::runtime_error("hmac final failed!");
            value.assign(&_M_md[0], len);
            return *this;
        }
    }
}
