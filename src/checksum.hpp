#ifndef SHA_DEMO_CHECKSUM_HPP_INCLUDED
#define SHA_DEMO_CHECKSUM_HPP_INCLUDED

namespace org {
    namespace sqg {

        class bytes;
        class checksum {
            public:
                virtual ~checksum() {};
                virtual checksum& reset() = 0;
                virtual checksum& update(void const*, size_t) = 0;
                virtual checksum& update(bytes const&) = 0;
                virtual checksum& finish(bytes&) = 0;
        };

    }
}

#endif // SHA_DEMO_CHECKSUM_HPP_INCLUDED
