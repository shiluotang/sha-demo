#include <cstdlib>
#include <cstdio>
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
#include "../src/digester.hpp"
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

int main(int argc, char* argv[]) try {
    using namespace std;
    using namespace std::rel_ops;
    using namespace org::sqg;
    using namespace org::sqg::envelope;

    std::vector<engine> const &engines = engine::engines();
    for (std::vector<engine>::const_iterator it = engines.begin();
            it != engines.end(); ++it)
        cout << *it << endl;

    cout << digester::of("SHA") << endl;
    cout << digester::of("SHA1") << endl;
    cout << digester::of("SHA224") << endl;
    cout << digester::of("SHA256") << endl;
    cout << digester::of("SHA384") << endl;
    cout << digester::of("SHA512") << endl;

    cout << digester::of("MDC2") << endl;
    cout << digester::of("MD4") << endl;
    cout << digester::of("MD5") << endl;
    cout << digester::of("DSA") << endl;
    cout << digester::of("RIPEMD160") << endl;

    return EXIT_SUCCESS;
} catch (std::exception const &e) {
    std::cerr << "[C++ exception] " << e.what() << std::endl;
    return EXIT_FAILURE;
} catch (...) {
    std::cerr << "[C++ exception] <UNKNOWN>" << std::endl;
    return EXIT_FAILURE;
}
