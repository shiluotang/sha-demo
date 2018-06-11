#ifndef SHA_HPP_INCLUDED
#define SHA_HPP_INCLUDED

#include <cstddef>
#include <stdexcept>

#include <openssl/sha.h>

#include "bytes.hpp"
#include "checksum.hpp"

namespace org {
    namespace sqg {

        template <typename context>
        class sha_base: public checksum {
            private:
                context _M_ctx;
            public:
                sha_base() { }
                virtual ~sha_base() { }

                virtual sha_base& reset() {
                    if (!_M_ctx.init()) throw std::runtime_error("init failed!");
                    return *this;
                }

                virtual sha_base& update(void const *data, size_t n) {
                    if (!_M_ctx.update(data, n))
                        throw std::runtime_error("update failed!");
                    return *this;
                }

                virtual sha_base& update(bytes const &data) {
                    if (!_M_ctx.update(data.address(), data.size()))
                        throw std::runtime_error("update failed!");
                    return *this;
                }

                virtual sha_base& finish(bytes &data) {
                    unsigned char md[context::DIGEST_SIZE];
                    if (!_M_ctx.finish(&md[0]))
                        throw std::runtime_error("final failed!");
                    data.assign(md);
                    return *this;
                }
        };

#define DEFINE_SHA_CONTEXT(TYPE, DIGEST_LENGTH, CTX, FUNCS) \
    struct TYPE { \
        static const int DIGEST_SIZE = DIGEST_LENGTH; \
        CTX _M_ctx; \
        bool init() { return FUNCS##_Init(&_M_ctx); } \
        bool update(void const *data, size_t n) { return FUNCS##_Update(&_M_ctx, data, n); } \
        bool finish(unsigned char *md) { return FUNCS##_Final(md, &_M_ctx); } \
    };

        DEFINE_SHA_CONTEXT(sha_context,    SHA_DIGEST_LENGTH,    SHA_CTX,    SHA)
        DEFINE_SHA_CONTEXT(sha1_context,   SHA_DIGEST_LENGTH,    SHA_CTX,    SHA1)
        DEFINE_SHA_CONTEXT(sha224_context, SHA224_DIGEST_LENGTH, SHA256_CTX, SHA224)
        DEFINE_SHA_CONTEXT(sha256_context, SHA256_DIGEST_LENGTH, SHA256_CTX, SHA256)
        DEFINE_SHA_CONTEXT(sha384_context, SHA384_DIGEST_LENGTH, SHA512_CTX, SHA384)
        DEFINE_SHA_CONTEXT(sha512_context, SHA512_DIGEST_LENGTH, SHA512_CTX, SHA512)

        class sha    : public sha_base<sha_context   > {};
        class sha1   : public sha_base<sha1_context  > {};
        class sha224 : public sha_base<sha224_context> {};
        class sha256 : public sha_base<sha256_context> {};
        class sha384 : public sha_base<sha384_context> {};
        class sha512 : public sha_base<sha512_context> {};
    }
}

#endif // SHA_HPP_INCLUDED
