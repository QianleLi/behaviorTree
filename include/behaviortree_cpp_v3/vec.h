//
// Created by binfeng.yang on 2019/5/3.
//

#ifndef BVNAVIGATION_VEC_H
#define BVNAVIGATION_VEC_H
#include <cmath>
#include <limits>
template <typename Type>
struct Vec2;

template <typename Type>
struct Vec3;

template <typename Type>
struct Vec2
{
    using type = Type;

    union
    {
        Type x;
        Type s;
        Type r;
        Type v;
        Type p;
    };
    union
    {
        Type y;
        Type t;
        Type g;
        Type w;
        Type l;
    };

    Vec2() : x(0), y(0)
    {
    }
    Vec2(Type x_in, Type y_in) : x(x_in), y(y_in)
    {
    }
    Vec2(const Vec2<Type>& copy)
    {
        x = copy.x;
        y = copy.y;
    }
    /* Vec2(Type scalar) : x(scalar), y(scalar) { }
    Vec2(Vec3<Type> copy) { x = copy.x; y = copy.y; }*/

    static bool is_equal(const Vec2<Type>& first, const Vec2<Type>& second, Type epsilon)
    {
        Type diff_x = second.x - first.x;
        Type diff_y = second.y - first.y;
        return (diff_x >= -epsilon && diff_x <= epsilon && diff_y >= -epsilon && diff_y <= epsilon);
    }

    /// \brief Returns true if equal within the bounds of an epsilon
    ///
    /// \param other = Other value
    /// \param epsilon = The epsilon (eg FLT_EPSILON, DBL_EPSILON)
    bool is_equal(const Vec2<Type>& other,
                  Type epsilon = std::numeric_limits<Type>::epsilon()) const
    {
        return Vec2<Type>::is_equal(*this, other, epsilon);
    }

    /// \brief Returns the distance between two points
    ///
    /// \param other = Second vector used to calculate distance.
    /// \return Distance between two vector
    Type distance(const Vec2<Type>& other) const;

    bool operator==(const Vec2<Type>& other) const
    {
        return is_equal(other);
    }

    bool operator!=(const Vec2<Type>& other) const
    {
        return !this->operator==(other);
    }

    bool operator<(const Vec2<Type>& other) const
    {
        return y < other.y || (y == other.y && x < other.x);
    }

    Vec2<Type> operator+(const Vec2<Type>& other) const
    {
        return {x + other.x, y + other.y};
    }

    Vec2<Type> operator-(const Vec2<Type>& other) const
    {
        return {x - other.x, y - other.y};
    }
};

typedef Vec2<unsigned char> Vec2ub;
typedef Vec2<char> Vec2b;
typedef Vec2<unsigned short> Vec2us;
typedef Vec2<short> Vec2s;
typedef Vec2<unsigned int> Vec2ui;
typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;
typedef Vec2i Point_2i;
typedef Vec2f Point_2f;
typedef Vec2d Point_2d;

// For integers
template <typename Type>
inline Type Vec2<Type>::distance(const Vec2<Type>& vector) const
{
    float value_x = x - vector.x;
    float value_y = y - vector.y;
    return (Type)std::floor(std::sqrt(value_x * value_x + value_y * value_y) + 0.5f);
}

// For floats
template <>
inline float Vec2f::distance(const Vec2f& vector) const
{
    float value_x = x - vector.x;
    float value_y = y - vector.y;
    return std::sqrt(value_x * value_x + value_y * value_y);
}

// For doubles
template <>
inline double Vec2d::distance(const Vec2d& vector) const
{
    double value_x = x - vector.x;
    double value_y = y - vector.y;
    return std::sqrt(value_x * value_x + value_y * value_y);
}

template <typename Type>
struct Vec3
{
    using type = Type;

    union
    {
        Type x;
        Type s;
        Type r;
    };
    union
    {
        Type y;
        Type t;
        Type g;
    };
    union
    {
        Type z;
        Type u;
        Type b;
    };

