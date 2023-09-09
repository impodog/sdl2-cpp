//
// Created by impodog on 9/9/23.
//

#ifndef SDL2_CPP_UTILITY_HPP
#define SDL2_CPP_UTILITY_HPP

#include "../include.h"

namespace sdl2::utility
{
    /**
     * @brief Returns the right value form of a variable.
     */
    template<typename T>
    consteval T value_of(const T &) noexcept
    {
        return std::declval<T>();
    }

    template<typename Current, template<typename> typename Next,
            template<typename InnerType> typename ...Rest>
    struct NestedTypeOf_s
    {
        using type = typename NestedTypeOf_s<Next<Current>, Rest...>::type;
    };

    template<typename Current, template<typename> typename Next>
    struct NestedTypeOf_s<Current, Next>
    {
        using type = Next<Current>;
    };

    /**
     * @brief A clearer form of deeply nested template type series like A<B<C>>.
     * @note The correct order of writing is NestedTypeOf<C, B, A>.
     */
    template<typename Current, template<typename> typename Next,
            template<typename> typename ...Rest>
    using NestedTypeOf = typename NestedTypeOf_s<Current, Next, Rest...>::type;


    template<typename T>
    using ArithmeticTypeOf = decltype(std::declval<T>().x);

    template<typename T>
    consteval auto arithmetic_value_of()
    {
        return std::declval<ArithmeticTypeOf<T>>();
    }

    template<typename T>
    concept IsArithmetic =
    requires(T value) {
        { value + value } -> std::convertible_to<T>;
        { value - value } -> std::convertible_to<T>;
        { value * value } -> std::convertible_to<T>;
        { value / value } -> std::convertible_to<T>;
        { ::abs(value) } -> std::convertible_to<T>;
        { ::sqrt(value) } -> std::convertible_to<double>;
    } && std::convertible_to<T, double>;

    template<typename T>
    concept HasPointFeatures =
    std::is_class_v<T> &&
    requires(T value) {
        { value_of(value.x) } -> IsArithmetic;
    }
    && std::is_same_v<decltype(T::x), decltype(T::y)>;

    template<typename T>
    concept HasSizeFeatures =
    std::is_class_v<T> &&
    requires(T value) {
        { value_of(value.w) } -> IsArithmetic;
    }
    && std::is_same_v<decltype(T::w), decltype(T::h)>;

    template<typename T>
    concept HasRectFeatures =
    HasPointFeatures<T> && HasSizeFeatures<T>
    && std::is_same_v<decltype(T::x), decltype(T::w)>;


    template<IsArithmetic T>
    constexpr T square(const T &value)
    {
        return value * value;
    }
}

#endif //SDL2_CPP_UTILITY_HPP
