#ifndef FLOAT2_H
#define FLOAT2_H

#include <string>

class Float2
{
    public:
        Float2();
        Float2(float x, float y);
        virtual ~Float2();

        std::string  toString() const;
        //const Float2 operator+(Float2 const& lhs, Float2 const& rhs);
        Float2& operator+=(Float2 const& rhs);
        Float2& operator-=(Float2 const& rhs);
        //Float2& operator*=(Float2 const& rhs);
        Float2& operator*=(float const& rhs);


        float   getLengthSquared();
        float   getX() const { return m_x; }
        void    setX(float val) { m_x = val; }
        float   getY() const { return m_y; }
        void    setY(float val) { m_y = val; }
    protected:
    private:
        float m_x;
        float m_y;

};

std::ostream& operator<<(std::ostream& os, Float2 const& obj);


const Float2    operator+(Float2 const& lhs, Float2 const& rhs);
const Float2    operator-(Float2 const& lhs, Float2 const& rhs);
//inline const Float2    operator*(Float2 const& lhs, Fgloat2 const& rhs);
const Float2    operator*(Float2 const& lhs, float const& rhs);
#endif // FLOAT2_H
