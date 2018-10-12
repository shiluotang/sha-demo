#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

#include <openssl/evp.h>
#include <openssl/engine.h>

#include "openssl_env.hpp"

namespace org {
    namespace sqg {

        openssl_env::openssl_env() {
                OpenSSL_add_all_algorithms();
                // OpenSSL_add_all_digests();
                // OpenSSL_add_all_ciphers();

                ENGINE_load_dynamic();
                ENGINE_load_rdrand();
                ENGINE_load_openssl();
                ENGINE_load_builtin_engines();
                ENGINE_register_all_complete();

                std::cout << "initialization" << std::endl;
            }

        openssl_env::~openssl_env() {
#if defined(OPENSSL_API_COMPAT) && OPENSSL_API_COMPAT < 0x10100000L
                ENGINE_cleanup();
#endif
                EVP_cleanup();
                std::cout << "finalization" << std::endl;
        }
    }
}
