// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include <memory>
#include "header8body.h"
#include "kaitai/exceptions.h"

header8body_t::header8body_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, header8body_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_trans = nullptr;
}

void header8body_t::_read() {
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
    int l_trans = timecnt();
    m_trans = std::unique_ptr<std::vector<double>>(new std::vector<double>());
    m_trans->reserve(l_trans);
    for (int i = 0; i < l_trans; i++) {
        m_trans->push_back(std::move(m__io->read_f8be()));
    }
}

header8body_t::~header8body_t() {
}
