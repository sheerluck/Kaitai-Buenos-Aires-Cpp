meta:
  id: header8body
  endian: be
  license: WTF
  ks-version: 0.9

seq:

  - id: magic
    contents: [0x54, 0x5A, 0x69, 0x66]
  - id: version
    type: u1
  - id: reserved
    size: 15
  - id: ttisutcnt
    type: u4
  - id: ttisstdcnt
    type: u4
  - id: leapcnt
    type: u4
  - id: timecnt
    type: u4
  - id: typecnt
    type: u4
  - id: charcnt
    type: u4
  - id: unix_time
    type: s8
    repeat: expr
    repeat-expr: timecnt
  - id: type_index
    type: u1
    repeat: expr
    repeat-expr: timecnt
  - id: info
    type: intbb
    repeat: expr
    repeat-expr: typecnt

types:
  intbb:
    seq:
      - id: utc_offset
        type: u4
      - id: is_dst
        type: u1
      - id: abbr_index
        type: u1
