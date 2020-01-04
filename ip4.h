#ifndef IP4_H
#define IP4_H
#include <iostream>
#include <array>
#include <sstream>
#include <assert.h>

class ip4
{
    std::array<unsigned char, 4> data;
public:
    constexpr ip4() = delete;
    constexpr ip4(unsigned char const a, unsigned char const b,
                  unsigned char const c, unsigned char const d);
    ip4(std::string& str);

    ip4(ip4 const & other) noexcept;

    ip4& operator=(ip4 const & other) noexcept;

    std::string to_string() const;
    constexpr unsigned long to_ulong() const noexcept;


    friend bool operator==(ip4 const & a1, ip4 const & a2) noexcept;
    friend bool operator!=(ip4 const & a1, ip4 const & a2) noexcept;
    friend bool operator<(ip4 const & a1, ip4 const & a2) noexcept;
    friend bool operator>(ip4 const & a1, ip4 const & a2) noexcept;
    friend bool operator<=(ip4 const & a1, ip4 const & a2) noexcept;
    friend bool operator>=(ip4 const & a1, ip4 const & a2) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const ip4& a);

    friend std::istream& operator>>(std::istream& is, ip4& a);
};

#endif //IP4_H