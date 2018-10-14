#include <stdexcept>
#include <ostream>

#include "digester.hpp"

namespace org {
    namespace sqg {
        namespace envelope {

            digester::context::context()
                :_M_ctx(::EVP_MD_CTX_create())
            {
                if (!_M_ctx)
                    throw std::runtime_error("Failed to create context");
            }

            digester::context::~context() {
                _M_ctx = NULL;
            }

            int digester::context::size() const {
                return EVP_MD_CTX_size(_M_ctx);
            }

            int digester::context::block_size() const {
                return EVP_MD_CTX_block_size(_M_ctx);
            }

            int digester::context::type() const {
                return EVP_MD_CTX_type(_M_ctx);
            }

            digester digester::context::digester() const {
                return ::org::sqg::envelope::digester(::EVP_MD_CTX_md(_M_ctx));
            }

            digester::digester(::EVP_MD const *md)
                : _M_md(md) {
            }

            digester::digester(std::string const &name)
                : _M_md(EVP_get_digestbyname(name.c_str())) {
                if (!_M_md)
                    throw std::runtime_error("No digester for name " + name);
            }

            digester::digester(digester const &other)
                :_M_md(other._M_md) {
            }

            digester::~digester() { _M_md = NULL; }

            std::string digester::name() const {
                return EVP_MD_name(_M_md);
            }

            int digester::type() const {
                return EVP_MD_type(_M_md);
            }

            int digester::pkey_type() const {
                return EVP_MD_pkey_type(_M_md);
            }

            int digester::size() const {
                return EVP_MD_size(_M_md);
            }

            int digester::block_size() const {
                return EVP_MD_block_size(_M_md);
            }

            int digester::nid() const {
                return EVP_MD_nid(_M_md);
            }

            bool digester::operator = (digester const &other) const {
                return _M_md == other._M_md;
            }

            digester digester::of(std::string const& name) {
                return digester(name);
            }

            std::ostream& operator << (std::ostream &os, digester const &digester) {
                return os << digester.name();
            }
        }
    }
}
