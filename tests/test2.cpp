#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <openssl/engine.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>

#include "../src/bytes.hpp"
#include "../src/checksum.hpp"
#include "../src/engine.hpp"
#include "../src/envvars.hpp"
#include "../src/evp.hpp"
#include "../src/hmac.hpp"
#include "../src/openssl_env.hpp"
#include "../src/sha.hpp"
#include "../src/utils.hpp"

static struct openssl_env_initial {
    openssl_env_initial() { static org::sqg::openssl_env initializer; }
} initialization;

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
