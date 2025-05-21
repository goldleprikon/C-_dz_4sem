#ifndef CONCRETECHECKPOINTBUILDER_H
#define CONCRETECHECKPOINTBUILDER_H

#include "checkpointbuilder.h"

class OptionalCheckPointBuilder : public CheckPointBuilder {
private:
    CheckPoint checkPoint;
public:
    OptionalCheckPointBuilder();
    void buildName(std::string name) override;
    void buildCoordinates(double latitude, double longitude) override;
    void buildPenaltyTime(double penaltyTime) override;
    CheckPoint getResult() override;
};

class ObligatoryCheckPointBuilder : public CheckPointBuilder {
private:
    CheckPoint checkPoint;
public:
    ObligatoryCheckPointBuilder();
    void buildName(std::string name) override;
    void buildCoordinates(double latitude, double longitude) override;
    void buildPenaltyTime(double penaltyTime) override;
    CheckPoint getResult() override;
};

#endif // CONCRETECHECKPOINTBUILDER_H
