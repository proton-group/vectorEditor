#ifndef EDITOR_HPP
#define EDITOR_HPP
#include <vector>
#include "DomainObjects.hpp"
#include "Commands.hpp"
#include "CommandsCreator.hpp"
#include <algorithm>
#include <unordered_map>
#include "EditorParser.hpp"

class Editor final
{
    std::vector<Command*> commands;
    std::unordered_map<std::string, void*> objects;
public:
    Editor(const EditorObjectParser& objParser);
    void executeCommand(std::vector<Command*> cmd);
    void undo();
    std::unordered_map<std::string, void*>& getObjects()
    {
        return objects;
    }
    ~Editor();
};
#endif