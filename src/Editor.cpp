#include "Editor.hpp"

Editor::Editor(const EditorObjectParser& objParser)
{
    while(auto obj = objParser.getObjects())
    {
        objects.insert(obj.value());
    }
}

void Editor::executeCommand(std::vector<Command*> cmd)
{
    if(cmd.size() == 0)
    {
        this->undo();
        return;
    }
    std::for_each(cmd.begin(), cmd.end(), [&](Command* command)
    {
        commands.push_back(command);
        command->Execute();
    });
}

void Editor::undo()
{
    if(commands.empty())
    {
        return;
    }
    auto cmd = commands.back();
    cmd->unExecute();
    delete cmd;
    commands.pop_back();
}

Editor::~Editor()
{
    for (auto data : commands)
    {
        delete data;
    }
    for (auto data : objects)
    {
        delete (EditorObject*) data.second;
    }
}