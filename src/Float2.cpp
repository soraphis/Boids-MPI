#include "Float2.h"

#include <sstream>

static Float2* tmp_e = new Float2(0, 0);

Float2::Float2()  : m_x(0), m_y(0)
{
    //ctor
}

Float2::Float2(float x, float y) : m_x(x), m_y(y)
{
}

Float2::~Float2()
{
    //dtor
}

bool Float2::inRange(Float2 *to, float range){
	if(this->m_x - to->m_x > range) return false;
	if(this->m_y - to->m_y > range) return false;
	tmp_e->setX( (this->m_x - to->m_x) );
	tmp_e->setY(this->m_y - to->m_y);
	//float r = (((*to)-=(*this)).getLengthSquared());
	if(tmp_e->getLengthSquared() > range) return false;
	return true;
}

std::string Float2::toString() const{
    std::ostringstream a;
    a << "(" << m_x << ", " << m_y << ")";
    return  a.str();
}

float Float2::getLengthSquared(){
    return this->m_x*this->m_x + this->m_y*this->m_y;
}

Float2&         Float2::operator+=(Float2 const& rhs){
    this->m_x += rhs.getX();
    this->m_y += rhs.getY();
    return *this;
}

Float2&         Float2::operator-=(Float2 const& rhs){
    this->m_x -= rhs.getX();
    this->m_y -= rhs.getY();
    return *this;
}
//Float2&         Float2::operator*=(Float2 const& rhs){
//    this->m_x -= rhs.getX();
//    this->m_y -= rhs.getY();
//    return *this;
//}

Float2&         Float2::operator*=(float const& rhs){
    this->m_x *= rhs;
    this->m_y *= rhs;
    return *this;
}

const Float2    operator+(Float2 const& lhs, Float2 const& rhs){
    Float2 tmp(lhs);
    tmp += rhs;
    return tmp;
}

const Float2    operator-(Float2 const& lhs, Float2 const& rhs){
    Float2 tmp(lhs);
    tmp -= rhs;
    return tmp;
}
// do not implement ... either cross or dot
//const Float2    operator*(Float2 const& lhs, Float2 const& rhs){
//    // cross product !
//    Float2 tmp(lhs.getY(), - rhs.getX());
//    return tmp;
//}
const Float2    operator*(Float2 const& lhs, float const& rhs){
    Float2 tmp(lhs);
    tmp *= rhs;
    return tmp;
}

std::ostream& operator<<(std::ostream& os, Float2 const& obj){
    return os << "(" << obj.getX() << ", " << obj.getY() << ")";
}
