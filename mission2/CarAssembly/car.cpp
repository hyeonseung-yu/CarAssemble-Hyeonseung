#pragma once
#include "system.h"

enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK
};

class Car : System {

public:
    Car() {};

    bool isValidTypeRange(int answer) const override {
        return answer >= SEDAN && answer <= TRUCK;
    }

    int numberOfAvailableTypes() const override {
        return 3;
    }

    std::string getTypeName(int type) const override {
        if (type == SEDAN) return "Sedan";
        if (type == SUV) return "SUV";
        if (type == TRUCK) return "Truck";
        return "INVALID TYPE";
    }

    int getType() const override {
        return carType;
    }

    void setType(int type) override {
        carType = type;
    }

private:
    int carType = -1;
};