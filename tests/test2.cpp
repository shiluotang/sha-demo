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

class hmac {
    private:
        struct context {
            HMAC_CTX _M_ctx;

            context() { init(); }

            virtual ~context() { cleanup(); }

            void init() {
                HMAC_CTX_init(&_M_ctx);
            }

            void cleanup() {
                HMAC_CTX_cleanup(&_M_ctx);
            }
        };

    public:
        hmac(EVP_MD const* hasher, org::sqg::bytes const &key, ENGINE *engine = NULL)
        {
            reset(hasher, key, engine);
        }

        virtual ~hmac() {
        }

        void reset(EVP_MD const *hasher, org::sqg::bytes const &key, ENGINE *engine = NULL) {
            HMAC_Init_ex(&_M_ctx._M_ctx,
                    key.address(), key.size(),
                    hasher,
                    engine);
        }

        void reset() {
            HMAC_Init_ex(&_M_ctx._M_ctx, NULL, 0, NULL, NULL);
        }

        hmac& update(org::sqg::bytes const &data) {
            if (!HMAC_Update(&_M_ctx._M_ctx,
                    reinterpret_cast<unsigned char const*>(data.address()),
                    data.size()))
                throw std::runtime_error("hmac update failed!");
            return *this;
        }

        hmac& finish(org::sqg::bytes &value) {
            unsigned int len = 0;
            if (!HMAC_Final(&_M_ctx._M_ctx,
                    &_M_md[0],
                    &len))
                throw std::runtime_error("hmac final failed!");
            value.assign(&_M_md[0], len);
            return *this;
        }

    private:
        context _M_ctx;
        unsigned char _M_md[EVP_MAX_MD_SIZE];
};

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace org::sqg;

    bytes bb = bytes::from_hex("12345678");
    cout << "bb = " << bb << endl;

    return EXIT_SUCCESS;
}
