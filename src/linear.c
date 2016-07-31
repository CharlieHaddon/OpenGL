#include "linear.h"

/* 2D vector */
float vec2Dot (vec2 u, vec2 v){
    float result;
    result = u.x * v.x + u.y * v.y;
    return result;
}

float vec2Mag (vec2 u){
    float result;
    result = sqrt (pow (u.x, 2) + pow (u.y, 2));
    return result;
}

vec2 vec2Norm (vec2 u){
    float mag = vec2Mag (u);
    vec2 result = {u.x / mag, u.y / mag};
    return result;
}

vec2 vec2Add (vec2 u, vec2 v){
    vec2 result = {u.x + v.x, u.y + v.y};
    return result;
}

vec2 vec2Scale (float s, vec2 u){
    vec2 result = {s * u.x, s * u.y};
    return result;
}

/* 3D vector */
float vec3Dot (vec3 u, vec3 v){
    float result;
    result = u.x * v.x + u.y * v.y + u.z * v.z;
    return result;
}

float vec3Mag (vec3 u){
    float result;
    result = sqrt (pow (u.x, 2) + pow (u.y, 2) + pow (u.z, 2));
    return result;
}

vec3 vec3Norm (vec3 u){
    float mag = vec3Mag (u);
    vec3 result = {u.x / mag, u.y / mag, u.z / mag};
    return result;
}

vec3 vec3Add (vec3 u, vec3 v){
    vec3 result = {u.x + v.x, u.y + v.y, u.z + v.z};
    return result;
}

vec3 vec3Scale (float s, vec3 u){
    vec3 result = {s * u.x, s * u.y, s* u.z};
    return result;
}

vec3 vec3Cross (vec3 u, vec3 v){
    vec3 result = {
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    };
    return result;
}

/* 4D vector */
float vec4Dot (vec4 u, vec4 v){
    float result;
    result = u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w;
    return result;
}

float vec4Mag (vec4 u){
    float result;
    result = sqrt (pow (u.x, 2) + pow (u.y, 2) + pow (u.z, 2) + pow (u.w, 2));
    return result;
}

vec4 vec4Norm (vec4 u){
    float mag = vec4Mag (u);
    vec4 result = {u.x / mag, u.y / mag, u.z / mag, u.w / mag};
    return result;
}

vec4 vec4Add (vec4 u, vec4 v){
    vec4 result = {u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w};
    return result;
}

vec4 vec4Scale (float s, vec4 u){
    vec4 result = {s * u.x, s * u.y, s * u.z, s * u.w};
    return result;
}

/* 2x2 matrix */
mat2 mat2Mult (mat2 x, mat2 y){
    float a = x.a * y.a + x.b * y.c;
    float b = x.a * y.b + x.b * y.d;

    float c = x.c * y.a + x.d * y.c;
    float d = x.c * y.b + x.d * y.d;

    mat2 result = {
        a, b,
        c, d
    };
    return result;
}

mat2 mat2Transpose (mat2 x){
    mat2 result = {
        x.a, x.c,
        x.b, x.d
    };
    return result;
}

mat2 mat2Inv (mat2 x){
    float det = mat2Det (x);
    mat2 result = {
        x.d / det, -x.a / det,
       -x.c / det,  x.a / det
    };
    return result;
}

float mat2Det (mat2 x){
    float result;
    result = x.a * x.d - x.b * x.c;
    return result;
}

/* 3x3 matrix */
mat3 mat3Mult (mat3 x, mat3 y){
    float a = x.a * y.a + x.b * y.d + x.c * y.g;
    float b = x.a * y.b + x.b * y.e + x.c * y.h;
    float c = x.a * y.c + x.b * y.f + x.c * y.i;

    float d = x.d * y.a + x.e * y.d + x.f * y.g;
    float e = x.d * y.b + x.e * y.e + x.f * y.h;
    float f = x.d * y.c + x.e * y.f + x.f * y.i;

    float g = x.g * y.a + x.h * y.d + x.i * y.g;
    float h = x.g * y.b + x.h * y.e + x.i * y.h;
    float i = x.g * y.c + x.h * y.f + x.i * y.i;

    mat3 result = {
        a, b, c,
        d, e, f,
        g, h, i
    };
    return result;
}

mat3 mat3Transpose (mat3 x){
    mat3 result = {
        x.a, x.d, x.g,
        x.b, x.e, x.h,
        x.c, x.f, x.i
    };
    return result;
}

mat3 mat3Inv (mat3 x){
    float det = mat3Det (x);
    float a = mat2Det ((mat2){x.e, x.f, x.h, x.i}) / det;
    float b = mat2Det ((mat2){x.f, x.d, x.i, x.g}) / det;
    float c = mat2Det ((mat2){x.d, x.e, x.g, x.h}) / det;
    float d = mat2Det ((mat2){x.h, x.i, x.b, x.c}) / det;
    float e = mat2Det ((mat2){x.i, x.g, x.c, x.a}) / det;
    float f = mat2Det ((mat2){x.g, x.h, x.a, x.b}) / det;
    float g = mat2Det ((mat2){x.b, x.c, x.e, x.f}) / det;
    float h = mat2Det ((mat2){x.c, x.a, x.f, x.d}) / det;
    float i = mat2Det ((mat2){x.a, x.b, x.d, x.e}) / det;

    mat3 result = {
        a, d, g,
        b, e, h,
        c, f, i
    };
    return result;
}

float mat3Det (mat3 x){
    float result;
    mat2 ia = {x.e, x.f, x.h, x.i};
    mat2 ib = {x.f, x.d, x.i, x.g};
    mat2 ic = {x.d, x.e, x.g, x.h};
    result = x.a * mat2Det (ia)
           + x.b * mat2Det (ib)
           + x.c * mat2Det (ic);
    return result;
}

