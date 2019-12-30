#pragma once

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <memory>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class header8body_t : public kaitai::kstruct {

public:

    header8body_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = nullptr, header8body_t* p__root = nullptr);
    void _read();
    ~header8body_t();

private:
    std::string m_magic;
    uint8_t m_version;
    std::string m_reserved;
    uint32_t m_ttisutcnt;
    uint32_t m_ttisstdcnt;
    uint32_t m_leapcnt;
    uint32_t m_timecnt;
    uint32_t m_typecnt;
    uint32_t m_charcnt;
    std::unique_ptr<std::vector<double>> m_trans;
    header8body_t* m__root;
    kaitai::kstruct* m__parent;

public:
    std::string magic() const { return m_magic; }
    uint8_t version() const { return m_version; }
    std::string reserved() const { return m_reserved; }
    uint32_t ttisutcnt() const { return m_ttisutcnt; }
    uint32_t ttisstdcnt() const { return m_ttisstdcnt; }
    uint32_t leapcnt() const { return m_leapcnt; }
    uint32_t timecnt() const { return m_timecnt; }
    uint32_t typecnt() const { return m_typecnt; }
    uint32_t charcnt() const { return m_charcnt; }
    std::vector<double>* trans() const { return m_trans.get(); }
    header8body_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};