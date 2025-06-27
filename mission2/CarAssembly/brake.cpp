#pragma once
#include "system.h"

enum BrakeType
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};


class Brake : System {

public:
    Brake() {};

    bool isValidTypeRange(int answer) const override {
        return answer >= MANDO && answer <= BOSCH_B;
    }

    int numberOfAvailableTypes() const override {
        return 3;
    }

    std::string getTypeName(int type) const override {
        if (type == MANDO) return "MANDO";
        if (type == CONTINENTAL) return "CONTINENTAL";
        if (type == BOSCH_B) return "BOSCH";
        return "INVALID TYPE";
    }

    int getType() const override {
        return brakeType;
    }

    void setType(int type) override {
        brakeType = type;
    }

private:
    int brakeType = -1;
};