#ifndef SHA_DEMO_ENGINE_HPP_INCLUDED
#define SHA_DEMO_ENGINE_HPP_INCLUDED

#include <iosfwd>
#include <openssl/engine.h>

namespace org {
    namespace sqg {

        class engine {
        public:
            explicit engine(::ENGINE *engine);

            engine(engine const &other);

            virtual ~engine();

            std::string name() const;

            std::string id() const;

            ::ENGINE const* native_engine() const;

            ::ENGINE* native_engine();

            bool operator == (engine const &other) const;

            static std::vector<engine> engines();
        private:
            ::ENGINE *_M_engine;
        };

        extern std::ostream& operator << (std::ostream &os, engine const &e);
    }
}

#endif // SHA_DEMO_ENGINE_HPP_INCLUDED
