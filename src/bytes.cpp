#include <ostream>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <cstring>

#include "bytes.hpp"

namespace org {
    namespace sqg {

        bytes::bytes() { }

        bytes::bytes(void const *data, size_t size) :_M_data(data ? size : size_t(0)) {
            if (data)
                std::copy(
                        reinterpret_cast<byte const*>(data),
                        reinterpret_cast<byte const*>(data) + size,
                        _M_data.begin());
        }

        void bytes::assign(void const *data, size_t size) {
            if (address() == data)
                return;
            _M_data.resize(size);
            std::copy(
                    reinterpret_cast<byte const*>(data),
                    reinterpret_cast<byte const*>(data) + size,
                    _M_data.begin()
                    );
        }

        std::ostream& operator << (std::ostream &os, bytes const &data) {
            return data.print(os);
        }

        std::wostream& operator << (std::wostream &os, bytes const &data) {
            return data.print(os);
        }

        bool bytes::operator < (bytes const &other) const {
            if (this == &other)
                return false;
            int c = std::memcmp(address(), other.address(), std::min(size(), other.size()));
            return c == 0 ? size() < other.size() : c < 0;
        }

        bool bytes::operator == (bytes const &other) const {
            if (this == &other)
                return true;
            if (size() != other.size())
                return false;
            return std::memcmp(address(), other.address(), size()) == 0;
        }

        bytes bytes::from_hex(std::string const &hex) {
            if (hex.length() % 2 != 0)
                throw std::runtime_error("hex string length must be even!");
            int size = hex.length() / 2;
            int value = 0;
            std::vector<unsigned char> buffer(size);
            std::stringstream ss;
            ss << std::hex;
            for (int i = 0, n = hex.length(); !ss.fail() && i < n; i += 2) {
                ss.clear();
                ss << hex[i] << hex[i + 1];
                ss >> value;
                buffer[i / 2] = value & 0xff;
            }
            return bytes(&buffer[0], size);
        }

        bytes bytes::from_binary(std::string const &binary) {
        }
    }
}
