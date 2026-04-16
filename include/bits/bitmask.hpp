/// SPDX-License-Identifier: MIT
/// Copyright (c) 2026 ours Developers
#ifndef BITS_BIT_MASK_HPP
#define BITS_BIT_MASK_HPP 1

#include <type_traits>
#include <utility>

#if defined BITS_IMPL_BITMASK
#   error "The marco `BITS_IMPL_BITMASK` has been defined"
#endif

#define BITS_IMPL_BITMASK(T)    \
    static auto bits_impl_bitmask_for(T) -> bits::bitmask::Implemented;

#define BITS_IMPL_BITMASK_INNER(T)    \
    friend auto bits_impl_bitmask_for(T) -> bits::bitmask::Implemented;

constexpr auto bits_impl_bitmask_for(...) -> void;

namespace bits::bitmask {
    struct Implemented {};

    template <typename Enum>
        requires std::is_enum_v<Enum>
    constexpr auto ImplementedV = std::is_same_v<decltype(bits_impl_bitmask_for(std::declval<Enum>())), Implemented>;
} // namespace bits

template <typename Enum>
    requires bits::bitmask::ImplementedV<Enum>
constexpr auto operator|(Enum lhs, Enum rhs) -> Enum {
    return static_cast<Enum>(std::to_underlying(lhs) | std::to_underlying(rhs));
}

template <typename Enum>
    requires bits::bitmask::ImplementedV<Enum>
constexpr auto operator&(Enum lhs, Enum rhs) -> Enum {
    return static_cast<Enum>(std::to_underlying(lhs) & std::to_underlying(rhs));
}

template <typename Enum>
    requires bits::bitmask::ImplementedV<Enum>
constexpr auto operator~(Enum e) -> Enum {
    return static_cast<Enum>(~std::to_underlying(e));
}

template<typename Enum>
    requires bits::bitmask::ImplementedV<Enum>
constexpr auto operator|=(Enum& lhs, Enum rhs) -> Enum & {
    lhs = lhs | rhs;
    return lhs;
}

template<typename Enum>
    requires bits::bitmask::ImplementedV<Enum>
constexpr auto operator&=(Enum& lhs, Enum rhs) -> Enum & {
    lhs = lhs & rhs;
    return lhs;
}

template<typename Enum>
    requires bits::bitmask::ImplementedV<Enum>
constexpr auto operator!(Enum lhs) -> bool {
    return !std::to_underlying(lhs);
}

constexpr auto operator""_bit(unsigned long long v) -> unsigned long long { 
    return static_cast<unsigned long long>(1 << v);
}

#endif // #ifndef BITS_BIT-MASK_HPP