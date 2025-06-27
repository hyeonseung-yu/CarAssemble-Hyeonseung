#pragma once

#include "car.cpp"
#include "engine.cpp"
#include "brake.cpp"
#include "steering.cpp"

class Assembler {

public:
    Assembler(const Assembler&) = delete;
    Assembler& operator=(const Assembler&) = delete;

    static Assembler& getInstance()
    {
        static Assembler instance;
        return instance;
    }

	bool isValidAssembly(const Car& car, const Engine& engine, const Brake& brake, const Steering& steering) const {

        if (car.getType() == SEDAN && brake.getType() == CONTINENTAL) return false;
        if (car.getType() == SUV && engine.getType() == TOYOTA) return false;
        if (car.getType() == TRUCK && engine.getType() == WIA)  return false;
        if (car.getType() == TRUCK && brake.getType() == MANDO) return false;
        if (brake.getType() == BOSCH_B && steering.getType() != BOSCH_S) return false;

        return true;
	}

    std::string generateTestResultString(const Car& car, const Engine& engine, const Brake& brake, const Steering& steering) const
    {
        std::string result;
        if (car.getType() == SEDAN && brake.getType() == CONTINENTAL)
        {
            result = "FAIL\nSedan���� Continental������ġ ��� �Ұ�";
        }
        else if (car.getType() == SUV && engine.getType() == TOYOTA)
        {
            result = "FAIL\nSUV���� TOYOTA���� ��� �Ұ�";
        }
        else if (car.getType() == TRUCK && engine.getType() == WIA)
        {
            result = "FAIL\nTruck���� WIA���� ��� �Ұ�";
        }
        else if (car.getType() == TRUCK && brake.getType() == MANDO)
        {
            result = "FAIL\nTruck���� Mando������ġ ��� �Ұ�";
        }
        else if (brake.getType() == BOSCH_B && steering.getType() != BOSCH_S)
        {
            result = "FAIL\nBosch������ġ���� Bosch������ġ �̿� ��� �Ұ�";
        }
        else
        {
            result = "PASS";
        }

        return result;
    }

protected:
    Assembler() {}
    virtual ~Assembler() {}
};