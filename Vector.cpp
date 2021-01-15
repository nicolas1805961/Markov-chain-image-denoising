#include "Vector.hpp"

Vector::Vector(){}

Vector::Vector(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector::Vector(float f)
{
    this->x = f;
    this->y = f;
    this->z = f;
}

float& Vector::operator[](int i) 
{
    if (i == 0)
        return x;
    else if (i == 1)
        return y;
    else if (i == 2)
        return z;
}

float Vector::operator[](int i) const
{
    if (i == 0)
        return x;
    else if (i == 1)
        return y;
    else if (i == 2)
        return z;
}

Vector& Vector::operator/=(float const &rhs)
{
    this->x /= rhs;
    this->y /= rhs;
    this->z /= rhs;
    return *this;
}

Vector Vector::operator*(std::vector<Vector> const &rhs)
{
    Vector res(0);
    res.x = this->x *rhs[0].x + this->y *rhs[0].y + this->z *rhs[0].z;
    res.y = this->x *rhs[1].x + this->y *rhs[1].y + this->z *rhs[1].z;
    res.z = this->x *rhs[2].x + this->y *rhs[2].y + this->z *rhs[2].z;
    return res;
}

float Vector:: max_component()
{
    return std::max(this->x, std::max(this->y, this->z));
}

Vector Vector::operator+(Vector const &rhs)
{
    return Vector(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
}

Vector& Vector::operator+=(Vector const &rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Vector Vector::operator+(Vector const &rhs) const
{
    return Vector(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
}

Vector Vector::operator-(Vector const &rhs)
{
    return Vector(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
}

Vector Vector::operator-(Vector const &rhs) const
{
    return Vector(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
}

float Vector::dot_product(Vector const &rhs)
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

float Vector::dot_product(Vector const &rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

Vector Vector::cross_product(Vector const &rhs)
{
    return Vector(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}

Vector Vector::cross_product(Vector const &rhs) const
{
    return Vector(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}

float Vector::norm()
{
    return sqrt(this->dot_product(*this));
}

float Vector::norm() const
{
    return sqrt(this->dot_product(*this));
}

Vector Vector::normalize()
{
    return (*this)*(1/norm());
}

Vector Vector::normalize() const
{
    return (*this)*(1/norm());
}

float Vector::get_x()
{
    return x;
}

float Vector::get_y() const
{
    return y;
}

float Vector::get_z() const
{
    return z;
}

float Vector::get_y()
{
    return y;
}

void Vector::set_y(float y)
{
    this->y = y;
}

float Vector::get_z()
{
    return z;
}


float Vector::get_x() const
{
    return x;
}
Vector::~Vector(){}

bool operator!=(Vector const &left, Vector const &right) 
{
    return !(left[0] == right[0] && left[1] == right[1] && left[2] == right[2]);
}

Vector operator*(Vector const& lhs, Vector const& rhs) 
{
    Vector res;
    res.x = lhs.get_x() * rhs.get_x();
    res.y = lhs.get_y() * rhs.get_y();
    res.z = lhs.get_z() * rhs.get_z();
    return res;
}

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}
Vector operator*(float scalar, Vector const& rhs)
{
    return Vector(scalar * rhs.x, scalar * rhs.y, scalar * rhs.z);
}

Vector operator*(Vector const& lhs, float scalar)
{
    return Vector(scalar * lhs.x, scalar * lhs.y, scalar * lhs.z);
}

Vector operator*(std::vector<Vector> const &lhs, const Vector& rhs)
{
    Vector res(0);
    res.x = lhs[0].x * rhs.x + lhs[1].x * rhs.y + lhs[2].x * rhs.z;
    res.y = lhs[0].y * rhs.x + lhs[1].y * rhs.y + lhs[2].y * rhs.z;
    res.z = lhs[0].z * rhs.x + lhs[1].z * rhs.y + lhs[2].z * rhs.z;
    return res;
}

bool operator==(Vector const &left, float right)
{
    return (left.x == right && left.y == right && left.z == right);
}

bool operator<(Vector const &left, Vector const &right)
{
    return left.norm() < right.norm();
}

Vector& Vector::operator*=(float rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

/*Vector operator+(Vector lhs, Vector const& rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    return lhs;
}*/

Vector operator/(Vector const& lhs, float scalar)
{
    return Vector(lhs.x / scalar, lhs.y / scalar, lhs.z / scalar);
}