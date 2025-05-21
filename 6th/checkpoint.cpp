#include "checkpoint.h"

void CheckPoint::displayInfo() {
    std::cout << "Name: " << name << std::endl;
    std::cout << "coordinates: (" << latitude << ", " << longitude << ")" << std::endl;
    if (penaltyTime > 0) {
        std::cout<< "Penalty time: " << penaltyTime << " h" << std::endl;
    }
    else {
        std::cout << "Failed SU" << std::endl;
    }
}
