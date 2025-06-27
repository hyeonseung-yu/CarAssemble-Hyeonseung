#pragma once

#include "car.h"
#include "engine.h"
#include "brake.h"
#include "steering.h"

class Assembler {
    
public:
    Assembler() {}


	bool isValidAssembly(const Car& car, const Engine& engine, const Brake& brake, const Steering& steering) const {

        if (car.getType() == SEDAN && brake.getType() == CONTINENTAL) return false;
        if (car.getType() == SUV && engine.getType() == TOYOTA) return false;
        if (car.getType() == TRUCK && engine.getType() == WIA)  return false;
        if (car.getType() == TRUCK && brake.getType() == MANDO) return false;
        if (brake.getType() == BOSCH_B && steering.getType() != BOSCH_S) return false;

        return true;
	}

    void testProducedCar(const Car& car, const Engine& engine, const Brake& brake, const Steering& steering) const
    {
        if (car.getType() == SEDAN && brake.getType() == CONTINENTAL)
        {
            std::cout << "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n";
            std::cout << "Sedan���� Continental������ġ ��� �Ұ�\n";
        }
        else if (car.getType() == SUV && engine.getType() == TOYOTA)
        {
            std::cout << "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n";
            std::cout << "SUV���� TOYOTA���� ��� �Ұ�\n";
        }
        else if (car.getType() == TRUCK && engine.getType() == WIA)
        {
            std::cout << "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n";
            std::cout << "Truck���� WIA���� ��� �Ұ�\n";
        }
        else if (car.getType() == TRUCK && brake.getType() == MANDO)
        {
            std::cout << "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n";
            std::cout << "Truck���� Mando������ġ ��� �Ұ�\n";
        }
        else if (brake.getType() == BOSCH_B && steering.getType() != BOSCH_S)
        {
            std::cout << "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n";
            std::cout << "Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n";
        }
        else
        {
            std::cout << "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n";
        }
    }
};