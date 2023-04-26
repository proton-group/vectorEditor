#include "EditorParser.hpp"
BaseCommands::BaseCommands()
{
    CommandsDatabase["translate rect"] = new CreateTwoPointsShapeTranslate();
    CommandsDatabase["translate line"] = new CreateTwoPointsShapeTranslate();
    CommandsDatabase["translate ellipse"] = new CreateEllipseTranslate();
    CommandsDatabase["scale rect"] = new CreateTwoPointsShapeScale();
    CommandsDatabase["scale line"] = new CreateTwoPointsShapeScale();
    CommandsDatabase["scale ellipse"] = new CreateEllipseScale();
    CommandsDatabase["rotate rect"] = new CreateTwoPointsShapeRotate();
    CommandsDatabase["rotate line"] = new CreateTwoPointsShapeRotate();
    CommandsDatabase["rotate ellipse"] = new CreateEllipseRotate();
    CommandsDatabase["rotate"] = new RotateAll();
    CommandsDatabase["scale"] = new ScaleAll();
    CommandsDatabase["translate"] = new TranslateAll();
    CommandsDatabase["undo"] = new Undo();
}

BaseCommands::~BaseCommands()
{
    for (auto data : CommandsDatabase)
    {
        delete data.second;
    }
}
std::optional<std::pair<std::string, void*>> EditorObjectParser::getObjects() const
{
    std::string line;
    if(std::getline(objectList, line))
    {
        auto pos = line.find_first_of("[");
        std::string type, name, param1, param2, param3, param4;
        if(pos != std::string::npos)
        {
            type = line.substr(0, pos);
            auto pos2 = line.find_first_of("]", pos);
            name = line.substr(pos+1, pos2-pos-1);
            pos = line.find_first_of(" ", pos2+2);
            param1 = line.substr(pos2+2, pos-(pos2+2));
            pos2 = line.find_first_of(" ", pos+1);
            param2 = line.substr(pos+1, pos2-(pos+1));
            pos = line.find_first_of(" ", pos2+1);
            param3 = line.substr(pos2+1, pos-(pos2+1));
            pos2 = line.find_first_of(" ", pos+1);
            param4 = line.substr(pos+1, line.size()-1);
        }
        else
        {
            throw unknown_object(); 
        }
        AllCreator creator;
        return std::optional<std::pair<std::string, void*>>(std::pair(name, creator.createObject(type, std::stoi(param1), std::stoi(param2), std::stoi(param3), std::stoi(param4))));
    }
    return std::nullopt;
}

std::vector<Command*> BaseCommands::getCommand(std::string commandName, std::unordered_map<std::string, void*>& objects)
{
    auto pos = commandName.find_first_of("[");
    std::string command, object, param;
    std::unordered_map<std::string, void*>::iterator objIter;
    if(pos != std::string::npos)
    {
        command = commandName.substr(0, pos);
        auto pos2 = commandName.find_first_of("]");
        object = commandName.substr(pos+1, pos2-pos-1);
        param = commandName.substr(pos2+2, commandName.size());
        objIter = objects.find(object);
    }
    else
    {
        pos = commandName.find_first_of(" ");
        object = "";
        command = commandName.substr(0, pos);
        param = commandName.substr(pos+1, commandName.size());
        objIter = objects.begin();
    }
    if(objIter == objects.end())
    {
        throw object_not_found();
    }
    //итераторы
    CommandDto commandInfo = {objIter, objects.end(), param};
    return CommandsDatabase.at(command)->createCommand(commandInfo);
}

std::optional<std::vector<Command*>> EditorCommandParser::getCommands(std::unordered_map<std::string, void*>& objects)
{
    std::string line;
    if(std::getline(code, line))
    {
        return std::optional(commandsDb->getCommand(line, objects));
    }
    return std::nullopt;
}