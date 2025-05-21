#include "concretecheckpointbuilder.h"


OptionalCheckPointBuilder::OptionalCheckPointBuilder() {}

void OptionalCheckPointBuilder::buildName(std::string name) {
    checkPoint.name = name;
}

void OptionalCheckPointBuilder::buildCoordinates(double latitude, double longitude) {
    if (latitude < -90.0 || latitude > 90.0 || longitude < -180.0 || longitude > 180.0) {
        throw std::invalid_argument("Invalid latitude and longitude values");
    }
    checkPoint.latitude = latitude;
    checkPoint.longitude = longitude;
}

void OptionalCheckPointBuilder::buildPenaltyTime(double penaltyTime) {
    checkPoint.penaltyTime = penaltyTime;
}

CheckPoint OptionalCheckPointBuilder::getResult() {
    return checkPoint;
}

ObligatoryCheckPointBuilder::ObligatoryCheckPointBuilder() {}

void ObligatoryCheckPointBuilder::buildName(std::string name) {
    checkPoint.name = name;
}

void ObligatoryCheckPointBuilder::buildCoordinates(double latitude, double longitude) {
    if (latitude < -90.0 || latitude > 90.0 || longitude < -180.0 || longitude > 180.0) {
        throw std::invalid_argument("Invalid latitude and longitude values");
    }
    checkPoint.latitude = latitude;
    checkPoint.longitude = longitude;
}

void ObligatoryCheckPointBuilder::buildPenaltyTime(double penaltyTime) {
    checkPoint.penaltyTime = 0;
}

CheckPoint ObligatoryCheckPointBuilder::getResult() {
    return checkPoint;
}