/* 4x4 matrix */
mat4 mat4Mult (mat4 x, mat4 y){
    float a = x.a * y.a + x.b * y.e + x.c * y.i + x.d * y.m;
    float b = x.a * y.b + x.b * y.f + x.c * y.j + x.d * y.n;
    float c = x.a * y.c + x.b * y.g + x.c * y.k + x.d * y.o;
    float d = x.a * y.d + x.b * y.h + x.c * y.l + x.d * y.p;
    
    float e = x.e * y.a + x.f * y.e + x.g * y.i + x.h * y.m;
    float f = x.e * y.b + x.f * y.f + x.g * y.j + x.h * y.n;
    float g = x.e * y.c + x.f * y.g + x.g * y.k + x.h * y.o;
    float h = x.e * y.d + x.f * y.h + x.g * y.l + x.h * y.p;

    float i = x.i * y.a + x.j * y.e + x.k * y.i + x.l * y.m;
    float j = x.i * y.b + x.j * y.f + x.k * y.j + x.l * y.n;
    float k = x.i * y.c + x.j * y.g + x.k * y.k + x.l * y.o;
    float l = x.i * y.d + x.j * y.h + x.k * y.l + x.l * y.p;
    
    float m = x.m * y.a + x.n * y.e + x.o * y.i + x.p * y.m;
    float n = x.m * y.b + x.n * y.f + x.o * y.j + x.p * y.n;
    float o = x.m * y.c + x.n * y.g + x.o * y.k + x.p * y.o;
    float p = x.m * y.d + x.n * y.h + x.o * y.l + x.p * y.p;

    mat4 result = {
        a, b, c, d,
        e, f, g, h,
        i, j, k, l,
        m, n, o, p
    };
    return result;
}

mat4 mat4Transpose (mat4 x){
    mat4 result = {
        x.a, x.e, x.i, x.m,
        x.b, x.f, x.j, x.n,
        x.c, x.g, x.k, x.o,
        x.d, x.h, x.l, x.p
    };
    return result;
}

/* I don't think this function works properly but haven't checked. */
mat4 mat4Inv (mat4 x){
    double ca = x.k * x.p - x.o * x.l;
    double cb = x.j * x.p - x.n * x.l;
    double cc = x.j * x.o - x.n * x.k;
    double cd = x.i * x.p - x.m * x.l;
    double ce = x.i * x.o - x.m * x.k;
    double cf = x.i * x.n - x.m * x.j;
    double cg = x.g * x.p - x.o * x.h;
    double ch = x.f * x.p - x.n * x.h;
    double ci = x.f * x.o - x.n * x.g;
    double cj = x.e * x.p - x.m * x.h;
    double ck = x.e * x.o - x.m * x.g;
    double cl = x.f * x.p - x.n * x.h;
    double cm = x.e * x.n - x.m * x.f;
    double cn = x.g * x.l - x.k * x.h;
    double co = x.f * x.l - x.j * x.h;
    double cp = x.f * x.k - x.j * x.g;
    double cq = x.e * x.l - x.i * x.h;
    double cr = x.e * x.k - x.i * x.g;
    double cs = x.e * x.j - x.i * x.f;

    mat4 r;

    r.a = + (x.f * ca - x.g * cb + x.h * cc);
    r.b = - (x.e * ca - x.g * cd + x.h * ce);
    r.c = + (x.e * cb - x.f * cd + x.h * cf);
    r.d = - (x.e * cc - x.f * ce + x.g * cf);

    r.e = - (x.b * ca - x.c * cb + x.d * cc);
    r.f = + (x.a * ca - x.c * cd + x.d * ce);
    r.g = - (x.a * cb - x.b * cd + x.d * cf);
    r.h = + (x.a * cc - x.b * ce + x.c * cf);

    r.i = + (x.b * cg - x.c * ch + x.d * ci);
    r.j = - (x.a * cg - x.c * cj + x.d * ck);
    r.k = + (x.a * cl - x.b * cj + x.d * cm);
    r.l = - (x.a * ci - x.b * ck + x.c * cm);

    r.m = - (x.b * cn - x.c * co + x.d * cp);
    r.n = + (x.a * cn - x.c * cq + x.d * cr);
    r.o = - (x.a * co - x.b * cq + x.d * cs);
    r.p = + (x.a * cp - x.b * cr + x.c * cs);

    double d =
        + x.a * r.a
        + x.b * r.b
        + x.c * r.c
        + x.d * r.d;

    mat4 result = (mat4){
        r.a / d, r.b / d, r.c / d, r.d / d,
        r.e / d, r.f / d, r.g / d, r.h / d,
        r.i / d, r.j / d, r.k / d, r.l / d,
        r.m / d, r.n / d, r.o / d, r.p / d
    };
    return result;
}

/* This function doesn't do what it's supposed to. */
float mat4Det (mat4 x){
    mat3 ia = {
        x.f, x.g, x.h,
        x.j, x.k, x.l,
        x.n, x.o, x.p
    };
    mat3 ib = {
        x.g, x.h, x.e,
        x.k, x.l, x.i,
        x.o, x.p, x.l
    };
    mat3 ic = {
        x.h, x.e, x.f,
        x.l, x.i, x.j,
        x.p, x.m, x.n
    };
    mat3 id = {
        x.e, x.f, x.g,
        x.i, x.j, x.k,
        x.m, x.n, x.o
    };

    float result = x.a * mat3Det (ia)
                 + x.b * mat3Det (ib)
                 + x.c * mat3Det (ic)
                 + x.d * mat3Det (id);
    return result;
}
