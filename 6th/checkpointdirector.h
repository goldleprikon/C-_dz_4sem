#ifndef CHECKPOINTDIRECTOR_H
#define CHECKPOINTDIRECTOR_H

#include "concretecheckpointbuilder.h"

class CheckPointDirector
{
private:
    CheckPointBuilder* builder;

public:
    CheckPointDirector(CheckPointBuilder* builder)
        :builder(builder)
    {}
    CheckPoint constructCheckPoint(std::string name,
                                   double latitude, double longitude,
                                   double penaltyTime);
};

#endif // CHECKPOINTDIRECTOR_H
