#ifndef EDITOR_PARSER_HPP
#define EDITOR_PARSER_HPP
#include <istream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include "Commands.hpp"
#include "CommandsCreator.hpp"
#include "ObjectCreator.hpp"
#include <utility>
#include <optional>

class object_not_found : public std::exception {};

class CommandsAndObjectsDatabase
{
public:
    virtual std::vector<Command*> getCommand(std::string commandName, std::unordered_map<std::string, void*>& objects) = 0;
    virtual ~CommandsAndObjectsDatabase() {}
};

class BaseCommands final : public CommandsAndObjectsDatabase
{
    std::unordered_map<std::string, CommandsCreator*> CommandsDatabase;
public:
    BaseCommands();
    virtual std::vector<Command*> getCommand(std::string commandName, std::unordered_map<std::string, void*>& objects);
    ~BaseCommands();
};

class EditorObjectParser
{
    std::istream& objectList;
    //TODO:
    //unordered
    //id: type + name
    //объединить объекты одним типом с методом stream;
    //вынести в сцену
public:
    EditorObjectParser(std::istream& _objectList) : objectList(_objectList) {}
    virtual std::optional<std::pair<std::string, void*>> getObjects() const;
    virtual ~EditorObjectParser() {};
};

class EditorCommandParser
{
    std::istream& code;
    CommandsAndObjectsDatabase* commandsDb;
public:
    EditorCommandParser(std::istream& _code, CommandsAndObjectsDatabase* _commandsDb) : code(_code), commandsDb(_commandsDb){}
    virtual std::optional<std::vector<Command*>> getCommands(std::unordered_map<std::string, void*>& objects);
    virtual ~EditorCommandParser() {}
};

class EditorOutputObjectParser
{
    std::ostream& objectList;
public:
    EditorOutputObjectParser(std::ostream& _objectList) : objectList(_objectList) {}
    void writeObjects(std::unordered_map<std::string, void*>& objects)
    {
        std::for_each(objects.begin(), objects.end(), [&](std::pair<std::string, void*> objectPair)
        {
            auto& object = objectPair.second;
            auto& name = objectPair.first;
            objectList << ((EditorObject*) object)->getObjectName() << "[" << name << "]" << " " << ((EditorObject*) object)->getObjectParams() << "\n";
        });
    }
    class unknown_object : public std::exception {};
    virtual ~EditorOutputObjectParser() {};
};
#endif