// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include <memory>
#include "header4.h"
#include "kaitai/exceptions.h"

header4_t::header4_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, header4_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
}

void header4_t::_read() {
    m_magic = m__io->read_bytes(4);
    if (!(magic() == std::string("\x54\x5A\x69\x66", 4))) {
        throw kaitai::validation_not_equal_error<std::string>(std::string("\x54\x5A\x69\x66", 4), magic(), _io(), std::string("/seq/0"));
    }
    m_version = m__io->read_u1();
    m_reserved = m__io->read_bytes(15);
    m_ttisutcnt = m__io->read_u4be();
    m_ttisstdcnt = m__io->read_u4be();
    m_leapcnt = m__io->read_u4be();
    m_timecnt = m__io->read_u4be();
    m_typecnt = m__io->read_u4be();
    m_charcnt = m__io->read_u4be();
}

header4_t::~header4_t() {
}
