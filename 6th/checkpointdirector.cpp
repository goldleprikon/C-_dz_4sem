#include "checkpointdirector.h"

CheckPoint CheckPointDirector::constructCheckPoint(std::string name,
                                                   double latitude, double longitude,
                                                   double penaltyTime) {
    builder->buildName(name);
    builder->buildCoordinates(latitude, longitude);
    builder->buildPenaltyTime(penaltyTime);
    return builder->getResult();
}
