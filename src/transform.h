#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <math.h>

#include "linear.h"

mat4 mat4Translate (vec3 v);
mat4 mat4Scale (vec3 v);
mat4 mat4Rotate (vec3 v, float t);

mat4 mat4Perspective (float vfov, float aspect, float near, float far);
mat4 mat4LookAt (vec3 camPos, vec3 camTarget, vec3 up);

#endif
