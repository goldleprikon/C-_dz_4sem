#include <iostream>
#include <sstream>
#include "manager.h"


using namespace std;

int main () {
    Manager man;

    std::string commandLine;
    std::string command;
    std::vector<std::string> args;

    while (true) {

        std::cout << "Enter the command: ";
        std::getline(std::cin, commandLine);
        std::istringstream stream(commandLine);

        // Очистка списка аргументов
        args.clear();

        // Разбиение строки на слова
        while (stream >> command) {
            args.push_back(command);
        }

        if (args[0] == "createUser" && args.size() == 4) {
            int userId = std::stoi(args[1]);
            std::string userName = args[2];
            std::string description = args[3];
            man.createUser(userId, userName, description);
        } else if (args[0] == "deleteUser" && args.size() == 2) {
            int userId = std::stoi(args[1]);
            man.deleteUser(userId);
        } else if (args[0] == "allUsers" && args.size() == 1) {
            man.allUsers();
        } else if (args[0] == "getUser" && args.size() == 2) {
            int userId = std::stoi(args[1]);
            man.getUser(userId);
        } else if (args[0] == "createGroup" && args.size() == 2) {
            int groupId = std::stoi(args[1]);
            man.createGroup(groupId);
        } else if (args[0] == "deleteGroup" && args.size() == 2) {
            int groupId = std::stoi(args[1]);
            man.deleteGroup(groupId);
        } else if (args[0] == "allGroups" && args.size() == 1) {
            man.allGroups();
        } else if (args[0] == "getGroup" && args.size() == 2) {
            int groupId = std::stoi(args[1]);
            man.getGroup(groupId);
        } else if (args[0] == "addUserToGroup" && args.size() == 3) {
            int userId = std::stoi(args[1]);
            int groupId = std::stoi(args[2]);
            man.addUserToGroup(userId, groupId);
        }
        else if (args[0] == "exit")
        {
            break;
        } else {
            std::cout << "Unknown command or incorrect number of arguments.\n";
        }
    }
    return 0;
}
