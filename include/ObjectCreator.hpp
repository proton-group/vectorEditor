#ifndef OBJECTCREATOR_HPP
#define OBJECTCREATOR_HPP
#include <string>
#include "DomainObjects.hpp"

class unknown_object : public std::exception {};

class ObjectCreator
{
public:
    virtual void* createObject(std::string type, int param1, int param2, int param3, int param4) = 0;
    virtual ~ObjectCreator() {};
};

class RectCreator : public ObjectCreator
{
public:
    virtual void* createObject(std::string type, int param1, int param2, int param3, int param4);
};

class LineCreator : public RectCreator
{
public:
    virtual void* createObject(std::string type, int param1, int param2, int param3, int param4);
};

class AllCreator : public LineCreator
{
public:
    virtual void* createObject(std::string type, int param1, int param2, int param3, int param4);
};


#endif