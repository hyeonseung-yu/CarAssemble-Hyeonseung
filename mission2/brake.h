#pragma once


enum BrakeType
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};


class Brake {

public:
    Brake() {};

    bool isValidTypeRange(int answer) const {
        return answer >= MANDO && answer <= BOSCH_B;
    }

    int numberOfAvailableTypes() const {
        return 3;
    }

    std::string getTypeName(int type) const {
        if (type == MANDO) return "MANDO";
        if (type == CONTINENTAL) return "CONTINENTAL";
        if (type == BOSCH_B) return "BOSCH";
    }

    int getType() const {
        return brakeType;
    }

    void setType(int type) {
        brakeType = type;
    }

private:
    int brakeType = -1;
};