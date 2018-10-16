#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <openssl/engine.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>

#include "../src/bytes.hpp"
#include "../src/checksum.hpp"
#include "../src/digester.hpp"
#include "../src/engine.hpp"
#include "../src/envvars.hpp"
#include "../src/evp.hpp"
#include "../src/hmac.hpp"
#include "../src/openssl_env.hpp"
#include "../src/sha.hpp"
#include "../src/utils.hpp"


namespace org {
	namespace sqg {

		template <typename Byte, typename Allocator = std::allocator<Byte> >
		class basic_bytes {
		public:
			typedef Byte byte;

			typedef std::vector<byte, Allocator> container;
			typedef typename container::iterator iterator;
			typedef typename container::const_iterator const_iterator;
		public:
			template <typename CharT>
			basic_bytes(CharT const *s)
				:_M_data(reinterpret_cast<byte const*>(s), reinterpret_cast<byte const*>(s + std::char_traits<CharT>::length(s)))
			{
			}

			basic_bytes(void const* data, std::size_t size)
				:_M_data(reinterpret_cast<byte const*>(data), reinterpret_cast<byte const*>(data) + size)
			{
			}

			virtual ~basic_bytes() {}

			void const* address() const { return &_M_data[0]; }

			void* address() { return &_M_data[0]; }

			const_iterator begin() const { return _M_data.begin(); }

			iterator begin() { return _M_data.begin(); }

			const_iterator end() const { return _M_data.end(); }

			iterator end() { return _M_data.end(); }

			std::size_t size() const { return _M_data.size(); }

			basic_bytes<Byte, Allocator>& assign(void const* data, std::size_t size) {
				_M_data.resize(size);
				std::copy_n(reinterpret_cast<byte const*>(data), size, &_M_data[0]);
				return *this;
			}

			int compare(basic_bytes<Byte, Allocator> const& other) const {
				size_t n = std::min(size(), other.size());
				int c = std::char_traits<Byte>::compare(&_M_data[0], &other._M_data[0], n);
				if (c == 0)
					return size() - other.size();
				return c;
			}

			basic_bytes<Byte, Allocator>& operator = (basic_bytes<Byte, Allocator> const &other) {
				return assign(other.address(), other.size());
			}

			bool operator < (basic_bytes<Byte, Allocator> const &other) const {
				return compare(other) < 0;
			}

			bool operator == (basic_bytes<Byte, Allocator> const &other) const {
				return compare(other) == 0;
			}

			template <typename CharT, typename Traits>
			std::basic_ostream<CharT, Traits>& print(std::basic_ostream<CharT, Traits> &os) const {
                basic_ios_guard<CharT> guarder(os);
				os << std::hex << std::uppercase << std::setfill(os.widen('0'));
				for (const_iterator it = begin(); it != end(); ++it)
					os << std::setw(2) << (static_cast<int>(*it) & 0xff);
				return os;
			}

			template <typename CharT, typename Traits>
			std::basic_istream<CharT, Traits>& read(std::basic_istream<CharT, Traits> &is) {
                typedef typename Allocator::template rebind<CharT>::other A;
				typedef std::basic_string<CharT, Traits, A> string;
				typedef std::basic_istringstream<CharT, Traits, A> istringstream;
				container c;

				string s;
				is >> s;
				unsigned short value;
				for (typename string::size_type i = 0, n = s.length() / 2; i < n ; ++i) {
					istringstream ss(s.substr(i * 2, 2));
					ss >> std::hex >> value;
					if (ss.fail())
						break;
					c.push_back(value & 0xff);
				}
				assign(c.size() > 0 ? &c[0] : NULL, c.size());
				return is;
			}
		private:
			container _M_data;
		};

		template <typename Byte, typename Allocator>
		std::ostream& operator << (std::ostream &os, basic_bytes<Byte, Allocator> const& b) {
			return b.print(os);
		}

		template <typename Byte, typename Allocator>
		std::wostream& operator << (std::wostream &os, basic_bytes<Byte, Allocator> const& b) {
			return b.print(os);
		}

		template <typename Byte, typename Allocator>
		std::istream& operator >> (std::istream &is, basic_bytes<Byte, Allocator> &b) {
			return b.read(is);
		}

		template <typename Byte, typename Allocator>
		std::wistream& operator >> (std::wistream &is, basic_bytes<Byte, Allocator> &b) {
			return b.read(is);
		}

		typedef basic_bytes<unsigned char> ubytes;
		typedef basic_bytes<signed char> sbytes;
		// typedef basic_bytes<char> bytes;
	}
}

static struct openssl_env_initial {
    openssl_env_initial() { static org::sqg::openssl_env initializer; }
} initialization;

int main(int argc, char* argv[]) try {
    using namespace std;
    using namespace std::rel_ops;
    using namespace org::sqg;
    using namespace org::sqg::envelope;

    std::vector<engine> const &engines = engine::engines();
    for (std::vector<engine>::const_iterator it = engines.begin();
            it != engines.end(); ++it)
        cout << *it << endl;

    cout << digester::of("SHA") << endl;
    cout << digester::of("SHA1") << endl;
    cout << digester::of("SHA224") << endl;
    cout << digester::of("SHA256") << endl;
    cout << digester::of("SHA384") << endl;
    cout << digester::of("SHA512") << endl;

    cout << digester::of("MDC2") << endl;
    cout << digester::of("MD4") << endl;
    cout << digester::of("MD5") << endl;
    cout << digester::of("DSA") << endl;
    cout << digester::of("RIPEMD160") << endl;

    basic_bytes<unsigned char> b = "Hello World!";
    cout << b << endl;

    stringstream ss("ABCDEFFF11223344");

    bytes bb("Hello");
    cout << bb << endl;
    ss >> b;
    cout << b << endl;

    return EXIT_SUCCESS;
} catch (std::exception const &e) {
    std::cerr << "[C++ exception] " << e.what() << std::endl;
    return EXIT_FAILURE;
} catch (...) {
    std::cerr << "[C++ exception] <UNKNOWN>" << std::endl;
    return EXIT_FAILURE;
}
