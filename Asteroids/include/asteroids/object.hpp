#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <memory>

static constexpr float deg2Rad = 3.14159/180;

template <class T = float>
struct Position
{
    T x_, y_;
    int angle_;
    Position()
    {
        x_ = 0;
        y_ = 0;
        angle_ = 0;
    }
    Position(T x, T y )
    {
        x_ = x;
        y_ = y;
    }
    Position(T x, T y, float angle)
    {
        x_ = x;
        y_ = y;
        angle_ = angle;
    }
    
};

template <class T = float>
class Object
{
    public:
    Position<> position_;
    float dx = 0;
    float dy = 0;
    float speed = 0;
    

    Object()
    {
        position_ = Position<>();
    }
    Object(const T& x, const T& y)
    {
        position_ = Position<float>(x,y);
    }
    Object(const T& x, const T& y, const float& angle)
    {
        position_ = Position<T>(x,y, angle);
    }

    const Position<> getPosition() const 
    {
        return position_;
    }
};


#endif