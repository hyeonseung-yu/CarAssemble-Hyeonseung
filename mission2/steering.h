#pragma once

enum SteeringType
{
    BOSCH_S = 1,
    MOBIS
};

class Steering {

public:
    Steering() {};

    bool isValidTypeRange(int answer) const {
        return answer >= BOSCH_S && answer <= MOBIS;
    }

    int numberOfAvailableTypes() const {
        return 2;
    }

    std::string getTypeName(int type) const {
        if (type == BOSCH_S) return "BOSCH";
        if (type == MOBIS) return "MOBIS";
    }

    int getType() const {
        return steeringType;
    }

    void setType(int type) {
        steeringType = type;
    }

private:
    int steeringType = -1;
};