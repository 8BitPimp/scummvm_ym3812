#include <cassert>
#include <cstdio>

#include "fmopl.h"
#include "../common/file.h"

extern "C" {
extern long SDL_GetTicks();
}

class rpihat_t : public ::OPL::RealOPL {
public:

    typedef unsigned char uint8_t;
    typedef unsigned int uint32_t;

    uint8_t chip_[256];
    ::Common::DumpFile dump_;

    rpihat_t()
        : dump_()
    {
        reset();
    }

    virtual ~rpihat_t() {
        if (dump_.isOpen()) {
            dump_.close();
        }
    }

    virtual bool init() {
        dump_.open("output.opl");
        return true;
    }

    virtual void reset() {
        memset(chip_, 0, sizeof(chip_));
    }

    // IO port write
    virtual void write(int a, int v) {
    }

    virtual byte read(int a) {
        return 0;
    }

    // register write
    virtual void writeReg(int r, int v) {
        const uint8_t adr = uint8_t(r);
        const uint8_t val = uint8_t(v);
        assert(r < sizeof(chip_));
        chip_[adr] = val;
        // 
        if (dump_.isOpen()) {
            const uint32_t tck = SDL_GetTicks();
            dump_.write(&tck, sizeof(tck));
            dump_.write(&adr, sizeof(adr));
            dump_.write(&val, sizeof(val));
        }
    }
};

namespace OPL {
namespace RPIHAT {
::OPL::OPL *create() {
    return new rpihat_t;
}
} // namespace RPIHAT
} // namespace OPL
