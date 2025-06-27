#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include <iostream>
#include <string>
#include <sstream>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"

int answers[10];

void showSelectionMsg(int step, int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);
std::string getCarTypeName(int answer);
std::string getEngineName(int answer);
std::string getBrakeName(int answer);
std::string getSteeringName(int answer);
bool parseInt(const std::string& input, int& answer);

enum QuestionType
{
    CarType_Q,
    Engine_Q,
    BrakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK
};

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA,
    BrokenEngine
};

enum brakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};

enum SteeringSystem
{
    BOSCH_S = 1,
    MOBIS
};

void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

std::string getCarTypeName(int answer) {
    if (answer == SEDAN) return "Sedan";
    if (answer == SUV) return "SUV";
    if (answer == TRUCK) return "Truck";
}

std::string getEngineName(int answer) {
    if (answer == GM) return "GM";
    if (answer == TOYOTA) return "TOYOTA";
    if (answer == WIA) return "WIA";
}

std::string getBrakeName(int answer) {
    if (answer == MANDO) return "MANDO";
    if (answer == CONTINENTAL) return "CONTINENTAL";
    if (answer == BOSCH_B) return "BOSCH";
}

std::string getSteeringName(int answer) {
    if (answer == BOSCH_S) return "BOSCH";
    if (answer == MOBIS) return "MOBIS";
}


void showQuestion(int step) {

    printf(CLEAR_SCREEN);
    if (step == CarType_Q)
    {

        std::cout << "        ______________\n";
        std::cout << "       /|            | \n";
        std::cout << "  ____/_|_____________|____\n";
        std::cout << " |                      O  |\n";
        std::cout << " '-(@)----------------(@)--'\n";
        std::cout << "===============================\n";
        std::cout << "어떤 차량 타입을 선택할까요?\n";
        std::cout << "1. Sedan\n";
        std::cout << "2. SUV\n";
        std::cout << "3. Truck\n";
    }
    else if (step == Engine_Q)
    {
        std::cout << "어떤 엔진을 탑재할까요?\n";
        std::cout << "0. 뒤로가기\n";
        std::cout << "1. GM\n";
        std::cout << "2. TOYOTA\n";
        std::cout << "3. WIA\n";
        std::cout << "4. 고장난 엔진\n";
    }
    else if (step == BrakeSystem_Q)
    {
        std::cout << "어떤 제동장치를 선택할까요?\n";
        std::cout << "0. 뒤로가기\n";
        std::cout << "1. MANDO\n";
        std::cout << "2. CONTINENTAL\n";
        std::cout << "3. BOSCH\n";
    }
    else if (step == SteeringSystem_Q)
    {
        std::cout << "어떤 조향장치를 선택할까요?\n";
        std::cout << "0. 뒤로가기\n";
        std::cout << "1. BOSCH\n";
        std::cout << "2. MOBIS\n";
    }
    else if (step == Run_Test)
    {
        std::cout << "멋진 차량이 완성되었습니다.\n";
        std::cout << "어떤 동작을 할까요?\n";
        std::cout << "0. 처음 화면으로 돌아가기\n";
        std::cout << "1. RUN\n";
        std::cout << "2. Test\n";
    }
    std::cout << "===============================\n";
}

bool parseInt(const std::string& input, int& answer) {
    std::stringstream ss(input);
    ss >> answer;
    return !ss.fail() && ss.eof();
}

int main()
{
    char buf[100];
    std::string input;
    int step = CarType_Q;

    while (1)
    {
        showQuestion(step);

        std::cout << "INPUT > ";
        std::getline(std::cin, input);

        if (input == "exit") {
            std::cout << "바이바이\n";
            break;
        }

        int answer;
        if (!parseInt(input, answer)) {
            std::cout << "ERROR :: 숫자만 입력 가능\n";
            delay(800);
            continue;
        }


        if (step == CarType_Q && !(answer >= 1 && answer <= 3))
        {
            std::cout << "ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n";
            delay(800);
            continue;
        }

        if (step == Engine_Q && !(answer >= 0 && answer <= 4))
        {
            std::cout << "ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n";
            delay(800);
            continue;
        }

        if (step == BrakeSystem_Q && !(answer >= 0 && answer <= 3))
        {
            std::cout << "ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n";
            delay(800);
            continue;
        }

        if (step == SteeringSystem_Q && !(answer >= 0 && answer <= 2))
        {
            std::cout << "ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n";
            delay(800);
            continue;
        }

        if (step == Run_Test && !(answer >= 0 && answer <= 2))
        {
            std::cout << "ERROR :: Run 또는 Test 중 하나를 선택 필요\n";
            delay(800);
            continue;
        }

        // 처음으로 돌아가기
        if (answer == 0 && step == Run_Test)
        {
            step = CarType_Q;
            continue;
        }

        // 이전으로 돌아가기
        if (answer == 0 && step >= 1)
        {
            step -= 1;
            continue;
        }

        if (step >= CarType_Q && step <= SteeringSystem_Q) {
            answers[step] = answer;
            showSelectionMsg(step, answer);
            delay(1500);
            step += 1;
        }
        else if (step == Run_Test && answer == 1)
        {
            runProducedCar();
            delay(2000);
        }
        else if (step == Run_Test && answer == 2)
        {
            std::cout << "Test...\n";
            delay(1500);
            testProducedCar();
            delay(2000);
        }
    }
}

