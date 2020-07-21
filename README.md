# Shared Enum and Bitfield Types
This library provides classes for enum values that are shared between multiple enums. 
This allows for importing enums to namespace, when a enum name is shared by multiple classes

# Usage
```cpp
#include <trak/shared_enum.hpp>

enum class A : unsigned int {
    SharedEnum,
    AnEnum
};
enum class B : unsigned int {
    AnotherEnum,
    SharedEnum
};

constexpr inline trak::shared_enum<A, B> SharedEnum = A::SharedEnum;
constexpr inline A AnEnum = A::AnEnum;
constexpr inline B AnotherEnum = B::AnotherEnum;

# Implicitly convertible
void takesA(A a);
void takesB(B b);
takesA(SharedEnum);
takesB(SharedEnum);
```

The library also implements shared bitfields, which behaves like `trak::shared_enum`, however it provides bit-wise operators.
```cpp
#include <trak/shared_bitfield.hpp>

enum class A : unsigned int {
    SharedEnum,
    AnotherSharedEnum
};
enum class B : unsigned int {
    AnotherEnum,
    AnotherSharedEnum
};

constexpr inline trak::shared_enum<A, B> SharedEnum = A::SharedEnum;
constexpr inline trak::shared_enum<A, B> AnotherSharedEnum = B::AnotherSharedEnum;

# Implicitly convertible
void takesA(A a);
takesA(SharedEnum | AnotherSharedEnum);
```
