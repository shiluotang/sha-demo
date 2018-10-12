#include <string>
#include <stdexcept>

#include "evp.hpp"

namespace org {
    namespace sqg {
        evp::evp(std::string const& digester, ::ENGINE *engine) :_M_md_type(NULL) {
            EVP_MD const* hasher = EVP_get_digestbyname(digester.c_str());
            _M_md_type = hasher;
            reset(hasher);
        }

        evp::evp(::EVP_MD const *hasher, ::ENGINE *engine) :_M_md_type(hasher) {
            reset(hasher, engine);
        }

        evp::~evp() {}

        evp& evp::reset(std::string const &digester, ENGINE *engine) {
            return reset(EVP_get_digestbyname(digester.c_str()), engine);
        }

        evp& evp::reset(::EVP_MD const *hasher, ENGINE *engine) {
            _M_md_type = hasher;
            if (!EVP_DigestInit_ex(&_M_ctx._M_ctx, _M_md_type, engine))
                throw std::runtime_error("EVP_DigestInit_ex failed!");
            return *this;
        }

        evp& evp::reset() { return reset(_M_md_type); }

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
