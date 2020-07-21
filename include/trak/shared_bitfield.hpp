#ifndef TRAK_SHARED_BITFIELD_HPP
#define TRAK_SHARED_BITFIELD_HPP

#include <trak/shared_enum.hpp>

namespace trak {

    /**
     * Represents an bitfield value being member of multiple bitfields.
     * The value is implicitly convertible to each bitfield type.
     *
     * @tparam Ts
     *      List of types this bitfield is a member of.
     */
    template<typename... Ts>
    class shared_bitfield;

    /**
     * Invalid specification.
     */
    template<typename>
    struct shared_enum_to_bitfield {};

    /**
     * Converts a shared enum to a shared bitfield and provides
     * public member typedef type, being the converted type.
     *
     * @tparam Ts
     *      The list of types of the shared enum.
     */
    template<typename... Ts>
    struct shared_enum_to_bitfield<shared_enum<Ts...>> {
        using type = shared_bitfield<Ts...>;
    };

    /**
     * Represents an bitfield value being member of multiple bitfields.
     * The value is implicitly convertible to each bitfield type.
     *
     * @tparam T
     *      The head of the valid types of the shared bitfield.
     * @tparam Ts
     *      The tail of the valid types of the shared bitfield.
     */
    template<typename T, typename... Ts>
    class shared_bitfield<T, Ts...> : public shared_enum<T, Ts...> {
    public:
        using underlying_type = typename shared_enum<T, Ts...>::underlying_type;
        using shared_enum<T, Ts...>::shared_enum;

        /**
         * Performs a bit-wise 'or' operation on the values of this and rhs, while
         * constraining the shared types to the intersection.
         *
         * @tparam Us
         *      The list of types of the right-hand side shared bitfield.
         */
        template<typename... Us>
        constexpr inline auto operator|(shared_bitfield<Us...> rhs) const -> typename std::enable_if<!std::is_same<
                typename intersect_shared_enum<shared_enum<T, Ts...>, shared_enum<Us...>>::type, shared_enum<>>::value,
        typename shared_enum_to_bitfield<typename intersect_shared_enum<shared_enum<T, Ts...>, shared_enum<Us...>>::type>::type>::type {
            return static_cast<typename shared_enum_to_bitfield<typename intersect_shared_enum<shared_enum<T, Ts...>, shared_enum<Us...>>::type>::type>(
                    static_cast<underlying_type>(*this) | static_cast<underlying_type>(rhs));
        }

        /**
         * Performs a bit-wise 'or' assignment operation on the values of this and rhs.
         * The types of the right-hand side must be a superset of this.
         *
         * @tparam Us
         *      The list of types of the right-hand side shared bitfield.
         */
        template<typename... Us>
        inline auto operator|=(shared_bitfield<Us...> rhs) -> typename std::enable_if<!std::is_same<
                typename intersect_shared_enum<shared_enum<T, Ts...>, shared_enum<Us...>>::type, shared_enum<>>::value, shared_bitfield&>::type {
            this->value_ |= static_cast<underlying_type>(rhs);
            return *this;
        }

        /**
         * Performs a bit-wise 'and' operation on the values of this and rhs, while
         * constraining the shared types to the intersection.
         *
         * @tparam Us
         *      The list of types of the right-hand side shared bitfield.
         */
        template<typename... Us>
        constexpr inline auto operator&(shared_bitfield<Us...> rhs) const -> typename std::enable_if<!std::is_same<
                typename intersect_shared_enum<shared_enum<T, Ts...>, shared_enum<Us...>>::type, shared_enum<>>::value,
                typename shared_enum_to_bitfield<typename intersect_shared_enum<shared_enum<T, Ts...>, shared_enum<Us...>>::type>::type>::type {
            return static_cast<typename shared_enum_to_bitfield<typename intersect_shared_enum<shared_enum<T, Ts...>, shared_enum<Us...>>::type>::type>(
                    static_cast<underlying_type>(*this) & static_cast<underlying_type>(rhs));
        }

        /**
         * Performs a bit-wise 'and' assignment operation on the values of this and rhs.
         * The types of the right-hand side must be a superset of this.
         *
         * @tparam Us
         *      The list of types of the right-hand side shared bitfield.
         */
        template<typename... Us>
        inline auto operator&=(shared_bitfield<Us...> rhs) -> typename std::enable_if<!std::is_same<
                typename intersect_shared_enum<shared_enum<T, Ts...>, shared_enum<Us...>>::type, shared_enum<>>::value, shared_bitfield&>::type {
            this->value_ &= static_cast<underlying_type>(rhs);
            return *this;
        }

        /**
         * Performs a bit-wise 'xor' operation on the values of this and rhs, while
         * constraining the shared types to the intersection.
         *
         * @tparam Us
         *      The list of types of the right-hand side shared bitfield.
         */
        template<typename... Us>
        constexpr inline auto operator^(shared_bitfield<Us...> rhs) const -> typename std::enable_if<!std::is_same<
                typename intersect_shared_enum<shared_enum<T, Ts...>, shared_enum<Us...>>::type, shared_enum<>>::value,
                typename shared_enum_to_bitfield<typename intersect_shared_enum<shared_enum<T, Ts...>, shared_enum<Us...>>::type>::type>::type {
            return static_cast<typename shared_enum_to_bitfield<typename intersect_shared_enum<shared_enum<T, Ts...>, shared_enum<Us...>>::type>::type>(
                    static_cast<underlying_type>(*this) ^ static_cast<underlying_type>(rhs));
        }

        /**
         * Performs a bit-wise 'xor' assignment operation on the values of this and rhs.
         * The types of the right-hand side must be a superset of this.
         *
         * @tparam Us
         *      The list of types of the right-hand side shared bitfield.
         */
        template<typename... Us>
        inline auto operator^=(shared_bitfield<Us...> rhs) -> typename std::enable_if<!std::is_same<
                typename intersect_shared_enum<shared_enum<T, Ts...>, shared_enum<Us...>>::type, shared_enum<>>::value, shared_bitfield&>::type {
            this->value_ ^= static_cast<underlying_type>(rhs);
            return *this;
        }
    };
}

#endif //TRAK_SHARED_BITFIELD_HPP
