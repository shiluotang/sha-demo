#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <iterator>
#include <stdexcept>

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

class engine_iterator;
class engine {

    private:
        ENGINE *_M_engine;

    private:
        friend class engine_iterator;

    public:
        explicit engine(ENGINE *engine) :_M_engine(engine) {
        }

        engine(engine const &other) :_M_engine(other._M_engine) { }

        virtual ~engine() { _M_engine = NULL; }

        std::string name() const {
            return ENGINE_get_name(_M_engine);
        }

        std::string id() const {
            return ENGINE_get_id(_M_engine);
        }

        bool operator == (engine const &other) const {
            return _M_engine == other._M_engine;
        }

        friend std::ostream& operator << (std::ostream&, engine const&);
};

std::ostream& operator << (std::ostream &os, engine const &e) {
    return os << e.id() << ", " << e.name();
}

class engine_iterator: public std::iterator<std::forward_iterator_tag, engine> {
    private:
        engine _M_engine;
    public:
        explicit engine_iterator(engine e)
            :_M_engine(e) {
        }

        engine_iterator(engine_iterator const &other)
            :_M_engine(other._M_engine) {
        }

        virtual ~engine_iterator() {
        }

        engine_iterator& operator++() {
            _M_engine = engine(ENGINE_get_next(_M_engine._M_engine));
            return *this;
        }

        engine_iterator operator++(int) {
            engine_iterator copy(*this);
            this->operator++();
            return copy;
        }

        bool operator == (engine_iterator const &other) {
            return _M_engine == other._M_engine;
        }

        bool operator != (engine_iterator const &other) {
            return !(*this == other);
        }

        reference operator*() { return _M_engine; }

        pointer operator->() { return &_M_engine; }
};

class engine_provider {
    public:
        engine_iterator begin() {
            return engine_iterator(engine(ENGINE_get_first()));
        }

        engine_iterator end() {
            return engine_iterator(engine(ENGINE_get_last()));
        }
};

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace std::rel_ops;
    using namespace org::sqg;

    bytes const key(string("30.90.10.126"));
    bytes const data = bytes::from_hex("00330202004000000010B14204B0810C20431080E03020080A0216284096102184086210010D4A0858A1025840861021884000");
    bytes expected = bytes::from_binary("0011110001101110000001101001011111011100000110000100001110011100");

    bytes actual;

    evp evp(EVP_sha224());
    evp.reset().update(data).finish(actual);
    cout << "actual " << actual << endl;
    evp.reset().update(data).finish(actual);
    cout << "actual " << actual << endl;
    sha224 s;
    s.reset().update(data).finish(actual);
    cout << "actual " << actual << endl;

    hmac mac(EVP_sha256(), key);
    mac.update(data);
    mac.finish(actual);
    mac.reset(EVP_sha256(), key).update(data).finish(actual);

    bytes r(actual.address(), 64 / 8);
    if (r != expected)
        throw std::runtime_error("not equal!");

    cout << "expected " << expected << endl;
    cout << "  actual " << r << endl;

    return EXIT_SUCCESS;
}
