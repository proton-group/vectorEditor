#ifndef DOMAIN_OBJECTS
#define DOMAIN_OBJECTS
#include <string>

class EditorObject
{
public:
    virtual std::string getObjectName()
    {
        return "unnamed";
    };
    virtual std::string getObjectParams()
    {
        return "non params";
    }
    virtual ~EditorObject() {}
};

class Point final
{
    int x;
    int y;
public:
    Point() = default;
    Point(int _x, int _y) : x(_x), y(_y) {}
    int getX() const
    {
        return x;
    }
    int getY() const
    {
        return y;
    }
    void setX(int _x)
    {
        x = _x;
    }
    void setY(int _y)
    {
        y = _y;
    }
};

class TwoPointsShape : public EditorObject
{
    std::string id;
    Point position1;
    Point position2;
public:
    Point getFirstPoint() const
    {
        return position1;
    }
    Point getSecondPoint() const
    {
        return position2;
    }
    void setFirstPoint(const Point& pos1)
    {
        position1 = pos1;
    }
    void setSecondPoint(const Point& pos2)
    {
        position2 = pos2;
    }
    virtual ~TwoPointsShape() {};
};

class Rectangle final : public TwoPointsShape
{
public:
    Rectangle(int x1, int y1, int x2, int y2)
    {
        setFirstPoint(Point(x1, y1));
        setSecondPoint(Point(x2, y2));
    }
    virtual std::string getObjectName()
    {
        return "rect";
    }
    virtual std::string getObjectParams()
    {
        return std::to_string(getFirstPoint().getX()) + " " + std::to_string(getFirstPoint().getY()) + " " + std::to_string(getSecondPoint().getX()) + " " + std::to_string(getSecondPoint().getY());
    }
};

class Line final : public TwoPointsShape
{
public:
    Line(int x1, int y1, int x2, int y2)
    {
        setFirstPoint(Point(x1, y1));
        setSecondPoint(Point(x2, y2));
    }
    virtual std::string getObjectName()
    {
        return "line";
    }
    virtual std::string getObjectParams()
    {
        return std::to_string(getFirstPoint().getX()) + " " + std::to_string(getFirstPoint().getY()) + " " + std::to_string(getSecondPoint().getX()) + " " + std::to_string(getSecondPoint().getY());
    }
};

class Ellipse final : public EditorObject
{
    Point position;
    int weight;
    int height;
public:
    virtual std::string getObjectName()
    {
        return "ellipse";
    }
    Ellipse(int x, int y, int w, int h)
    {
        position = Point(x, y);
        weight = w;
        height = h;
    }
    void setPosition(int x, int y)
    {
        position = Point(x, y);
    }
    void setScale(int w, int h)
    {
        weight = w;
        height = h;
    }
    Point getPosition()
    {
        return position;
    }
    int getWeight()
    {
        return weight;
    }
    int getHeight()
    {
        return height;
    }
    virtual std::string getObjectParams()
    {
        return std::to_string(getPosition().getX()) + " " + std::to_string(getPosition().getY()) + " " + std::to_string(getWeight()) + " " + std::to_string(getHeight());
    }
};
#endif