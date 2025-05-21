#ifndef CHECKPOINTBUILDER_H
#define CHECKPOINTBUILDER_H

#include "checkpoint.h"

class CheckPointBuilder {
public:
    virtual void buildName(std::string name) = 0;
    virtual void buildCoordinates(double latitude, double longitude) = 0;
    virtual void buildPenaltyTime(double penaltyTime) = 0;
    virtual CheckPoint getResult() = 0;
};


#endif // CHECKPOINTBUILDER_H
