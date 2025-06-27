#pragma once
#include "system.h"

enum SteeringType
{
    BOSCH_S = 1,
    MOBIS
};

class Steering : public System {

public:
    Steering() {};

    bool isValidTypeRange(int answer) const override{
        return answer >= BOSCH_S && answer <= MOBIS;
    }

    int numberOfAvailableTypes() const override {
        return 2;
    }

    std::string getTypeName(int type) const override {
        if (type == BOSCH_S) return "BOSCH";
        if (type == MOBIS) return "MOBIS";
        return "INVALID TYPE";
    }

    int getType() const override {
        return steeringType;
    }

    void setType(int type) override {
        steeringType = type;
    }

private:
    int steeringType = -1;
};