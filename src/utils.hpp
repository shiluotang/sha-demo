#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <ios>

namespace org {
    namespace sqg {

        template <typename CharT>
        struct basic_ios_guard {

            typedef std::basic_ios<CharT> xios;
            typedef CharT char_type;

            basic_ios_guard(xios &stream)
                : _M_stream(stream)
                  , _M_flags(stream.flags())
                  , _M_fillchar(stream.fill())
                  , _M_width(stream.width())
                  , _M_precision(stream.precision())
            {
            }

            ~basic_ios_guard() {
                _M_stream.flags(_M_flags);
                _M_stream.fill(_M_fillchar);
                _M_stream.width(_M_width);
                _M_stream.precision(_M_precision);
            }

            xios &_M_stream;
            typename xios::fmtflags  _M_flags;
            typename xios::char_type _M_fillchar;
            std::streamsize _M_width;
            std::streamsize _M_precision;
        };

        typedef basic_ios_guard<char> ios_guard;
        typedef basic_ios_guard<wchar_t> wios_guard;
    }
}

#endif // UTILS_HPP_INCLUDED
