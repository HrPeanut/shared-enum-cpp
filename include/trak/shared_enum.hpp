#ifndef TRAK_SHARED_ENUM_HPP
#define TRAK_SHARED_ENUM_HPP

#include <type_traits>

namespace trak {

    /**
     * Represents an enum value being member of multiple enums.
     * The value is implicitly convertible to each member type.
     *
     * @tparam Ts
     *      List of types this enum value is member of.
     */
    template<typename... Ts>
    class shared_enum;

    /**
     * Checks whether U is a member of a shared enum. Provides the member constant value which is
     * equal to \c true if U is in the list of types Ts. Otherwise, value is \c false.
     *
     * This declaration breaks the recursive definition is_member_of_shared_enum::value.
     *
     * @tparam U
     *      The type to test for membership.
     * @tparam Ts
     *      The tail of the list of shared enum types.
     */
    template<typename U, typename... Ts>
    struct is_member_of_shared_enum {
        static const bool value = false;
    };

    /**
     * Checks whether U is a member of a shared enum. Provides the member constant value which is
     * equal to \c true if U is the same as T or in the list of types Ts. Otherwise, value is \c false.
     *
     * The membership test is done using a recursive definition of value on the list tail Ts.
     *
     * @tparam U
     *      The type to test for membership.
     * @tparam T
     *      The head of the list of shared enum types.
     * @tparam Ts
     *      The tail of the list of shared enum types.
     */
    template<typename U, typename T, typename... Ts>
    struct is_member_of_shared_enum<U, T, Ts...> {
        static const bool value = std::conditional<std::is_same<U, T>::value, std::true_type, is_member_of_shared_enum<U, Ts...>>::type::value;
    };

    /**
     * Invalid specification.
     */
    template<typename, typename>
    struct prepend_to_shared_enum {};

    /**
     * Prepends T to a shared enum template parameter list and provides public member typedef type.
     *
     * @tparam T
     *      The type to prepend.
     * @tparam Ts
     *      The list of types of the shared enum.
     */
    template<typename T, typename... Ts>
    struct prepend_to_shared_enum<T, shared_enum<Ts...>> {
        using type = shared_enum<T, Ts...>;
    };

    /**
     * Intersect shared enum types and provides public typedef type equal to a shared enum of the intersection.
     */
    template<typename, typename>
    struct intersect_shared_enum {
        using type = shared_enum<>;
    };

    /**
     * Intersects shared enum types and provides public typedef type equal to a shared enum of the intersection.
     *
     * @tparam T
     *      The head of the first list of shared enum types.
     * @tparam Ts
     *      The tail of the first list of shared enum types.
     * @tparam Us
     *      The second list of shared enum types.
     */
    template<typename T, typename... Ts, typename... Us>
    struct intersect_shared_enum<shared_enum<T, Ts...>, shared_enum<Us...>> {
        using type = typename std::conditional<is_member_of_shared_enum<T, Us...>::value,
                typename prepend_to_shared_enum<T, typename intersect_shared_enum<shared_enum<Ts...>, shared_enum<Us...>>::type>::type,
                typename intersect_shared_enum<shared_enum<Ts...>, shared_enum<Us...>>::type>::type;
    };

    /**
     * Base of shared enums containing the actual enum value.
     *
     * @tparam T
     *      The underlying type of the value.
     */
    template<typename T>
    class shared_enum_base {
    public:
        /**
         * @param value
         *      The value of the shared enum.
         */
        constexpr inline explicit shared_enum_base(T value) noexcept : value_(value) {}

        /**
         * Cast operator to the underlying type.
         *
         * @return
         *      The enum value.
         */
        constexpr inline explicit operator T() const noexcept {
            return value_;
        };

    protected:
        T value_;
    };

    /**
     * Invalid shared_enum template instantiation.
     */
    template<>
    class shared_enum<> {};

    /**
     * Represents an enum value being a member of multiple enums.
     * The value is implicitly convertible to T.
     *
     * @tparam T
     *      The valid enum type of this shared enum.
     */
    template<typename T>
    class shared_enum<T> : public shared_enum_base<typename std::underlying_type<T>::type> {
    public:
        using underlying_type = typename std::underlying_type<T>::type;

        /**
         * Constructor
         *
         * @tparam U
         *      The parameter type of value which is implicitly convertible to the underlying type of T.
         * @param value
         *      The value of this shared enum.
         */
        template<typename U>
        constexpr inline shared_enum(U value) noexcept
                : shared_enum_base<underlying_type>(static_cast<underlying_type>(value)) {
            static_assert(is_member_of_shared_enum<U, T>::value, "U is not a member of shared enum");
        }

        /**
         * Constructor
         *
         * @param value
         *      The value of this shared enum.
         */
        constexpr inline explicit shared_enum(underlying_type value) noexcept
                : shared_enum_base<underlying_type>(value) {}

        /**
         * Cast operator allowing for implicit conversion to T.
         *
         * @return
         *      The enum value as T.
         */
        constexpr inline operator T() const noexcept {
            return static_cast<T>(this->value_);
        }
    };

    template<typename T, typename... Ts>
    class shared_enum<T, Ts...> : shared_enum<Ts...> {
    public:
        using underlying_type = typename shared_enum<Ts...>::underlying_type;

        /**
         * Constructor
         *
         * @tparam U
         *      The parameter type of value which is implicitly convertible to the underlying type of T.
         * @param value
         *      The value of this shared enum.
         */
        template<typename U>
        constexpr inline shared_enum(U value) noexcept : shared_enum<Ts...>(static_cast<underlying_type>(value)) {
            static_assert(is_member_of_shared_enum<U, T, Ts...>::value, "U is not a member of shared enum");
        }
    };
}

#endif //TRAK_SHARED_ENUM_HPP
