#include "ip4.h"

ip4::ip4(unsigned char const a, unsigned char const b,
                   unsigned char const c, unsigned char const d):
        data{{a,b,c,d}} {}
ip4::ip4(std::string_view str)
{
    std::stringstream sstr;
    sstr.str(str.data());
    sstr >> *this;
}

ip4::ip4(ip4 const & other) noexcept : data(other.data) {}
ip4::ip4(ip4 && other) noexcept
{
    data.swap(other.data);
}

ip4& ip4::operator=(ip4 const & other) noexcept
{
    data = other.data;
    return *this;
}

ip4& ip4::operator=(ip4 && other) noexcept
{
    data.swap(other.data);
    return *this;
}

std::string ip4::to_string() const
{
    std::stringstream sstr;
    sstr << *this;
    return sstr.str();
}

constexpr unsigned long ip4::to_ulong() const noexcept
{
    return
            (static_cast<unsigned long>(data[0]) << 24) |
            (static_cast<unsigned long>(data[1]) << 16) |
            (static_cast<unsigned long>(data[2]) << 8) |
            static_cast<unsigned long>(data[3]);
}

uint8_t ip4::at(size_t index)
{
    if(index > data.size())
        throw std::out_of_range("Exceeded data size");
    return data.at(index);
}
size_t ip4::size()
{
    return data.size();
}

bool operator==(ip4 const & a1, ip4 const & a2) noexcept
{
    return a1.data == a2.data;
}

bool operator!=(ip4 const & a1, ip4 const & a2) noexcept
{
    return !(a1 == a2);
}

bool operator<(ip4 const & a1, ip4 const & a2) noexcept
{

    return a1.to_ulong() < a2.to_ulong();
}

bool operator>(ip4 const & a1, ip4 const & a2) noexcept
{
    return a2 < a1;
}

bool operator<=(ip4 const & a1, ip4 const & a2) noexcept
{
    return !(a1 > a2);
}

bool operator>=(ip4 const & a1, ip4 const & a2) noexcept
{
    return !(a1 < a2);
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
    auto fits_char = [](int x){ return (x>=0)&&(x<=255);};
    if (is_dot(d1) && is_dot(d2) && is_dot(d3)
        && fits_char(b1) && fits_char(b2) && fits_char(b3) && fits_char(b4))
    {
        a = ip4(b1, b2, b3, b4);
    }
    else {
        is.setstate(std::ios_base::failbit);
        throw(std::invalid_argument("Wrong ip format string!"));
    }

    return is;
}