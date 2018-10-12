#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>

#include <openssl/engine.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>

#include "../src/envvars.hpp"
#include "../src/utils.hpp"
#include "../src/bytes.hpp"
#include "../src/checksum.hpp"
#include "../src/sha.hpp"
#include "../src/hmac.hpp"
#include "../src/evp.hpp"

class engine {
public:
    explicit engine(::ENGINE *engine) : _M_engine(engine) {}

    engine(engine const &other) : _M_engine(other._M_engine) {}

    virtual ~engine() { _M_engine = NULL; }

    std::string name() const {
        return _M_engine ? ::ENGINE_get_name(_M_engine) : "<null>";
    }

    std::string id() const {
        return _M_engine ? ::ENGINE_get_id(_M_engine) : "<null>";
    }

    ::ENGINE* const native_engine() const { return _M_engine; }

    bool operator == (engine const &other) const {
        return _M_engine == other._M_engine;
    }

    static std::vector<engine> engines() {
        std::vector<engine> engines;
        for (::ENGINE *e = ::ENGINE_get_first(); e; e = ::ENGINE_get_next(e))
            engines.push_back(engine(e));
        return engines;
    }

    friend std::ostream &operator<<(std::ostream &, engine const &);
private:
    ::ENGINE *_M_engine;
};

std::ostream& operator << (std::ostream &os, engine const &e) {
    return os << e.id() << ", " << e.name();
}


static struct openssl_environment {

    openssl_environment() {
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

    virtual ~openssl_environment() {
#if defined(OPENSSL_API_COMPAT) && OPENSSL_API_COMPAT < 0x10100000L
        ENGINE_cleanup();
#endif
        EVP_cleanup();
        std::cout << "finalization" << std::endl;
    }
} env;

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace std::rel_ops;
    using namespace org::sqg;

    cout << "sizeof(evp) = " << sizeof(evp) << endl;
    cout << "sizeof(hmac) = " << sizeof(hmac) << endl;
    cout << "sizeof(sha) = " << sizeof(sha) << endl;
    cout << "sizeof(sha1) = " << sizeof(sha1) << endl;
    cout << "sizeof(sha224) = " << sizeof(sha224) << endl;
    cout << "sizeof(sha256) = " << sizeof(sha256) << endl;
    cout << "sizeof(sha384) = " << sizeof(sha384) << endl;
    cout << "sizeof(sha512) = " << sizeof(sha512) << endl;

    std::vector<engine> const &engines = engine::engines();
    for (std::vector<engine>::const_iterator it = engines.begin();
            it != engines.end(); ++it)
        cout << *it << endl;
    return EXIT_SUCCESS;
}
