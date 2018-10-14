#include <ostream>
#include <vector> 

#include <openssl/engine.h>

#include "engine.hpp"

namespace org {
    namespace sqg {

        engine::engine(::ENGINE *engine) : _M_engine(engine) {}

        engine::engine(engine const &other) : _M_engine(other._M_engine) {}

        engine::~engine() { _M_engine = NULL; }

        std::string engine::name() const {
            return _M_engine ? ::ENGINE_get_name(_M_engine) : "<null>";
        }

        std::string engine::id() const {
            return _M_engine ? ::ENGINE_get_id(_M_engine) : "<null>";
        }

        ::ENGINE const* engine::native_engine() const { return _M_engine; }

        ::ENGINE* engine::native_engine() { return _M_engine; }

        bool engine::operator == (engine const &other) const {
            return _M_engine == other._M_engine;
        }

        std::vector<engine> engine::engines() {
            std::vector<engine> engines;
            for (::ENGINE *e = ::ENGINE_get_first(); e; e = ::ENGINE_get_next(e))
                engines.push_back(engine(e));
            return engines;
        }

        std::ostream& operator << (std::ostream &os, engine const &e) {
            return os << e.id() << ", " << e.name();
        }
    }
}
