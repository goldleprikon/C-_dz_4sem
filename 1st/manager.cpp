#include "manager.h"
#include <vector>

void Manager::createUser(int userId, const std::string& userName, const std::string& description) {
    if (users.find(userId) == users.end())
    {
        users[userId] = std::make_shared<User>(userId, userName, description);
        std::cout << "User with ID: " << userId << " was created." << std::endl;
        return;
    }
    std::cout << "The user with this ID already exists." << std::endl;
}

void Manager::deleteUser(int userId) {
    if (users.find(userId) != users.end()) {
        users.erase(userId);
        std::cout << "User was deleted!" << std::endl;
        return;
    }
    std::cout << "There is no such user!" << std::endl;
}

void Manager::allUsers() {
    for (const auto& pair : users) {
        auto user = pair.second;
        getUser(user->getId());
//        std::cout << "ID: " <<user->getId() << ", Name: " << user->getName() << ", Description: " << user->getDescription() << std::endl;
    }
}

void Manager::getUser(int userId) {
    if (users.find(userId) != users.end()) {
        auto user = users[userId];
        if (user->getGroup().expired())
            std::cout << "ID: " <<user->getId() << ", Name: " << user->getName() << ", Description: " << user->getDescription() << std::endl;
        else
            std::cout << "ID: " <<user->getId() << ", Name: " << user->getName() << ", Description: " << user->getDescription() << " Group: "<< user->getGroup().lock()->getId() << std::endl;
        return;
    }
    std::cout << "There is no such user!" << std::endl;
}

void Manager::createGroup(int groupId) {
    if (groups.find(groupId) == groups.end())
    {
        groups[groupId] = std::make_shared<Group>(groupId);
        std::cout << "Group with ID: " << groupId << " was created." << std::endl;
        return;
    }
    std::cout << "The group with this ID already exists." << std::endl;
}

void Manager::deleteGroup(int groupId) {
    if (groups.find(groupId) != groups.end())
    {
        groups.erase(groupId);
        std::cout << "Group was deleted!" << std::endl;
        return;
    }
    std::cout << "There is no such group!" << std::endl;
}

void Manager::allGroups() {
    for (const auto& group : groups) {
        std::cout << "ID group: " << group.first << ", Users: ";
        for (const auto& user : group.second->getUsers())
            std::cout << user->getName() << " ";
        std::cout << std::endl;
    }
}

void Manager::getGroup(int groupId) {
    auto group = groups[groupId];
    std::cout << "ID group: " << group->getId() << ", Users: ";
    for (const auto& user : group->getUsers())
        std::cout << user->getName() << " ";
    std::cout << std::endl;
}

void Manager::addUserToGroup(int userId, int groupId) {
    if (groups.find(groupId) != groups.end() && users.find(userId) != users.end()) {
        auto group = groups[groupId];
        auto user = users[userId];
        group->addUser(user);
        users[userId]->setGroup(group);
        std::cout << "User " << userId << " Was added to the group " << groupId << "." << std::endl;
        return;
    }
    std::cout << "There is no such group or user!" << std::endl;
}
