// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include <memory>
#include "header8body.h"
#include "kaitai/exceptions.h"

header8body_t::header8body_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, header8body_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_unix_time = nullptr;
    m_type_index = nullptr;
    m_info = nullptr;
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
    int l_unix_time = timecnt();
    m_unix_time = std::unique_ptr<std::vector<int64_t>>(new std::vector<int64_t>());
    m_unix_time->reserve(l_unix_time);
    for (int i = 0; i < l_unix_time; i++) {
        m_unix_time->push_back(std::move(m__io->read_s8be()));
    }
    int l_type_index = timecnt();
    m_type_index = std::unique_ptr<std::vector<uint8_t>>(new std::vector<uint8_t>());
    m_type_index->reserve(l_type_index);
    for (int i = 0; i < l_type_index; i++) {
        m_type_index->push_back(std::move(m__io->read_u1()));
    }
    int l_info = typecnt();
    m_info = std::unique_ptr<std::vector<std::unique_ptr<intbb_t>>>(new std::vector<std::unique_ptr<intbb_t>>());
    m_info->reserve(l_info);
    for (int i = 0; i < l_info; i++) {
        std::unique_ptr<intbb_t> _t_info = std::unique_ptr<intbb_t>(new intbb_t(m__io, this, m__root));
        _t_info->_read();
        m_info->push_back(std::move(_t_info));
    }
}

header8body_t::~header8body_t() {
}

header8body_t::intbb_t::intbb_t(kaitai::kstream* p__io, header8body_t* p__parent, header8body_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
}

void header8body_t::intbb_t::_read() {
    m_utc_offset = m__io->read_u4be();
    m_is_dst = m__io->read_u1();
    m_abbr_index = m__io->read_u1();
}

header8body_t::intbb_t::~intbb_t() {
}
