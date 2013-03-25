#include <gtest/gtest.h>

#include <stdexcept>
#include <string>
#include "Utilities.h"
#include <iostream>


TEST(UtilitiesTests, GroupFromString) {
    std::string input = "ModPGroup(safe-prime modulus=2*order+1. order bit-length = 512 )::0000000002010000001c766572696669636174756d2e61726974686d2e4d6f64504772 6f757000000000040100000041014354c848a190b7b5fbddcd07bed36e59af5a50cc5966b 202bba0959ccc42061a2f468f87fa436451bd48d5cb333c0bb0aca763193e70c725495455 a99939276f010000004100a1aa642450c85bdafdeee683df69b72cd7ad28662cb359015dd 04ace6621030d17a347c3fd21b228dea46ae5999e05d85653b18c9f386392a4aa2ad4cc9c 93b701000000410132027413c1464af9b3ebe05f40059902857843365887f3e084e973dfd 3da198697724ac422dfce4728c2baa07760b5eae2d709bd7ff4f79d4e71fc9c2d37e26701 0000000400000001";

    std::cout << "Creating proofStruct" << std::endl;

    proofStruct pfStr;

    std::cout << "Getting group from string" << std::endl;
    getGroupFromString(pfStr, input);

    std::cout << "Creating group node" << std::endl;

    Node group;

    mpz_class rop;
    mpz_set_str(rop.get_mpz_t(), "014354c848a190b7b5fbddcd07bed36e59af5a50cc5966b202bba0959ccc42061a2f468f87fa436451bd48d5cb333c0bb0aca763193e70c725495455a99939276f", 16);

    group.addChild(IntLeaf(rop));

    mpz_set_str(rop.get_mpz_t(), "00a1aa642450c85bdafdeee683df69b72cd7ad28662cb359015dd04ace6621030d17a347c3fd21b228dea46ae5999e05d85653b18c9f386392a4aa2ad4cc9c93b7", 16);

    group.addChild(IntLeaf(rop));

    mpz_set_str(rop.get_mpz_t(), "0132027413c1464af9b3ebe05f40059902857843365887f3e084e973dfd3da198697724ac422dfce4728c2baa07760b5eae2d709bd7ff4f79d4e71fc9c2d37e267", 16);

    group.addChild(IntLeaf(rop));

    group.addChild(IntLeaf(1, 4));

    EXPECT_EQ(group == pfStr.Gq, true);
    
}

