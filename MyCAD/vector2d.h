#ifndef VECTOR2D_H
#define VECTOR2D_H

#endif // VECTOR2D_H

#include<iostream>
#include<math.h>

class Vector2D
{
public:
    float x,y;

    Vector2D(){}

    Vector2D(const Vector2D &a):x(a.x),y(a.y){}

    Vector2D(float nx,float ny):x(nx),y(ny){}

    Vector2D &operator =(const Vector2D &a)
    {
        x=a.x;
        y=a.y;
        return *this;
    }

    bool operator ==(const Vector2D &a)
    {
        return x==a.x&&y==a.y;
    }

    bool operator !=(const Vector2D &a)
    {
        return x!=a.x||y!=a.y;
    }

    void zero()
    {
        x=y=0.0f;
    }

    Vector2D operator - () const
    {
        return Vector2D(-x,-y);
    }

    Vector2D operator +(const Vector2D &a) const
    {
        return Vector2D(x+a.x,y+a.y);
    }

    Vector2D operator -(const Vector2D &a) const
    {
        return Vector2D(x-a.x,y-a.y);
    }

    Vector2D operator *(float a) const
    {
        return Vector2D(x*a,y*a);
    }

    Vector2D operator /(float a) const
    {
        float oneOverA=1.0f/a;
        return Vector2D(x*oneOverA,y*oneOverA);
    }

    Vector2D operator +=(const Vector2D &a)
    {
        x+=a.x;
        y+=a.y;
        return *this;
    }

    Vector2D operator -=(const Vector2D &a)
    {
        x-=a.x;
        y-=a.y;
        return *this;
    }

    Vector2D operator *=(float a)
    {
        x*=a;
        y*=a;
        return *this;
    }

    Vector2D operator /=(float a)
    {
        float oneOverA=1.0f/a;
        x*=oneOverA;
        y*=oneOverA;
        return *this;
    }

    void normalize()
    {
        float magsq=x*x+y*y;
        if(magsq>0.0f)
        {
            float oneOverMag=1.0f/sqrt(magsq);
            x*=oneOverMag;
            y=oneOverMag;
        }
    }

    float operator *(const Vector2D &a) const
    {
        return x*a.x+y*a.y;
    }


};
