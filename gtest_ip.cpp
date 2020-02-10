#include "ip4.h"

#include <gtest/gtest.h>
TEST(test_ip, test_ip_assign_op)
{
    ip4 a1(192,168,0,1);
    ip4 a2 = a1;
    ASSERT_EQ(a1, a2);
}

TEST(test_ip, test_ip_to_string)
{
    ASSERT_TRUE(ip4(192,168,0,1).to_string() == "192.168.0.1");
}

TEST(test_ip, test_ip_from_string)
{
    std::string str("192.168.0.1");
    ASSERT_TRUE(ip4(str).to_string() == "192.168.0.1");
}

TEST(test_ip, test_ip_character_throw)
{
    std::string str("192.168.o.1l");
    ASSERT_ANY_THROW(ip4{str});
}
TEST(test_ip, test_ip_overflow)
{
    std::string str("192.168.532.1");
    ASSERT_ANY_THROW(ip4{str});
}

TEST(test_ip, test_ip_wrong_format)
{
    std::string str("192.168,2.1");
    ASSERT_ANY_THROW(ip4{str});
}

TEST(test_ip, test_ip_at)
{
    auto ip = ip4{"192.168.2.1"};
    ASSERT_EQ(168,ip.at(1));
}

TEST(test_ip, test_ip_size)
{
    auto ip = ip4{"192.168.2.1"};
    ASSERT_EQ(4,ip.size());
}

TEST(test_ip, test_ip_exceed_range)
{
    auto ip = ip4{"192.168.2.1"};
    ASSERT_ANY_THROW(ip.at(4));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}