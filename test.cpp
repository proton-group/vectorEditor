#include "DomainObjects.hpp"
#include "Commands.hpp"
#include "CommandsCreator.hpp"
#include <fstream>
#include "EditorParser.hpp"
#include "Editor.hpp"
#include <iostream>
#include <gtest/gtest.h>
#include <string>

TEST(base, InvalidObject)
{
    std::stringstream objData;
    objData << "aboba[4] 0 5 6 2";
    //BaseCommands cmdDb;
    EditorObjectParser objParser(objData);
    ASSERT_THROW(Editor mainEditor(objParser), unknown_object);
}

TEST(base, InvalidData)
{
    std::stringstream objData;
    objData << "aboba[4] 0 f d 2";
    //BaseCommands cmdDb;
    EditorObjectParser objParser(objData);
    ASSERT_THROW(Editor mainEditor(objParser), std::invalid_argument);
}

TEST(base, InvalidCommand)
{
    std::stringstream objData, cmdData;
    objData << "rect[4] 0 5 6 2";
    cmdData << "aboba aboba[4] 232323 2323 2323";
    BaseCommands cmdDb;
    EditorObjectParser objParser(objData);
    EditorCommandParser cmdParser(cmdData, &cmdDb);
    Editor mainEditor(objParser);
    ASSERT_THROW(auto cmd = cmdParser.getCommands(mainEditor.getObjects()), std::out_of_range);
}

TEST(commands, translate)
{
    std::stringstream objData, cmdData, outData;
    objData << "rect[4] 2 2 1 1";
    cmdData << "translate rect[4] 2 1";
    BaseCommands cmdDb;
    EditorObjectParser objParser(objData);
    EditorCommandParser cmdParser(cmdData, &cmdDb);
    Editor mainEditor(objParser);
    auto cmd = cmdParser.getCommands(mainEditor.getObjects());
    mainEditor.executeCommand(cmd.value());
    EditorOutputObjectParser outParser(outData);
    outParser.writeObjects(mainEditor.getObjects());
    std::string out = outData.str();
    ASSERT_TRUE(out == "rect[4] 4 3 3 2\n");
}

TEST(commands, rotate)
{
    std::stringstream objData, cmdData, outData;
    objData << "rect[4] 2 2 1 1";
    cmdData << "rotate rect[4] 90";
    BaseCommands cmdDb;
    EditorObjectParser objParser(objData);
    EditorCommandParser cmdParser(cmdData, &cmdDb);
    Editor mainEditor(objParser);
    auto cmd = cmdParser.getCommands(mainEditor.getObjects());
    mainEditor.executeCommand(cmd.value());
    EditorOutputObjectParser outParser(outData);
    outParser.writeObjects(mainEditor.getObjects());
    std::string out = outData.str();
    ASSERT_TRUE(out == "rect[4] -2 2 -1 1\n");
}

TEST(commands, scale)
{
    std::stringstream objData, cmdData, outData;
    objData << "rect[4] 2 2 1 1";
    cmdData << "scale rect[4] 2 2";
    BaseCommands cmdDb;
    EditorObjectParser objParser(objData);
    EditorCommandParser cmdParser(cmdData, &cmdDb);
    Editor mainEditor(objParser);
    auto cmd = cmdParser.getCommands(mainEditor.getObjects());
    mainEditor.executeCommand(cmd.value());
    EditorOutputObjectParser outParser(outData);
    outParser.writeObjects(mainEditor.getObjects());
    std::string out = outData.str();
    ASSERT_TRUE(out == "rect[4] 4 4 2 2\n");
}

TEST(commands, undo)
{
    std::stringstream objData, cmdData, outData;
    objData << "rect[4] 2 2 1 1";
    cmdData << "scale rect[4] 2 2\n" << "undo\n";
    BaseCommands cmdDb;
    EditorObjectParser objParser(objData);
    EditorCommandParser cmdParser(cmdData, &cmdDb);
    Editor mainEditor(objParser);
    while(auto cmd = cmdParser.getCommands(mainEditor.getObjects()))
    {
        mainEditor.executeCommand(cmd.value());
    }
    EditorOutputObjectParser outParser(outData);
    outParser.writeObjects(mainEditor.getObjects());
    std::string out = outData.str();
    ASSERT_TRUE(out == "rect[4] 2 2 1 1\n");
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}