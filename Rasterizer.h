#pragma once
#include <vector>
#include <cmath>
#include <afxwin.h>

struct Vec2f {
    float x, y;
    Vec2f() : x(0), y(0) {}
    Vec2f(float _x, float _y) : x(_x), y(_y) {}
};

struct Vec3f {
    float x, y, w;
    Vec3f() : x(0), y(0), w(1) {}
    Vec3f(float _x, float _y, float _w = 1.0f) : x(_x), y(_y), w(_w) {}
};

struct Matrix3 {
    float m[3][3];
    Matrix3() {
        m[0][0] = 1; m[0][1] = 0; m[0][2] = 0;
        m[1][0] = 0; m[1][1] = 1; m[1][2] = 0;
        m[2][0] = 0; m[2][1] = 0; m[2][2] = 1;
    }
    static Matrix3 Translation(float tx, float ty) {
        Matrix3 r;
        r.m[0][2] = tx;
        r.m[1][2] = ty;
        return r;
    }
    static Matrix3 Rotation(float degrees) {
        Matrix3 r;
        float rad = degrees * 3.14159265358979323846f / 180.0f;
        float c = cosf(rad), s = sinf(rad);
        r.m[0][0] = c; r.m[0][1] = -s; r.m[0][2] = 0;
        r.m[1][0] = s; r.m[1][1] = c; r.m[1][2] = 0;
        r.m[2][0] = 0; r.m[2][1] = 0; r.m[2][2] = 1;
        return r;
    }
    static Matrix3 Scaling(float sx, float sy) {
        Matrix3 r;
        r.m[0][0] = sx; r.m[1][1] = sy;
        return r;
    }
    Matrix3 operator*(const Matrix3& o) const {
        Matrix3 r;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                r.m[i][j] = 0;
                for (int k = 0; k < 3; k++) r.m[i][j] += m[i][k] * o.m[k][j];
            }
        }
        return r;
    }
    Vec3f transform(const Vec3f& v) const {
        Vec3f r;
        r.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.w;
        r.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.w;
        r.w = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.w;
        if (r.w != 0.0f && r.w != 1.0f) {
            r.x /= r.w; r.y /= r.w; r.w = 1.0f;
        }
        return r;
    }
};

class Rasterizer {
public:  
    Rasterizer() {}
    ~Rasterizer() {}

    void PutPixel(CDC& dc, int x, int y, COLORREF color);
    void DrawLineBresenham(CDC& dc, int x0, int y0, int x1, int y1, COLORREF color);
    void DrawCircleMidpoint(CDC& dc, int cx, int cy, int radius, COLORREF color);
    void DrawEllipseMidpoint(CDC& dc, int cx, int cy, int a, int b, COLORREF color);
    void DrawTransformedLine(CDC& dc, const Matrix3& mat, float x0, float y0, float x1, float y1, COLORREF color);
    void DrawTransformedCircle(CDC& dc, const Matrix3& mat, int cx, int cy, int r, COLORREF color);
    void DrawTransformedEllipse(CDC& dc, const Matrix3& mat, int cx, int cy, int a, int b, COLORREF color);
};
