#include "gtest/gtest.h"

#include "hex.h"

GTEST_TEST(Hex, toBin)
{
    const uint8_t hex[] = "01020304ABcd";
    uint8_t *bin = (uint8_t *)malloc(6);
    memset(bin, 0, 6);
    size_t len = hex2bin(hex, 12, bin, 6);
    ASSERT_EQ(len, 6);
    ASSERT_EQ(bin[0], 1);
    ASSERT_EQ(bin[5], 0xCD);
}

GTEST_TEST(Bin, toHex)
{
    char *hex = (char *)malloc(13);
    memset(hex, 0, 13);
    uint8_t bin[] = {1, 2, 3, 4, 0xab, 0xcd};
    size_t len = bin2hex(bin, 6, (uint8_t *)hex, 12);
    ASSERT_EQ(len, 12);
    printf("%d, %s", strlen(hex), hex);
    ASSERT_EQ(hex[0], '0');
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}