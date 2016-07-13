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
void mat2ToArray (mat2 x, float data[4]){
    /* Needs to be flipped about leading diagonal */
    data[0] = x.a;
    data[1] = x.b;

    data[2] = x.c;
    data[3] = x.d;
}

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

float mat2Det (mat2 x){
    float result;
    result = x.a * x.d - x.b * x.c;
    return result;
}

/* 3x3 matrix */
void mat3ToArray (mat3 x, float data[9]){
    /* Needs to be flipped about leading diagonal */
    data[0] = x.a;
    data[1] = x.b;
    data[2] = x.c;

    data[3] = x.d;
    data[4] = x.e;
    data[5] = x.f;

    data[6] = x.g;
    data[7] = x.h;
    data[8] = x.i;
}

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

float mat3Det (mat3 x){
    float result;
    mat2 ca = {x.e, x.f, x.h, x.i};
    mat2 cb = {x.f, x.d, x.i, x.g};
    mat2 cc = {x.d, x.e, x.g, x.h};
    result = x.a * mat2Det (ca)
           + x.b * mat2Det (cb)
           + x.c * mat2Det (cc);
    return result;
}

/* 4x4 matrix */
void mat4ToArray (mat4 x, float data[16]){
    data[0]  = x.a;
    data[4]  = x.b;
    data[8]  = x.c;
    data[12]  = x.d;

    data[1]  = x.e;
    data[5]  = x.f;
    data[9]  = x.g;
    data[13]  = x.h;

    data[2]  = x.i;
    data[6]  = x.j;
    data[10] = x.k;
    data[14] = x.l;

    data[3] = x.m;
    data[7] = x.n;
    data[11] = x.o;
    data[15] = x.p;
}

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
