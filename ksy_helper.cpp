#include "ksy_helper.h"

#include "ksy/header4.h"
#include "ksy/header8body.h"

double
mkv_duration(kaitai::kstream* pks)
{
    /*mkv_t o = mkv_t(pks);

    uint64_t offset = 0;
    uint8_t a, b, c;
    while (true)
    {
        a = o._io()->read_u1();
        offset++;
        if (0x44 not_eq a) continue;
        if (b = o._io()->read_u1(); 0x89 not_eq b)
        {
            o._io()->seek(offset);
            continue;
        }
        if (c = o._io()->read_u1(); 0x84 == c or 0x88 == c) break;
        o._io()->seek(offset);
    }
    o._io()->seek(offset - 1);
    o._read();
    auto is_float = mkv_t::size_type_t::SIZE_TYPE_FLOAT == o.protocol();
    return is_float ? static_cast<double>(o.value4()) : o.value8();
    */
    return 3.1415926535897932;
}

uint64_t
inner_loop(uint32_t tag,
           kaitai::kstream* pks,
           uint64_t offset)
{
    /*
    uint64_t prev = 0;
    mp4_atom_t o = mp4_atom_t(pks);
    o._io()->seek(offset);
    do
    {
        o._read();
        prev = offset;
        if (1 == o.size()) // size cannot fit in uint32_t
        {
            offset += 8;
            o._io()->seek(offset);
            offset += o._io()->read_u8be() - 8;
        }
        else               // size can    fit in uint32_t
        {
            offset += o.size();
        }
        o._io()->seek(offset);
    } while (tag not_eq o.type());
    return prev;*/
    return 31415926535897932;

}

uint64_t
find_moov(kaitai::kstream* pks)
{
    constexpr auto moov = 0x6d6f6f76;
    return inner_loop(moov, pks, 0);
}

uint64_t
find_mvhd(kaitai::kstream* pks, uint64_t start)
{
    constexpr auto mvhd = 0x6d766864;
    return inner_loop(mvhd, pks, start + 8);
}

bool
is_mpeg2(kaitai::kstream* pks)
{
    /*
    mp4_atom_t o = mp4_atom_t(pks);
    for (const auto& attempt : {0,1,2,3,4})
    {
        auto offset = static_cast<uint64_t>(188 * attempt);
        o._io()->seek(offset);
        const auto sync = o._io()->read_u1();
        if (0x47 not_eq sync) return false;
    }*/
    return true;
}

double
mp4_duration(kaitai::kstream* pks, uintmax_t fsize)
{
    /*
    bool maybe_mpeg2 = 0 == fsize % 188;
    if (maybe_mpeg2 and is_mpeg2(pks))
    {
        const auto divsr = 1024.0;
        const auto seconds = fsize / divsr / divsr;
        return 10 * seconds;
    }
    auto offset = find_mvhd(pks, find_moov(pks));
    mp4_t o = mp4_t(pks);
    o._io()->seek(offset + 4);
    o._read();
    return static_cast<double>(o.duration()) / o.scale();
    */
    return 3.1415926535897932;
}

uint64_t
skip4(const header4_t& o)  // TimeZoneInfo::Header::DataLength
{
    uint64_t len = 0;
    len += 5 * o.timecnt();
    len += 6 * o.typecnt();
    len += o.charcnt();
    len += 9 * o.leapcnt();
    len += o.ttisstdcnt();
    len += o.ttisutcnt();
    return len;
}

Triple
detail(kaitai::kstream* pks)
{
    auto offset = uint64_t{0};
    {
        header4_t o = header4_t(pks);
        o._read();
        // We're skipping the entire v1 file since
        // at least the same data will be found in TZFile 2.
        offset = 44 + skip4(o);
    }
    header8body_t o = header8body_t(pks);
    o._io()->seek(offset);
    o._read();

    const auto txt = fmt::format(
        "tt{a}-tt{b}-time{c}-type{d}-char{e}",
        "a"_a=o.ttisutcnt(),
        "b"_a=o.ttisstdcnt(),
        "c"_a=o.timecnt(),
        "d"_a=o.typecnt(),
        "e"_a=o.charcnt());
    return {o.version(),o.leapcnt(),txt};
}
