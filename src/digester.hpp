#ifndef SHA_DEMO_MESSAGE_DIGESTER_HPP_INCLUDED
#define SHA_DEMO_MESSAGE_DIGESTER_HPP_INCLUDED

#include <string>
#include <memory>
#include <iosfwd>

#include <openssl/evp.h>

namespace org {
    namespace sqg {
        namespace envelope {

            class digester {
            public:
                class context {
                private:
                    context(context const&);
                public:
                    context();

                    virtual ~context();

                    int size() const;

                    int block_size() const;

                    int type() const;

                    ::org::sqg::envelope::digester digester() const;

                    ::EVP_MD_CTX *_M_ctx;
                };
            public:

                /**
                 * construct an instance of digester.
                 *
                 * @param[in] md The message digester pointer.
                 */
                explicit digester(::EVP_MD const *md);

                /**
                 * construct an instance of digester.
                 *
                 * @param[in] name The message digester name.
                 */
                explicit digester(std::string const &name);

                digester(digester const&);

                virtual ~digester();

            public:
                std::string name() const;

                int type() const;

                int pkey_type() const;

                int size() const;

                int block_size() const;

                int nid() const;

                bool operator = (digester const&) const;

            public:
                static digester of(std::string const&);

            private:
                ::EVP_MD const *_M_md;
            };

            extern std::ostream& operator << (std::ostream&, digester const&);
        }
    }
}

#endif // SHA_DEMO_MESSAGE_DIGESTER_HPP_INCLUDED
