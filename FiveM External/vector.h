#pragma once
#include <xmmintrin.h> // SIMD operations
#include <tlhelp32.h>
#include <windows.h>
#include <winternl.h>
#include <iostream>

// 2D vector
struct Vec2
{
    float x, y; // Components
};

// Structure representing a 4-dimensional vector
struct Vector4 {
    float x, y, z, w; // Components
};

// Structure representing a 3-dimensional vector
struct Vec3
{
    float x, y, z; // Components

    void Normalize() {
        // Ensure y component stays within [-180, 180] range
        while (y < -180) {
            y = 360;
        }
        while (y > 180) {
            y = -360;
        }

        // Ensure x component stays within [-89, 89] range
        while (x > 89) {
            x = -89;
        }
        while (x < -89) {
            x = 89;
        }
    }

    // Operator overloads for vector arithmetic
    Vec3 operator - (Vec3 i) {
        return {
          x - i.x,
          y - i.y,
          z - i.z
        };
    }

    Vec3 operator + (Vec3 i) {
        return {
          x + i.x,
          y + i.y,
          z + i.z
        };
    }

    Vec3 operator / (float i) {
        return {
          x / i,
          y / i,
          z / i
        };
    }

    Vec3 operator * (float i) {
        return {
          x * i,
          y * i,
          z * i
        };
    }

    // Static function to create Vec3 from __m128 type
    static Vec3 FromM128(__m128 in)
    {
        return Vec3
        {
            in.m128_f32[0],
            in.m128_f32[1],
            in.m128_f32[2]
        };
    }
};

// Structure representing a 3-dimensional vector with misspelled name
struct Vetor33 {
    float x, y, z; // Components
};

// Structure representing a 4-dimensional vector
struct Vec4
{
    float x, y, z, w; // Components
};

// Class representing a 3-dimensional vector
class Vetor3
{
public:
    Vetor3() : x(0.f), y(0.f), z(0.f) {} // Default constructor
    Vetor3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {} // Constructor with parameters
    ~Vetor3() {} // Destructor

    float x; // X component
    float y; // Y component
    float z; // Z component

    // Function to compute dot product with another vector
    inline float Dot(Vetor3 v) {
        return x * v.x + y * v.y + z * v.z;
    }

    // Function to compute distance to another vector
    inline float Distance(Vetor3 v) {
        return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
    }

    // Function to compute length of the vector
    inline float Length() {
        float ls = x * x + y * y + z * z;
        return sqrt(ls);
    }

    // Operator overloads for vector arithmetic
    Vetor3 operator+(Vetor3 v) {
        return Vetor3(x + v.x, y + v.y, z + v.z);
    }

    Vetor3 operator-(Vetor3 v) {
        return Vetor3(x - v.x, y - v.y, z - v.z);
    }

    Vetor3 operator*(float number) const {
        return Vetor3(x * number, y * number, z * number);
    }

    Vetor3& operator-=(const Vetor3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    // Function to clamp the vector within certain ranges
    void clamp() {
        if (x > 75.f) x = 75.f;
        else if (x < -75.f) x = -75.f;
        if (z < -180) z += 360.0f;
        else if (z > 180) z -= 360.0f;

        y = 0.f;
    }
};

#pragma pack(push, 1)
// Structure representing a packed 3-dimensional vector
typedef struct PVector3
{


    // DWORD _padding*; |  Padding for alignment


    float x; // X component
    DWORD _paddingx;
    float y; // Y component
    DWORD _paddingy;
    float z; // Z component
    DWORD _paddingz;

    PVector3(float x, float y, float z) :
        x(x), y(y), z(z),
        _paddingx(0), _paddingy(0), _paddingz(0)
    {
    }

    PVector3() noexcept : PVector3(0.f, 0.f, 0.f) {}
}PVector3;
#pragma pack(pop)

// Function to convert Vetor3 to PVector3
PVector3 ToPVector3(Vetor3 pVec) {
    return PVector3(pVec.x, pVec.y, pVec.z);
}
