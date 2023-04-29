#pragma once
#include <iostream>
#include <cmath>
class Vector2D
{
    public:
    float x;
    float y;

    Vector2D();
    Vector2D(float x, float y);

    void rotate(float angle) {
        float newX = x * cos(angle) - y * sin(angle);
        float newY = x * sin(angle) + y * cos(angle);
        x = newX;
        y = newY;
    }
    Vector2D& Add(const Vector2D& vec);
    Vector2D& Subtract(const Vector2D& vec);
    Vector2D& Multiply(const Vector2D& vec);
    Vector2D& Divide(const Vector2D& vec);

    friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

    Vector2D& operator+=(const Vector2D& vec);
    Vector2D& operator-=(const Vector2D& vec);
    Vector2D& operator*=(const Vector2D& vec);
    Vector2D& operator/=(const Vector2D& vec);

    Vector2D& operator*(const int& i);
    Vector2D& Zero();

    Vector2D normalize() const {
    float length = sqrt(x * x + y * y);
    if (length > 0) {
        return Vector2D(x / length, y / length);
    }
    return Vector2D(0, 0);
}
    
    friend std::ostream& operator << (std::ostream& stream, const Vector2D& vec);

};