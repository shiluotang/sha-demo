#ifndef SHA_DEMO_BYTES_HPP_INCLUDED
#define SHA_DEMO_BYTES_HPP_INCLUDED

#include <vector>
#include <iomanip>
#include <iosfwd>
#include <string>

#include "utils.hpp"

namespace org {
    namespace sqg {

        class bytes {
            private:
                typedef unsigned char byte;
            public:
                bytes();

                bytes(void const *data, size_t size);

                template <typename CharT>
                bytes(CharT const* s)
                    :_M_data(reinterpret_cast<byte const*>(s),
                            reinterpret_cast<byte const*>(s + std::char_traits<CharT>::length(s)))
                {
                }

                template <typename CharT>
                std::basic_ostream<CharT>& print(std::basic_ostream<CharT> &os) const {
                    basic_ios_guard<CharT> guard(os);
                    os << std::hex << std::uppercase << std::right;
                    for (std::vector<byte>::const_iterator it = _M_data.begin();
                            it != _M_data.end();
                            ++it)
                        os << std::setw(2) << std::setfill(os.widen('0'))
                            << static_cast<int>(*it & 0xff);
                    return os;
                }

                bytes& operator = (bytes const &other) {
                    assign(other);
                    return *this;
                }

                void* address() { return &_M_data[0]; }

                void const* address() const { return &_M_data[0]; }

                size_t size() const { return _M_data.size(); }

                void assign(void const *data, size_t size);

                template <typename T, size_t N>
                void assign(T (&a)[N]) {
                    assign(&a[0], sizeof(T) * N);
                }

                void assign(bytes const &data) {
                    assign(data.address(), data.size());
                }

                static bytes from_hex(std::string const&);

                static bytes from_binary(std::string const&);

                bool operator == (bytes const&) const;

                bool operator < (bytes const&) const;
            private:
                std::vector<byte> _M_data;
        };

        extern std::ostream& operator << (std::ostream&, bytes const&);

        extern std::wostream& operator << (std::wostream&, bytes const&);
    }
}

#endif // SHA_DEMO_BYTES_HPP_INCLUDED
