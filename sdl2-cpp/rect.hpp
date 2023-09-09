//
// Created by impodog on 9/9/23.
//

#ifndef SDL2_CPP_RECT_HPP
#define SDL2_CPP_RECT_HPP

#include "utility.hpp"
#include "point.hpp"

#define RECT_TEMPLATE(NAME, PNAME) \
template<\
    ::sdl2::utility::HasRectFeatures NAME, \
    ::sdl2::utility::HasPointFeatures PNAME \
>
#define RECT_ALIAS(NAME, PNAME) \
using ArithmeticType = utility::ArithmeticTypeOf<NAME>; \
static_assert(std::is_same_v<ArithmeticType, utility::ArithmeticTypeOf<PNAME>>, "Rect and Point type must be similar."); \
static constexpr bool use_references = std::is_arithmetic_v<ArithmeticType>;\
using ArithmeticRef = std::conditional_t<use_references, const ArithmeticType &, ArithmeticType>;

namespace sdl2::rect_base
{
    RECT_TEMPLATE(T, P)
    class RectBase : public T
    {
        RECT_ALIAS(T, P)
    public:
        // Constructors
        RectBase(ArithmeticRef w, ArithmeticRef h)
                : T{0, 0, w, h}
        {}

        RectBase(ArithmeticRef x, ArithmeticRef y, ArithmeticRef w, ArithmeticRef h)
                : T{x, y, w, h}
        {}

        RectBase(const P &p, ArithmeticRef w, ArithmeticRef h)
                : T{p.x, p.y, w, h}
        {}

        RectBase(const P &p1, const P &p2)
                : T{p1.x, p1.y, p2.x - p1.x, p2.y - p1.y}
        {}

        SDL2_CPP_IMPLICIT RectBase(const T &other)
                : T(other.x, other.y, other.w, other.h)
        {}

        SDL2_CPP_IMPLICIT RectBase(T &&other)
                : T(other.x, other.y, other.w, other.h)
        {}

        template<typename T_>
        auto convert() const
        {
            using ArithmeticType_ = utility::ArithmeticTypeOf<T_>;
            return T_{static_cast<ArithmeticType_>(this->x), static_cast<ArithmeticType_>(this->y),
                      static_cast<ArithmeticType_>(this->w), static_cast<ArithmeticType_>(this->h)};
        }
    };

    RECT_TEMPLATE(T, P)
    class RectOperators : public T
    {
        RECT_ALIAS(T, P)
    public:
        RectOperators(ArithmeticRef x, ArithmeticRef y, ArithmeticRef w, ArithmeticRef h)
                : T{x, y, w, h}
        {}

        SDL2_CPP_IMPLICIT RectOperators(const T &other)
                : T(other.x, other.y, other.w, other.h)
        {}

        T &operator+=(const P &p)
        {
            this->x += p.x;
            this->y += p.y;
            return *this;
        }

        T &operator-=(const P &p)
        {
            this->x -= p.x;
            this->y -= p.y;
            return *this;
        }

        bool operator==(const T &other) const
        {
            return this->x == other.x && this->y == other.y && this->w == other.w && this->h == other.h;
        }

        bool operator!=(const T &other) const
        {
            return !(*this == other);
        }
    };

    RECT_TEMPLATE(T, P)
    class RectCalculations : public T
    {
        RECT_ALIAS(T, P)
    public:
        RectCalculations(ArithmeticRef x, ArithmeticRef y, ArithmeticRef w, ArithmeticRef h)
                : T{x, y, w, h}
        {}

        SDL2_CPP_IMPLICIT RectCalculations(const T &other)
                : T(other.x, other.y, other.w, other.h)
        {}

        RectCalculations &expand(const P &center, ArithmeticRef factor)
        {
            this->x = center.x - (center.x - this->x) * factor;
            this->y = center.y - (center.y - this->y) * factor;
            this->w = this->w * factor;
            this->h = this->h * factor;
            return *this;
        }

        RectCalculations &move(const P &p)
        {
            this->x = p.x;
            this->y = p.y;
            return *this;
        }

        P center() const
        {
            return P(this->x + this->w / 2, this->y + this->h / 2);
        }

        P area() const
        {
            return P(this->w, this->h);
        }

        P position() const
        {
            return P(this->x, this->y);
        }

        ArithmeticType area_size() const
        {
            return this->w * this->h;
        }

        bool contains(const P &p) const
        {
            return this->x <= p.x && p.x <= this->x + this->w && this->y <= p.y && p.y <= this->y + this->h;
        }

        bool contains(const T &other) const
        {
            return this->x <= other.x && other.x + other.w <= this->x + this->w &&
                   this->y <= other.y && other.y + other.h <= this->y + this->h;
        }

        bool intersects(const T &other) const
        {
            return this->x < other.x + other.w && other.x < this->x + this->w &&
                   this->y < other.y + other.h && other.y < this->y + this->h;
        }
    };

    template<utility::IsArithmetic Arithmetic>
    struct RectStructType_s
    {
        struct type
        {
            Arithmetic x, y;
            Arithmetic w, h;
        };
        using ptype = sdl2::PointFromArithmetic<Arithmetic>;
    };
    template<>
    struct RectStructType_s<int>
    {
        using type = SDL_Rect;
        using ptype = SDL_Point;
    };
    template<>
    struct RectStructType_s<float>
    {
        using type = SDL_FRect;
        using ptype = SDL_FPoint;
    };

    RECT_TEMPLATE(T, P)
    struct RectFromClass_s
    {
        template<typename T_>
        using RectBase_t = rect_base::RectBase<T_, P>;

        using type = utility::NestedTypeOf<
                T,
                RectBase_t
        >;
    };

    RECT_TEMPLATE(T, P)
    using RectFromClass = typename rect_base::RectFromClass_s<T, P>::type;

    RECT_TEMPLATE(T, P)
    struct RectFromStruct_s
    {
        template<typename T_>
        using RectOperators_t = rect_base::RectOperators<T_, P>;

        template<typename T_>
        using RectCalculations_t = rect_base::RectCalculations<T_, P>;

        template<typename T_>
        using RectFromClass_t = RectFromClass<T_, P>;

        using type = utility::NestedTypeOf<
                T,
                RectOperators_t,
                RectCalculations_t,
                RectFromClass_t
        >;
    };

    RECT_TEMPLATE(T, P)
    using RectFromStruct = typename rect_base::RectFromStruct_s<T, P>::type;

    template<utility::IsArithmetic Arithmetic>
    using RectFromArithmetic = RectFromStruct<
            typename RectStructType_s<Arithmetic>::type,
            typename RectStructType_s<Arithmetic>::ptype
    >;
}

namespace sdl2
{
    using rect_base::RectFromClass;
    using rect_base::RectFromStruct;
    using rect_base::RectFromArithmetic;

    using Rect = RectFromArithmetic<int>;
    using FRect = RectFromArithmetic<float>;
    using LRect = RectFromArithmetic<long>;
    using DRect = RectFromArithmetic<double>;
}

RECT_TEMPLATE(T, P)
std::ostream &operator<<(std::ostream &out, const sdl2::rect_base::RectBase<T, P> &rect)
{
    out << "(" << rect.x << ", " << rect.y << ", " << rect.w << ", " << rect.h << ")";
    return out;
}

#undef RECT_TEMPLATE
#undef RECT_ALIAS

#endif //SDL2_CPP_RECT_HPP
