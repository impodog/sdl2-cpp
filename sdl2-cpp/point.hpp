//
// Created by impodog on 9/9/23.
//

#ifndef SDL2_CPP_POINT_HPP
#define SDL2_CPP_POINT_HPP

#include "utility.hpp"

#define POINT_TEMPLATE(NAME) \
template<\
    ::sdl2::utility::HasPointFeatures NAME \
>
#define POINT_ALIAS(NAME) \
using ArithmeticType = utility::ArithmeticTypeOf<NAME>; \
static constexpr bool use_references = std::is_arithmetic_v<ArithmeticType>;\
using ArithmeticRef = std::conditional_t<use_references, const ArithmeticType &, ArithmeticType>;

namespace sdl2::point_base
{
    POINT_TEMPLATE(T)
    class PointBase : public T
    {
        POINT_ALIAS(T)
    public:
        // Constructors
        PointBase()
                : T{0, 0}
        {}

        PointBase(ArithmeticRef x, ArithmeticRef y)
                : T{x, y}
        {}

        SDL2_CPP_IMPLICIT PointBase(const T &other)
                : T(other.x, other.y)
        {}

        template<typename T_>
        auto convert() const
        {
            using ArithmeticType_ = utility::ArithmeticTypeOf<T_>;
            return T_{static_cast<ArithmeticType_>(this->x), static_cast<ArithmeticType_>(this->y)};
        }
    };


    POINT_TEMPLATE(T)
    class PointOperators : public T
    {
        POINT_ALIAS(T)
    public:
        PointOperators(ArithmeticRef x, ArithmeticRef y)
                : T{x, y}
        {}

        SDL2_CPP_IMPLICIT PointOperators(const T &other)
                : T(other.x, other.y)
        {}

        PointOperators &operator+=(const T &other)
        {
            this->x += other.x;
            this->y += other.y;
            return *this;
        }

        PointOperators &operator-=(const T &other)
        {
            this->x -= other.x;
            this->y -= other.y;
            return *this;
        }

        PointOperators &operator*=(ArithmeticRef other)
        {
            this->x *= other;
            this->y *= other;
            return *this;
        }

        PointOperators &operator/=(ArithmeticRef other)
        {
            this->x /= other;
            this->y /= other;
            return *this;
        }

        bool operator==(const T &other) const noexcept
        {
            return this->x == other.x && this->y == other.y;
        }

        bool operator!=(const T &other) const noexcept
        {
            return this->x != other.x || this->y != other.y;
        }
    };

    POINT_TEMPLATE(T)
    class PointCalculations : public T
    {
        POINT_ALIAS(T)
    public:
        PointCalculations(ArithmeticRef x, ArithmeticRef y)
                : T{x, y}
        {}

        SDL2_CPP_IMPLICIT PointCalculations(const T &other)
                : T(other.x, other.y)
        {}

        [[nodiscard]] double sq_length() const
        {
            return utility::square(this->x) + utility::square(this->y);
        }

        [[nodiscard]] double length() const
        {
            return ::sqrt(sq_length());
        }

        [[nodiscard]] double sq_distance(const T &other) const
        {
            return utility::square(this->x - other.x) + utility::square(this->y - other.y);
        }

        [[nodiscard]] double distance(const T &other) const
        {
            return ::sqrt(sq_distance(other));
        }

        [[nodiscard]] ArithmeticType dot(const T &other) const
        {
            return this->x * other.x + this->y * other.y;
        }

        [[nodiscard]] ArithmeticType cross(const T &other) const
        {
            return this->x * other.y - this->y * other.x;
        }

        [[nodiscard]] double angle(const T &other) const
        {
            return ::atan2(this->cross(other), this->dot(other));
        }

        [[nodiscard]] double angle() const
        {
            return ::atan2(this->y, this->x);
        }
    };

    template<utility::IsArithmetic Arithmetic>
    struct PointStructType_s
    {
        struct type
        {
            Arithmetic x, y;
        };
    };
    template<>
    struct PointStructType_s<int>
    {
        using type = SDL_Point;
    };
    template<>
    struct PointStructType_s<float>
    {
        using type = SDL_FPoint;
    };
}

namespace sdl2
{
    POINT_TEMPLATE(T)
    using PointFromClass = utility::NestedTypeOf<
            T,
            point_base::PointBase
    >;
    POINT_TEMPLATE(T)
    using PointFromStruct = utility::NestedTypeOf<
            T,
            point_base::PointOperators,
            point_base::PointCalculations,
            PointFromClass
    >;
    template<utility::IsArithmetic Arithmetic>
    using PointFromArithmetic = PointFromStruct<typename point_base::PointStructType_s<Arithmetic>::type>;

    using Point = PointFromArithmetic<int>;
    using FPoint = PointFromArithmetic<float>;
    using LPoint = PointFromArithmetic<long>;
    using DPoint = PointFromArithmetic<double>;
}

POINT_TEMPLATE(T)
std::ostream &operator<<(std::ostream &out, const sdl2::point_base::PointBase<T> &point)
{
    return out << "(" << point.x << ", " << point.y << ")";
}

#undef POINT_TEMPLATE
#undef POINT_ALIAS

#endif //SDL2_CPP_POINT_HPP
