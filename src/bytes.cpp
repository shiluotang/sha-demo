#include <ostream>

#include "bytes.hpp"

namespace org {
    namespace sqg {

        bytes::bytes() { }

        bytes::bytes(void const *data, size_t size) :_M_data(data ? 0 : size) {
            if (data)
                std::copy(
                        reinterpret_cast<byte const*>(data),
                        reinterpret_cast<byte const*>(data) + size,
                        _M_data.begin());
        }

        void bytes::assign(void const *data, size_t size) {
            if (address() == data || size < 1)
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
    }
}
