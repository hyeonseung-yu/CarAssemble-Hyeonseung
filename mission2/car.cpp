#pragma once

enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK
};

class Car {

public:
    Car() {};

    bool isValidTypeRange(int answer) const {
        return answer >= SEDAN && answer <= TRUCK;
    }

    int numberOfAvailableTypes() const {
        return 3;
    }

    std::string getTypeName(int type) const {
        if (type == SEDAN) return "Sedan";
        if (type == SUV) return "SUV";
        if (type == TRUCK) return "Truck";
    }

    int getType() const  {
        return carType;
    }

    void setType(int type) {
        carType = type;
    }

private:
    int carType = -1;
};