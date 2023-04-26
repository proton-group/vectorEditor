#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <memory>
#include "DomainObjects.hpp"
#include "math.h"

class Command
{
public:
    virtual void Execute() = 0;
    virtual void unExecute() = 0;
    virtual ~Command() {};
};

class TwoPointsShapeTranslate final : public Command
{
    TwoPointsShape* TwoPointsShapeObject; 
    int dx;
    int dy;
public:
    TwoPointsShapeTranslate(TwoPointsShape* object, int _dx, int _dy) : TwoPointsShapeObject(object), dx(_dx), dy(_dy) {}
    virtual void Execute();
    virtual void unExecute();
};

class TwoPointsShapeRotate final : public Command
{
    TwoPointsShape* TwoPointsShapeObject;
    float angle; 
public:
    TwoPointsShapeRotate(TwoPointsShape* object, float _angle) : TwoPointsShapeObject(object), angle(_angle) {}
    virtual void Execute();
    virtual void unExecute();
};

class TwoPointsShapeScale final : public Command
{
    TwoPointsShape* TwoPointsShapeObject;
    float sx;
    float sy;
public:
    TwoPointsShapeScale(TwoPointsShape* object, float _sx, float _sy) : TwoPointsShapeObject(object), sx(_sx), sy(_sy) {}
    virtual void Execute();
    virtual void unExecute();
};

class EllipseTranslate final : public Command
{
    Ellipse* EllipseObject;
    int dx;
    int dy;
public:
    EllipseTranslate(Ellipse* object, int _dx, int _dy) : EllipseObject(object), dx(_dx), dy(_dy) {}
    virtual void Execute();
    virtual void unExecute();
};

class EllipseRotate final : public Command
{
    Ellipse* EllipseObject; 
    float angle;
public:
    EllipseRotate(Ellipse* object, float _angle) : EllipseObject(object), angle(_angle) {}
    virtual void Execute();
    virtual void unExecute();
};

class EllipseScale final : public Command
{
    Ellipse* EllipseObject; 
    int sx;
    int sy;
public:
    EllipseScale(Ellipse* object, int _sx, int _sy) : EllipseObject(object), sx(_sx), sy(_sy) {}
    virtual void Execute();
    virtual void unExecute();
};

#endif 