void showSelectionMsg(int step, int answer) {
    if (step == CarType_Q) std::cout << "차량 타입으로 " << getCarTypeName(answer) << "을 선택하셨습니다.\n";
    if (step == Engine_Q) std::cout << getEngineName(answer) << " 엔진을 선택하셨습니다.\n";
    if (step == BrakeSystem_Q) std::cout << getBrakeName(answer) << " 제동장치를 선택하셨습니다.\n";
    if (step == SteeringSystem_Q) std::cout << getSteeringName(answer) << " 조향장치를 선택하셨습니다.\n";
}

bool isValidAssembly()
{
    if (answers[CarType_Q] == SEDAN && answers[BrakeSystem_Q] == CONTINENTAL) return false;
    if (answers[CarType_Q] == SUV && answers[Engine_Q] == TOYOTA) return false;
    if (answers[CarType_Q] == TRUCK && answers[Engine_Q] == WIA)  return false;
    if (answers[CarType_Q] == TRUCK && answers[BrakeSystem_Q] == MANDO) return false;
    if (answers[BrakeSystem_Q] == BOSCH_B && answers[SteeringSystem_Q] != BOSCH_S) return false; 
    return true;
}

void runProducedCar()
{
    if (!isValidAssembly())
    {
        std::cout << "자동차가 동작되지 않습니다\n";
    }
    else
    {
        if (answers[Engine_Q] == BrokenEngine)
        {
            std::cout << "엔진이 고장나있습니다.\n";
            std::cout << "자동차가 움직이지 않습니다.\n";
        }
        else
        {
            std::cout << "Car Type : " << getCarTypeName(answers[CarType_Q]) << std::endl;
            std::cout << "Engine : " << getEngineName(answers[Engine_Q]) << std::endl;
            std::cout << "Brake System : " << getBrakeName(answers[BrakeSystem_Q]) << std::endl;
            std::cout << "SteeringSystem : " << getSteeringName(answers[SteeringSystem_Q]) << std::endl;
            std::cout << "자동차가 동작됩니다." << std::endl;
        }
    }
}

void testProducedCar()
{
    if (answers[CarType_Q] == SEDAN && answers[BrakeSystem_Q] == CONTINENTAL)
    {
        std::cout << "자동차 부품 조합 테스트 결과 : FAIL\n";
        std::cout << "Sedan에는 Continental제동장치 사용 불가\n";
    }
    else if (answers[CarType_Q] == SUV && answers[Engine_Q] == TOYOTA)
    {
        std::cout << "자동차 부품 조합 테스트 결과 : FAIL\n";
        std::cout << "SUV에는 TOYOTA엔진 사용 불가\n";
    }
    else if (answers[CarType_Q] == TRUCK && answers[Engine_Q] == WIA)
    {
        std::cout << "자동차 부품 조합 테스트 결과 : FAIL\n";
        std::cout << "Truck에는 WIA엔진 사용 불가\n";
    }
    else if (answers[CarType_Q] == TRUCK && answers[BrakeSystem_Q] == MANDO)
    {
        std::cout << "자동차 부품 조합 테스트 결과 : FAIL\n";
        std::cout << "Truck에는 Mando제동장치 사용 불가\n";
    }
    else if (answers[BrakeSystem_Q] == BOSCH_B && answers[SteeringSystem_Q] != BOSCH_S)
    {
        std::cout << "자동차 부품 조합 테스트 결과 : FAIL\n";
        std::cout << "Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n";
    }
    else
    {
        std::cout << "자동차 부품 조합 테스트 결과 : PASS\n";
    }
}

#endif