    Vec3() : x(0), y(0), z(0)
    {
    }
    Vec3(Type x_in, Type y_in, Type z_in) : x(x_in), y(y_in), z(z_in)
    {
    }
    // explicit Vec3(Type scalar) : x(scalar), y(scalar), z(scalar) { }
    Vec3(const Vec2<Type>& copy, const Type& z_in)
    {
        x = copy.x;
        y = copy.y;
        z = z_in;
    }
    // explicit Vec3(Vec3<Type> copy) { x = copy.x; y = copy.y; z = copy.z; }

    static bool is_equal(const Vec3<Type>& first, const Vec3<Type>& second, Type epsilon)
    {
        Type diff_x = second.x - first.x;
        Type diff_y = second.y - first.y;
        Type diff_z = second.z - first.z;
        return (diff_x >= -epsilon && diff_x <= epsilon && diff_y >= -epsilon &&
                diff_y <= epsilon && diff_z >= -epsilon && diff_z >= epsilon);
    }

    static Vec3<Type> cross(const Vec3<Type>& v1, const Vec3<Type>& v2)
    {
        Vec3<Type> tmp = Vec3<Type>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
                                    v1.x * v2.y - v1.y * v2.x);
        return tmp;
    }

    Vec3<Type>& cross(const Vec3<Type>& v)
    {
        *this = cross(*this, v);
        return *this;
    }

    /// \brief Returns true if equal within the bounds of an epsilon
    ///
    /// \param other = Other value
    /// \param epsilon = The epsilon (eg FLT_EPSILON, DBL_EPSILON)
    bool is_equal(const Vec3<Type>& other,
                  Type epsilon = std::numeric_limits<Type>::epsilon()) const
    {
        return Vec3<Type>::is_equal(*this, other, epsilon);
    }

    /// \brief Returns the distance between two points
    ///
    /// \param other = Second vector used to calculate distance.
    /// \return The distance between the two vectors.
    Type distance(const Vec3<Type>& other) const;

    bool operator==(const Vec3<Type>& other) const
    {
        return is_equal(other);
    }

    bool operator!=(const Vec3<Type>& other) const
    {
        return !this->operator==(other);
    }

    bool operator<(const Vec3<Type>& other) const
    {
        return z < other.z || (z == other.z && (y < other.y || (y == other.y && x < other.x)));
    }

    Vec3<Type> operator+(const Vec3<Type>& other) const
    {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vec3<Type> operator-(const Vec3<Type>& other) const
    {
        return {x - other.x, y - other.y, z - other.z};
    }
};
typedef Vec3<unsigned char> Vec3ub;
typedef Vec3<char> Vec3b;
typedef Vec3<unsigned short> Vec3us;
typedef Vec3<short> Vec3s;
typedef Vec3<unsigned int> Vec3ui;
typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;
typedef Vec3i Point_3i;
typedef Vec3f Point_3f;
typedef Vec3d Point_3d;
// For integers
template <typename Type>
inline Type Vec3<Type>::distance(const Vec3<Type>& vector) const
{
    float value_x, value_y, value_z;
    value_x = x - vector.x;
    value_y = y - vector.y;
    value_z = z - vector.z;
    return (Type)std::floor(std::sqrt(value_x * value_x + value_y * value_y + value_z * value_z) +
                            0.5f);
}

// For floats
template <>
inline float Vec3f::distance(const Vec3f& vector) const
{
    float value_x = x - vector.x;
    float value_y = y - vector.y;
    float value_z = z - vector.z;
    return std::sqrt(value_x * value_x + value_y * value_y + value_z * value_z);
}

// For doubles
template <>
inline double Vec3d::distance(const Vec3d& vector) const
{
    double value_x = x - vector.x;
    double value_y = y - vector.y;
    double value_z = z - vector.z;
    return std::sqrt(value_x * value_x + value_y * value_y + value_z * value_z);
}

#endif   // BVNAVIGATION_VEC_H
