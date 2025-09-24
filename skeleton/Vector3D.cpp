#include "Vector3D.h"

Vector3D::Vector3D() : _x(0), _y(0), _z(0){
}

Vector3D::Vector3D(float a): _x(a), _y(a), _z(a){
}

Vector3D::Vector3D(float x, float y, float z) : _x(x), _y(y), _z(z){
}

Vector3D Vector3D::normalize()
{
    
    return Vector3D();
}

float Vector3D::magnitude(){
    // sqrt((x^2)+(y^2)+(z^2))
    return std::sqrt((_x * _x) + (_y * _y) + (_z * _z));
}
