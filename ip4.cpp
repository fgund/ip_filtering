#include "ip4.h"
//constexpr ip4::ip4() : data{{0} } {}
constexpr ip4::ip4(unsigned char const a, unsigned char const b,
              unsigned char const c, unsigned char const d):
        data{{a,b,c,d}} {}
ip4::ip4(std::string& str)
{
    std::stringstream sstr;
    sstr.str(str);
    sstr >> *this;
}

ip4::ip4(ip4 const & other) noexcept : data(other.data) {}

ip4& ip4::operator=(ip4 const & other) noexcept
{
    data = other.data;
    return *this;
}

std::string ip4::to_string() const
{
    std::stringstream sstr;
    sstr << *this;
    return sstr.str();
}


std::ostream& operator<<(std::ostream& os, const ip4& a)
{
    os << static_cast<int>(a.data[0]) << '.'
       << static_cast<int>(a.data[1]) << '.'
       << static_cast<int>(a.data[2]) << '.'
       << static_cast<int>(a.data[3]);
    return os;
}

std::istream& operator>>(std::istream& is, ip4& a)
{
    char d1, d2, d3;
    int b1, b2, b3, b4;
    is >> b1 >> d1 >> b2 >> d2 >> b3 >> d3 >> b4;
    auto is_dot = [](char c){ return (c == '.');};
    auto fits_char = [](int x){ return (x>=0)&&(x<=UCHAR_MAX);};
    if (is_dot(d1) && is_dot(d2) && is_dot(d3)
        && fits_char(b1) && fits_char(b2) && fits_char(b3) && fits_char(b4))
    {
        a = ip4(b1, b2, b3, b4);
    }
    else {
        is.setstate(std::ios_base::failbit);
        throw(std::exception("Wrong ip format string!"));
    }

    return is;
}