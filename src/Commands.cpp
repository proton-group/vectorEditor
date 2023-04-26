#include "Commands.hpp"
void TwoPointsShapeTranslate::Execute()
{
    Point newFirstPoint, newSecondPoint;
    newFirstPoint.setX(TwoPointsShapeObject->getFirstPoint().getX() + dx);
    newFirstPoint.setY(TwoPointsShapeObject->getFirstPoint().getY() + dy);
    newSecondPoint.setX(TwoPointsShapeObject->getSecondPoint().getX() + dx);
    newSecondPoint.setY(TwoPointsShapeObject->getSecondPoint().getY() + dy);
    TwoPointsShapeObject->setFirstPoint(newFirstPoint);
    TwoPointsShapeObject->setSecondPoint(newSecondPoint);
}

void TwoPointsShapeTranslate::unExecute()
{
    Point newFirstPoint, newSecondPoint;
    newFirstPoint.setX(TwoPointsShapeObject->getFirstPoint().getX() - dx);
    newFirstPoint.setY(TwoPointsShapeObject->getFirstPoint().getY() - dy);
    newSecondPoint.setX(TwoPointsShapeObject->getSecondPoint().getX() - dx);
    newSecondPoint.setY(TwoPointsShapeObject->getSecondPoint().getY() - dy);
    TwoPointsShapeObject->setFirstPoint(newFirstPoint);
    TwoPointsShapeObject->setSecondPoint(newSecondPoint);
}

void TwoPointsShapeRotate::Execute()
{
    Point newFirstPoint, newSecondPoint;
    newFirstPoint.setX(round(TwoPointsShapeObject->getFirstPoint().getX() * cos(angle) - TwoPointsShapeObject->getFirstPoint().getY() * sin(angle)));
    newFirstPoint.setY(round(TwoPointsShapeObject->getFirstPoint().getY() * cos(angle) + TwoPointsShapeObject->getFirstPoint().getX() * sin(angle)));
    newSecondPoint.setX(round(TwoPointsShapeObject->getSecondPoint().getX() * cos(angle) - TwoPointsShapeObject->getSecondPoint().getY() * sin(angle)));
    newSecondPoint.setY(round(TwoPointsShapeObject->getSecondPoint().getY() * cos(angle) + TwoPointsShapeObject->getSecondPoint().getX() * sin(angle)));
    TwoPointsShapeObject->setFirstPoint(newFirstPoint);
    TwoPointsShapeObject->setSecondPoint(newSecondPoint);
}

void TwoPointsShapeRotate::unExecute()
{
    Point newFirstPoint, newSecondPoint;
    newFirstPoint.setX(TwoPointsShapeObject->getFirstPoint().getX() * cos(angle) + TwoPointsShapeObject->getFirstPoint().getY() * sin(angle));
    newFirstPoint.setY(TwoPointsShapeObject->getFirstPoint().getY() * cos(angle) - TwoPointsShapeObject->getFirstPoint().getX() * sin(angle));
    newSecondPoint.setX(TwoPointsShapeObject->getSecondPoint().getX() * cos(angle) + TwoPointsShapeObject->getSecondPoint().getY() * sin(angle));
    newSecondPoint.setY(TwoPointsShapeObject->getSecondPoint().getY() * cos(angle) - TwoPointsShapeObject->getSecondPoint().getX() * sin(angle));
    TwoPointsShapeObject->setFirstPoint(newFirstPoint);
    TwoPointsShapeObject->setSecondPoint(newSecondPoint);
}

void TwoPointsShapeScale::Execute()
{
    Point newFirstPoint, newSecondPoint;
    newFirstPoint.setX(TwoPointsShapeObject->getFirstPoint().getX() * sx);
    newFirstPoint.setY(TwoPointsShapeObject->getFirstPoint().getY() * sy);
    newSecondPoint.setX(TwoPointsShapeObject->getSecondPoint().getX() * sx);
    newSecondPoint.setY(TwoPointsShapeObject->getSecondPoint().getY() * sy);
    TwoPointsShapeObject->setFirstPoint(newFirstPoint);
    TwoPointsShapeObject->setSecondPoint(newSecondPoint);
}

void TwoPointsShapeScale::unExecute()
{
    Point newFirstPoint, newSecondPoint;
    newFirstPoint.setX(TwoPointsShapeObject->getFirstPoint().getX() / sx);
    newFirstPoint.setY(TwoPointsShapeObject->getFirstPoint().getY() / sy);
    newSecondPoint.setX(TwoPointsShapeObject->getSecondPoint().getX() / sx);
    newSecondPoint.setY(TwoPointsShapeObject->getSecondPoint().getY() / sy);
    TwoPointsShapeObject->setFirstPoint(newFirstPoint);
    TwoPointsShapeObject->setSecondPoint(newSecondPoint);
}

void EllipseTranslate::Execute()
{
    EllipseObject->setPosition((EllipseObject->getPosition()).getX()+dx, (EllipseObject->getPosition()).getY()+dy);
}

void EllipseTranslate::unExecute()
{
    EllipseObject->setPosition((EllipseObject->getPosition()).getX()-dx, (EllipseObject->getPosition()).getY()-dy);
}

void EllipseRotate::Execute()
{
    EllipseObject->setPosition((EllipseObject->getPosition()).getX()*cos(angle) - (EllipseObject->getPosition()).getY() * sin(angle), (EllipseObject->getPosition()).getX()*sin(angle) + (EllipseObject->getPosition()).getY() * cos(angle));
}

void EllipseRotate::unExecute()
{
    EllipseObject->setPosition((EllipseObject->getPosition()).getX()*cos(angle) + (EllipseObject->getPosition()).getY() * sin(angle), -1*(EllipseObject->getPosition()).getX()*sin(angle) - (EllipseObject->getPosition()).getY() * cos(angle));
}

void EllipseScale::Execute()
{
    EllipseObject->setScale(EllipseObject->getWeight()*sx, EllipseObject->getHeight()*sy);
}

void EllipseScale::unExecute()
{
    EllipseObject->setScale(EllipseObject->getWeight()/sx, EllipseObject->getHeight()/sy);
}