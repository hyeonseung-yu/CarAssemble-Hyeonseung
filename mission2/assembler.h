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
            std::cout << "자동차 부품 조합 테스트 결과 : FAIL\n";
            std::cout << "Sedan에는 Continental제동장치 사용 불가\n";
        }
        else if (car.getType() == SUV && engine.getType() == TOYOTA)
        {
            std::cout << "자동차 부품 조합 테스트 결과 : FAIL\n";
            std::cout << "SUV에는 TOYOTA엔진 사용 불가\n";
        }
        else if (car.getType() == TRUCK && engine.getType() == WIA)
        {
            std::cout << "자동차 부품 조합 테스트 결과 : FAIL\n";
            std::cout << "Truck에는 WIA엔진 사용 불가\n";
        }
        else if (car.getType() == TRUCK && brake.getType() == MANDO)
        {
            std::cout << "자동차 부품 조합 테스트 결과 : FAIL\n";
            std::cout << "Truck에는 Mando제동장치 사용 불가\n";
        }
        else if (brake.getType() == BOSCH_B && steering.getType() != BOSCH_S)
        {
            std::cout << "자동차 부품 조합 테스트 결과 : FAIL\n";
            std::cout << "Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n";
        }
        else
        {
            std::cout << "자동차 부품 조합 테스트 결과 : PASS\n";
        }
    }
};