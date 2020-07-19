#include <gtest/gtest.h>
#include <trak/shared_enum.hpp>

using namespace trak;

enum class A : unsigned int {
    Aa = 1,
    Ab = 2,
    Ac = 3
};

enum class B : unsigned int {
    Ba,
    Bb,
    Bc
};

enum class C : unsigned int {
    Ca,
    Cb,
    Cc
};

unsigned int takes_A(A value) {
    return static_cast<unsigned int>(value);
}

unsigned int takes_B(B value) {
    return static_cast<unsigned int>(value);
}

unsigned int takes_C(C value) {
    return static_cast<unsigned int>(value);
}

TEST(shared_enum, member) {
    auto test = is_member_of_shared_enum<A, A, B, C>::value;
    EXPECT_TRUE(test);
    test = is_member_of_shared_enum<B, A, B, C>::value;
    EXPECT_TRUE(test);
    test = is_member_of_shared_enum<C, A, B, C>::value;
    EXPECT_TRUE(test);

    test = is_member_of_shared_enum<A>::value;
    EXPECT_FALSE(test); // A is not in the empty shared enum
    test = is_member_of_shared_enum<A, B>::value;
    EXPECT_FALSE(test); // A is not B
    test = is_member_of_shared_enum<C, A, B>::value;
    EXPECT_FALSE(test); // C is neither A or B
}

TEST(shared_enum, intersection) {
    auto test = std::is_same<typename intersect_shared_enum<shared_enum<A>, shared_enum<A>>::type, shared_enum<A>>::value;
    EXPECT_TRUE(test);
    test = std::is_same<typename intersect_shared_enum<shared_enum<A, B>, shared_enum<A>>::type, shared_enum<A>>::value;
    EXPECT_TRUE(test);
    test = std::is_same<typename intersect_shared_enum<shared_enum<A, B, C>, shared_enum<A>>::type, shared_enum<A>>::value;
    EXPECT_TRUE(test);
    test = std::is_same<typename intersect_shared_enum<shared_enum<B, C>, shared_enum<A, B, C>>::type, shared_enum<B, C>>::value;
    EXPECT_TRUE(test);
    test = std::is_same<typename intersect_shared_enum<shared_enum<A, B, C>, shared_enum<A, B, C>>::type, shared_enum<A, B, C>>::value;
    EXPECT_TRUE(test);
}

//TEST(shared_enum, convertible) {
//    shared_enum<A, B, C> value = A::Aa;
//
//    EXPECT_EQ(1, takes_A(value));
//    EXPECT_EQ(1, takes_B(value));
//    EXPECT_EQ(1, takes_C(value));
//}

