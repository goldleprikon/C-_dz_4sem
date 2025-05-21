#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <string>
#include <memory>

class User;

class Group {
private:
    std::vector<std::shared_ptr<User>> users_;
    const int id_;

public:
    Group(int groupId) : id_(groupId) {}

    void addUser(std::shared_ptr<User> user) {
        users_.push_back(user);
    }

    int getId() const { return id_; }

    std::vector<std::shared_ptr<User>> getUsers() const { return users_; }
};

class User {
private:
    std::weak_ptr<Group> group_;
    std::string name_;
    std::string description_;
    const int id_;

public:
    User(int userId, const std::string& userName, const std::string& userDescription)
        : id_(userId), name_(userName), description_(userDescription) {}

    int getId() const { return id_; }
    std::string getName() const { return name_; }
    std::string getDescription() const { return description_; }

    void setGroup(std::shared_ptr<Group> pG) { group_ = pG; }

    std::weak_ptr<Group> getGroup() const { return group_; }
};
#endif // SYSTEM_H
