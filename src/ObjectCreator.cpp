#include "ObjectCreator.hpp"

void* RectCreator::createObject(std::string type, int param1, int param2, int param3, int param4)
{
    if(type == "rect")
    {
        return new Rectangle(param1, param2, param3, param4);
    }
    else
    {
        throw unknown_object();
    }
    return 0;
}

void* LineCreator::createObject(std::string type, int param1, int param2, int param3, int param4)
{
    if(type == "line")
    {
        return new Line(param1, param2, param3, param4);
    }
    return RectCreator::createObject(type, param1, param2, param3, param4);
}

void* AllCreator::createObject(std::string type, int param1, int param2, int param3, int param4)
{
    if(type == "ellipse")
    {
        return new Ellipse(param1, param2, param3, param4);
    }
    return LineCreator::createObject(type, param1, param2, param3, param4);
}