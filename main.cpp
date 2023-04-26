#include "DomainObjects.hpp"
#include "Commands.hpp"
#include "CommandsCreator.hpp"
#include <fstream>
#include "EditorParser.hpp"
#include "Editor.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << argv[1];
    std::ifstream objData(argv[1]);
    std::ifstream cmdData(argv[2]);
    std::fstream outData(argv[3]);
    BaseCommands cmdDb;
    EditorObjectParser objParser(objData);
    Editor mainEditor(objParser);
    EditorCommandParser cmdParser(cmdData, &cmdDb);
    while(auto cmd = cmdParser.getCommands(mainEditor.getObjects()))
    {
        mainEditor.executeCommand(cmd.value());
    }
    EditorOutputObjectParser outParser(outData);
    outParser.writeObjects(mainEditor.getObjects());
    return 0;
}