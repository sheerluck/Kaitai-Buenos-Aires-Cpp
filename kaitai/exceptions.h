#ifndef KAITAI_EXCEPTIONS_H
#define KAITAI_EXCEPTIONS_H

#include <kaitai/kaitaistream.h>

#include <string>
#include <stdexcept>

// We need to use "noexcept" in virtual destructor of our exceptions
// subclasses. Different compilers have different ideas on how to
// achieve that: C++98 compilers prefer `throw()`, C++11 and later
// use `noexcept`. We define KS_NOEXCEPT macro for that.

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1900)
#define KS_NOEXCEPT noexcept
#else
#define KS_NOEXCEPT throw()
#endif

namespace kaitai {

/**
 * Common ancestor for all error originating from Kaitai Struct usage.
 * Stores KSY source path, pointing to an element supposedly guilty of
 * an error.
 */
class kstruct_error: public std::runtime_error {
public:
    kstruct_error(const std::string what, const std::string src_path):
        std::runtime_error(src_path + ": " + what),
        m_src_path(src_path)
    {
    }

    virtual ~kstruct_error() KS_NOEXCEPT {};

protected:
    const std::string m_src_path;
};

/**
 * Error that occurs when default endianness should be decided with
 * a switch, but nothing matches (although using endianness expression
 * implies that there should be some positive result).
 */
class undecided_endianness_error: public kstruct_error {
public:
    undecided_endianness_error(const std::string src_path):
        kstruct_error("unable to decide on endianness for a type", src_path)
    {
    }

    virtual ~undecided_endianness_error() KS_NOEXCEPT {};
};

/**
 * Common ancestor for all validation failures. Stores pointer to
 * KaitaiStream IO object which was involved in an error.
 */
class validation_failed_error: public kstruct_error {
public:
    validation_failed_error(const std::string what, const kstream* io, const std::string src_path):
        kstruct_error(std::string("at pos ") + /*std::to_string(io->pos())*/ + ": validation failed:" + what, src_path),
        m_io(io)
    {
    }

// "at pos #{io.pos}: validation failed: #{msg}"

    virtual ~validation_failed_error() KS_NOEXCEPT {};

protected:
    const kstream* m_io;
};

/**
 * Signals validation failure: we required "actual" value to be equal to
 * "expected", but it turned out that it's not.
*/
template<typename T>
class validation_not_equal_error: public validation_failed_error {
public:
    validation_not_equal_error<T>(const T& expected, const T& actual, const kstream* io, const std::string src_path):
        validation_failed_error("not equal", io, src_path),
        m_expected(expected),
        m_actual(actual)
    {
    }

    // "not equal, expected #{expected.inspect}, but got #{actual.inspect}"

    virtual ~validation_not_equal_error<T>() KS_NOEXCEPT {};

protected:
    const T& m_expected;
    const T& m_actual;
};

}

#endif
