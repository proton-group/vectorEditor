#ifndef COMMANDSCREATOR_HPP
#define COMMANDSCREATOR_HPP
#include "Commands.hpp"
#include <unordered_map>
#include <vector>
#include <algorithm>

//Добавить dto
struct CommandDto final
{
    std::unordered_map<std::string, void*>::iterator objIterBegin;
    std::unordered_map<std::string, void*>::iterator objIterEnd;
    std::string objectData;
};

class CommandsCreator
{
public:
    virtual std::vector<Command*> createCommand(CommandDto& commandInfo) = 0;
    virtual ~CommandsCreator() {}
};

class Undo final : public CommandsCreator
{
public:
    virtual std::vector<Command*> createCommand(CommandDto& commandInfo)
    {
        return std::vector<Command*>();
    }
};

class CreateTwoPointsShapeTranslate final : public CommandsCreator
{
public:
    virtual std::vector<Command*> createCommand(CommandDto& commandInfo)
    {
        auto& objectData = commandInfo.objectData;
        auto pos = objectData.find_first_of(" ");
        return std::vector<Command*>{new TwoPointsShapeTranslate((TwoPointsShape*)(*(commandInfo.objIterBegin)).second, std::stoi(objectData.substr(0, pos)), std::stoi(objectData.substr(pos+1, objectData.size())))};
    }
};

class CreateTwoPointsShapeRotate final : public CommandsCreator
{
public:

    virtual std::vector<Command*> createCommand(CommandDto& commandInfo)
    {
        auto& objectData = commandInfo.objectData;
        return std::vector<Command*>{new TwoPointsShapeRotate((TwoPointsShape*)(*(commandInfo.objIterBegin)).second, std::stof(objectData) * M_PI / 180)};
    }
};

class CreateTwoPointsShapeScale final : public CommandsCreator
{
public:
    virtual std::vector<Command*> createCommand(CommandDto& commandInfo)
    {
        auto& objectData = commandInfo.objectData;
        auto pos = objectData.find_first_of(" ");
        return std::vector<Command*>{new TwoPointsShapeScale((TwoPointsShape*)(*(commandInfo.objIterBegin)).second, std::stof(objectData.substr(0, pos)), std::stof(objectData.substr(pos+1, objectData.size())))};
    }
};

class CreateEllipseRotate final : public CommandsCreator
{
public:
    virtual std::vector<Command*> createCommand(CommandDto& commandInfo)
    {
        auto& objectData = commandInfo.objectData;
        return std::vector<Command*>{new EllipseRotate((Ellipse*)(*(commandInfo.objIterBegin)).second, std::stof(objectData) * M_PI / 180)};
    }
};

class CreateEllipseTranslate final : public CommandsCreator
{
public:
    virtual std::vector<Command*> createCommand(CommandDto& commandInfo)
    {
        auto& objectData = commandInfo.objectData;
        auto pos = objectData.find_first_of(" ");
        return std::vector<Command*>{new EllipseTranslate((Ellipse*)(*(commandInfo.objIterBegin)).second, std::stoi(objectData.substr(0, pos-1)), std::stoi(objectData.substr(pos+1, objectData.size())))};
    }
};

class CreateEllipseScale final : public CommandsCreator
{
public:
    virtual std::vector<Command*> createCommand(CommandDto& commandInfo)
    {
        auto& objectData = commandInfo.objectData;
        auto pos = objectData.find_first_of(" ");
        return std::vector<Command*>{new EllipseScale((Ellipse*)(*(commandInfo.objIterBegin)).second, std::stoi(objectData.substr(0, pos-1)), std::stoi(objectData.substr(pos+1, objectData.size())))};
    }
};
class RotateAll final : public CommandsCreator
{
public:
    virtual std::vector<Command*> createCommand(CommandDto& commandInfo)
    {
        std::vector<Command*> commands;
        std::unordered_map<std::string, void*>::iterator objects = commandInfo.objIterBegin;
        CommandDto commandInfoLocal;
        std::for_each(commandInfo.objIterBegin, commandInfo.objIterEnd, [&](std::pair<std::string, void*> objectPair)
        {
            auto& object = objectPair.second;
            commandInfoLocal = {objects, commandInfo.objIterEnd, commandInfo.objectData};
            if(((EditorObject*)object)->getObjectName() == "line" || ((EditorObject*)object)->getObjectName() == "rect")
            {
                CreateTwoPointsShapeRotate command;
                commands.push_back(command.createCommand(commandInfoLocal).back());
            }
            if(((EditorObject*)object)->getObjectName() == "ellipse")
            {
                CreateEllipseRotate command;
                commands.push_back(command.createCommand(commandInfoLocal).back());
            }
            objects++;
        });
        return commands;
    }
};

class TranslateAll final : public CommandsCreator
{
    virtual std::vector<Command*> createCommand(CommandDto& commandInfo)
    {
        std::vector<Command*> commands;
        std::unordered_map<std::string, void*>::iterator objects = commandInfo.objIterBegin;
        CommandDto commandInfoLocal;
        std::for_each(commandInfo.objIterBegin, commandInfo.objIterEnd, [&](std::pair<std::string, void*> objectPair)
        {
            auto& object = objectPair.second;
            commandInfoLocal = {objects, commandInfo.objIterEnd, commandInfo.objectData};
            if(((EditorObject*)object)->getObjectName() == "line" || ((EditorObject*)object)->getObjectName() == "rect")
            {
                CreateTwoPointsShapeTranslate command;
                commands.push_back(command.createCommand(commandInfoLocal).back());
            }
            if(((EditorObject*)object)->getObjectName() == "ellipse")
            {
                CreateEllipseTranslate command;
                commands.push_back(command.createCommand(commandInfoLocal).back());
            }
            objects++;
        });
        return commands;
    }
};

class ScaleAll final : public CommandsCreator
{
    virtual std::vector<Command*> createCommand(CommandDto& commandInfo)
    {
        std::vector<Command*> commands;
        std::unordered_map<std::string, void*>::iterator objects = commandInfo.objIterBegin;
        CommandDto commandInfoLocal;
        std::for_each(commandInfo.objIterBegin, commandInfo.objIterEnd, [&](std::pair<std::string, void*> objectPair)
        {
            auto& object = objectPair.second;
            commandInfoLocal = {objects, commandInfo.objIterEnd, commandInfo.objectData};
            if(((EditorObject*)object)->getObjectName() == "line" || ((EditorObject*)object)->getObjectName() == "rect")
            {
                CreateTwoPointsShapeScale command;
                commands.push_back(command.createCommand(commandInfoLocal).back());
            }
            if(((EditorObject*)object)->getObjectName() == "ellipse")
            {
                CreateEllipseScale command;
                commands.push_back(command.createCommand(commandInfoLocal).back());
            }
            objects++;
        });
        return commands;
    }
};
#endif