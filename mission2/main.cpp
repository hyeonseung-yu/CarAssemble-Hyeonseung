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

#include "car.h"
#include "engine.h"
#include "brake.h"
#include "steering.h"
#include "assembler.h"

#define CLEAR_SCREEN "\033[H\033[2J"

int answers[10];

void runProducedCar(const Assembler& assembler, const Car& car, const Engine& engine, const Brake& brake, const Steering& steering);
void delay(int ms);
bool parseInt(const std::string& input, int& answer);

enum QuestionType
{
    CarType_Q,
    Engine_Q,
    BrakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
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

void showCarTypeQuestion(const Car& car) {
    std::cout << "        ______________\n";
    std::cout << "       /|            | \n";
    std::cout << "  ____/_|_____________|____\n";
    std::cout << " |                      O  |\n";
    std::cout << " '-(@)----------------(@)--'\n";
    std::cout << "===============================\n";
    std::cout << "어떤 차량 타입을 선택할까요?\n";
    for (int type = 1; type <= car.numberOfAvailableTypes(); type++) {
        std::cout << type << ". " << car.getTypeName(type) << std::endl;
    }
}

void showEngineTypeQuestion(const Engine& engine) {

    std::cout << "어떤 엔진을 탑재할까요?\n";
    std::cout << "0. 뒤로가기\n";
    for (int type = 1; type <= engine.numberOfAvailableTypes(); type++) {
        std::cout << type << ". " << engine.getTypeName(type) << std::endl;
    }
}

void showBrakeTypeQuestion(const Brake& brake) {
    std::cout << "어떤 제동장치를 선택할까요?\n";
    std::cout << "0. 뒤로가기\n";
    for (int type = 1; type <= brake.numberOfAvailableTypes(); type++) {
        std::cout << type << ". " << brake.getTypeName(type) << std::endl;
    }
}
void showSteeringTypeQuestion(const Steering& steering) {
    std::cout << "어떤 조향장치를 선택할까요?\n";
    std::cout << "0. 뒤로가기\n";
    for (int type = 1; type <= steering.numberOfAvailableTypes(); type++) {
        std::cout << type << ". " << steering.getTypeName(type) << std::endl;
    }
}

void showRunTestQuestion() {
    std::cout << "멋진 차량이 완성되었습니다.\n";
    std::cout << "어떤 동작을 할까요?\n";
    std::cout << "0. 처음 화면으로 돌아가기\n";
    std::cout << "1. RUN\n";
    std::cout << "2. Test\n";
}

bool parseInt(const std::string& input, int& answer) {
    std::stringstream ss(input);
    ss >> answer;
    return !ss.fail() && ss.eof();
}

int main()
{
    std::string input;
    int step = CarType_Q;
    Car car;
    Engine engine;
    Brake brake;
    Steering steering;
    Assembler assembler;

    while (1)
    {
        printf(CLEAR_SCREEN);
        if (step == CarType_Q) showCarTypeQuestion(car);
        else if (step == Engine_Q) showEngineTypeQuestion(engine);
        else if (step == BrakeSystem_Q) showBrakeTypeQuestion(brake);
        else if (step == SteeringSystem_Q) showSteeringTypeQuestion(steering);
        else if (step == Run_Test) showRunTestQuestion();
        std::cout << "===============================\n";

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

        if (step == CarType_Q && !car.isValidTypeRange(answer))
        {
            std::cout << "ERROR :: 차량 타입은 1 ~ "  << car.numberOfAvailableTypes() << " 범위만 선택 가능\n";
            delay(800);
            continue;
        }

        if (step == Engine_Q && !(answer == 0 || engine.isValidTypeRange(answer)) )
        {
            std::cout << "ERROR :: 엔진은 1 ~ " << engine.numberOfAvailableTypes() <<" 범위만 선택 가능\n";
            delay(800);
            continue;
        }

        if (step == BrakeSystem_Q && !(answer == 0 || brake.isValidTypeRange(answer)))
        {
            std::cout << "ERROR :: 제동장치는 1 ~ " << brake.numberOfAvailableTypes() << " 범위만 선택 가능\n";
            delay(800);
            continue;
        }

        if (step == SteeringSystem_Q && !(answer == 0 || steering.isValidTypeRange(answer)))
        {
            std::cout << "ERROR :: 조향장치는 1 ~ " << steering.numberOfAvailableTypes() << " 범위만 선택 가능\n";
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

        if (step == CarType_Q) {
            answers[step] = answer;
            car.setType(answer);
            std::cout << "차량 타입으로 " << car.getTypeName(answer) << "을 선택하셨습니다.\n";
            delay(1500);
            step += 1;
        }else if (step == Engine_Q){
            answers[step] = answer;
            engine.setType(answer);
            std::cout << engine.getTypeName(answer) << " 엔진을 선택하셨습니다.\n";
            delay(1500);
            step += 1;
        }
        else if (step == BrakeSystem_Q) {
            answers[step] = answer;
            brake.setType(answer);
            std::cout << brake.getTypeName(answer) << " 제동장치를 선택하셨습니다.\n";
            delay(1500);
            step += 1;
        }
        else if (step == SteeringSystem_Q) { 
            answers[step] = answer;
            steering.setType(answer);
            std::cout << steering.getTypeName(answer) << " 조향장치를 선택하셨습니다.\n";
            delay(1500);
            step += 1;
        }
        else if (step == Run_Test && answer == 1)
        {
            runProducedCar(assembler, car, engine, brake, steering);
            delay(2000);
        }
        else if (step == Run_Test && answer == 2)
        {
            std::cout << "Test...\n";
            delay(1500);
            assembler.testProducedCar(car, engine, brake, steering);
            delay(2000);
        }
    }
}

void runProducedCar(const Assembler& assembler, const Car& car, const Engine& engine, const Brake& brake, const Steering& steering)
{
    if (!assembler.isValidAssembly(car, engine, brake, steering))
    {
        std::cout << "자동차가 동작되지 않습니다\n";
    }
    else
    {
        if ( engine.isEngineBroken() )
        {
            std::cout << "엔진이 고장나있습니다.\n";
            std::cout << "자동차가 움직이지 않습니다.\n";
        }
        else
        {
            std::cout << "Car Type : " << car.getTypeName(car.getType()) << std::endl;
            std::cout << "Engine : " << engine.getTypeName(engine.getType()) << std::endl;
            std::cout << "Brake System : " << brake.getTypeName(brake.getType()) << std::endl;
            std::cout << "SteeringSystem : " << steering.getTypeName(steering.getType()) << std::endl;
            std::cout << "자동차가 동작됩니다." << std::endl;
        }
    }
}

#endif