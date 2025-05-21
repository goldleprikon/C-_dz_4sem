#ifndef MANAGER_H
#define MANAGER_H

#include "System.h"
#include <iostream>
#include <unordered_map>

class Manager {
private:
    std::unordered_map<int, std::shared_ptr<User>> users;
    std::unordered_map<int, std::shared_ptr<Group>> groups;
public:
    void createUser(int userId, const std::string& userName, const std::string& description);
    void deleteUser(int userId);
    void allUsers();
    void getUser(int userId);
    void createGroup(int groupId);
    void deleteGroup(int groupId);
    void allGroups();
    void getGroup(int groupId);
    void addUserToGroup(int userId, int groupId);
};

#endif // MANAGER_H
