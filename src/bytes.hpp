#ifndef BYTES_HPP_INCLUDED
#define BYTES_HPP_INCLUDED

#include <vector>
#include <iomanip>
#include <iosfwd>

#include "utils.hpp"

namespace org {
    namespace sqg {

        class bytes {
            private:
                typedef unsigned char byte;
            public:
                bytes();

                //bytes(bytes const &other) {
                //    assign(other);
                //}

                bytes(void const *data, size_t size);

                template <typename T, size_t N>
                explicit bytes(T (&a)[N]) :_M_data(sizeof(T) * N) {
                    std::copy(
                            reinterpret_cast<byte const*>(&a[0]),
                            reinterpret_cast<byte const*>(&a[0]) + sizeof(a[0]) * N,
                            _M_data.begin());
                }

                template <typename CharT>
                explicit bytes(std::basic_string<CharT> const &s)
                    :_M_data(sizeof(CharT) * s.length()) {
                    std::copy(
                            reinterpret_cast<byte const*>(&s[0]),
                            reinterpret_cast<byte const*>(&s[0]) + sizeof(CharT) * s.length(),
                            _M_data.begin());
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

#endif // BYTES_HPP_INCLUDED
