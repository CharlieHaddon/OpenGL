#include "transform.h"

mat4 mat4Translate (vec3 v){
    mat4 x = {
        1, 0, 0, v.x,
        0, 1, 0, v.y,
        0, 0, 1, v.z,
        0, 0, 0, 1
    };
    return x;
}

mat4 mat4Scale (vec3 v){
    mat4 x = {
        v.x, 0,   0,   0,
        0,   v.y, 0,   0,
        0,   0,   v.z, 0,
        0,   0,   0,   1
    };
    return x;
}

mat4 mat4Rotate (vec3 v, float t){
    double cost = cos (t);
    double sint = sin (t);
    double omcost = 1 - cost;

    float a = v.x * v.x * omcost + cost;
    float b = v.y * v.x * omcost - v.z * sint;
    float c = v.z * v.x * omcost + v.y * sint;
    
    float e = v.x * v.y * omcost + v.z * sint;
    float f = v.y * v.y * omcost + cost;
    float g = v.z * v.y * omcost - v.x * sint;

    float i = v.x * v.z * omcost - v.y * sint;
    float j = v.y * v.z * omcost + v.x * sint;
    float k = v.z * v.z * omcost + cost;

    mat4 x = {
        a, b, c, 0,
        e, f, g, 0,
        i, j, k, 0,
        0, 0, 0, 1
    };
    return x;
}

mat4 mat4Perspective (float hfov, float vfov, float near, float far){
    float nearw = near * tan (hfov / 2);
    float nearh = near * tan (vfov / 2);

    float a = (2 * near) / nearw;
    float f = (2 * near) / nearh;
    float k = -(far + near) / (far - near);
    float l = -(2 * far * near) / (far - near);
    float o = -1;

    mat4 x = {
        a, 0, 0, 0,
        0, f, 0, 0,
        0, 0, k, l,
        0, 0, o, 0
    };
    return x;
}
