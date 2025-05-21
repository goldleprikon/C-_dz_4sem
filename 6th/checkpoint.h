#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <iostream>
#include <string>

struct CheckPoint {
    std::string name;
    double latitude;
    double longitude;
    double penaltyTime;

    void displayInfo();
};

#endif // CHECKPOINT_H
