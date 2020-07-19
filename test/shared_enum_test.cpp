#include <gtest/gtest.h>
#include <trak/shared_enum.hpp>

using namespace trak;

enum class A : unsigned int {
    First,
    Second,
    Third
};

enum class B : unsigned int {
    First,
    Second,
    Third
};

enum class C : unsigned int {
    First,
    Second,
    Third
};

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

unsigned int takes_A(A value) {
    return static_cast<unsigned int>(value);
}

unsigned int takes_B(B value) {
    return static_cast<unsigned int>(value);
}

unsigned int takes_C(C value) {
    return static_cast<unsigned int>(value);
}

TEST(shared_enum, convertible) {
    shared_enum<A, B, C> value1 = A::First;

    EXPECT_EQ(0, takes_A(value1));
    EXPECT_EQ(0, takes_B(value1));
    EXPECT_EQ(0, takes_C(value1));

    shared_enum<B, C> value2 = B::Third;
    EXPECT_EQ(2, takes_B(value2));
    EXPECT_EQ(2, takes_C(value2));

    shared_enum<A> value3 = A::Second;
    EXPECT_EQ(1, takes_A(value3));
}

TEST(shared_enum, comparable) {
    shared_enum<A, B, C> shared_abc_first = A::First;
    shared_enum<A, B, C> shared_abc_second = B::Second;
    shared_enum<A, B, C> shared_abc_third = C::Third;

    // Should be equal to their assigned value.
    EXPECT_EQ(shared_abc_first, A::First);
    EXPECT_EQ(shared_abc_second, B::Second);
    EXPECT_EQ(shared_abc_third, C::Third);
    EXPECT_EQ(A::First, shared_abc_first );
    EXPECT_EQ(B::Second, shared_abc_second);
    EXPECT_EQ(C::Third, shared_abc_third);

    // Should be equal to values from shared enums.
    EXPECT_EQ(shared_abc_first, C::First);
    EXPECT_EQ(shared_abc_second, A::Second);
    EXPECT_EQ(shared_abc_third, B::Third);
    EXPECT_EQ(B::First, shared_abc_first);
    EXPECT_EQ(C::Second, shared_abc_second);
    EXPECT_EQ(A::Third, shared_abc_third);

    // Should be comparable
    shared_enum<A, B, C> shared_1 = A::First;
    shared_enum<A, B, C> shared_2 = C::First;
    shared_enum<A, B> shared_ab_first = B::First;
    shared_enum<B, C> shared_bc_first = C::First;

    EXPECT_EQ(shared_1, shared_2);
    EXPECT_EQ(shared_1, shared_ab_first);
    EXPECT_EQ(shared_1, shared_bc_first);
}