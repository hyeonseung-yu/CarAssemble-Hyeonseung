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
#include <memory>
#include <vector>

#include "system.h"
#include "car.cpp"
#include "engine.cpp"
#include "brake.cpp"
#include "steering.cpp"
#include "assembler.cpp"

#define CLEAR_SCREEN "\033[H\033[2J"

void runAssembledCar(const Assembler& assembler, const Car& car, const Engine& engine, const Brake& brake, const Steering& steering);
void delay(int ms);
bool parseInt(const std::string& input, int& answer);\
void printTypeQuestion(int step, const std::vector<std::shared_ptr<System>>& systems);
void printRunTestQuestion();
void printSelectionMsg(int step, int answer, const std::vector<std::shared_ptr<System>>& systems);
bool isSystemTypeInvalid(int step, int answer, const std::vector<std::shared_ptr<System>>& systems);

enum QuestionType
{
    CarType_Q,
    Engine_Q,
    BrakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

int main()
{
    std::string input;
    int step = CarType_Q;
    std::shared_ptr<Car> car(new Car());
    std::shared_ptr<Engine> engine(new Engine());
    std::shared_ptr<Brake> brake(new Brake());
    std::shared_ptr<Steering> steering(new Steering());

    Assembler& assembler = Assembler::getInstance();

    std::vector<std::shared_ptr<System>> systems;
    systems.push_back(car);
    systems.push_back(engine);
    systems.push_back(brake);
    systems.push_back(steering);

    while (1)
    {
        printf(CLEAR_SCREEN);
        if (step <= SteeringSystem_Q) printTypeQuestion(step, systems);
        else if (step == Run_Test) printRunTestQuestion();
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

        if (step <= SteeringSystem_Q && isSystemTypeInvalid( step, answer, systems ) ) {
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

        if (step <= SteeringSystem_Q) {
            systems[step]->setType(answer);
            printSelectionMsg(step, answer, systems);
            delay(1500);
            step += 1;
        }
        else if (step == Run_Test && answer == 1)
        {
            runAssembledCar(assembler, *car, *engine, *brake, *steering);
            delay(2000);
        }
        else if (step == Run_Test && answer == 2)
        {
            std::cout << "Test..." << std::endl;
            delay(1500);
            std::cout << "자동차 부품 조합 테스트 결과 : " << assembler.generateTestResultString(*car, *engine, *brake, *steering) << std::endl;
            delay(2000);
        }
    }
}

void runAssembledCar(const Assembler& assembler, const Car& car, const Engine& engine, const Brake& brake, const Steering& steering)
{
    if (!assembler.isValidAssembly(car, engine, brake, steering))
    {
        std::cout << "자동차가 동작되지 않습니다" << std::endl;
        return;
    }

    if ( engine.isEngineBroken() )
    {
        std::cout << "엔진이 고장나있습니다." << std::endl;
        std::cout << "자동차가 움직이지 않습니다." << std::endl;
        return;
    }

    std::cout << "Car Type : " << car.getTypeName(car.getType()) << std::endl;
    std::cout << "Engine : " << engine.getTypeName(engine.getType()) << std::endl;
    std::cout << "Brake System : " << brake.getTypeName(brake.getType()) << std::endl;
    std::cout << "SteeringSystem : " << steering.getTypeName(steering.getType()) << std::endl;
    std::cout << "자동차가 동작됩니다." << std::endl;
}


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

bool parseInt(const std::string& input, int& answer) {
    std::stringstream ss(input);
    ss >> answer;
    return !ss.fail() && ss.eof();
}

void printTypeQuestion(int step, const std::vector<std::shared_ptr<System>>& systems) {
    if (step == CarType_Q)
    {
        printf("        ______________\n");
        printf("       /|            | \n");
        printf("  ____/_|_____________|____\n");
        printf(" |                      O  |\n");
        printf(" '-(@)----------------(@)--'\n");
        printf("===============================\n");
        printf("어떤 차량 타입을 선택할까요?\n");
    }
    else if (step == Engine_Q)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 엔진을 탑재할까요?\n");
        printf("0. 뒤로가기\n");
    }
    else if (step == BrakeSystem_Q)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 제동장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
    }
    else if (step == SteeringSystem_Q)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 조향장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
    }

    for (int type = 1; type <= systems[step]->numberOfAvailableTypes(); type++) {
        std::cout << type << ". " << systems[step]->getTypeName(type) << std::endl;
    }
}

void printRunTestQuestion() {
    std::cout << "멋진 차량이 완성되었습니다.\n";
    std::cout << "어떤 동작을 할까요?\n";
    std::cout << "0. 처음 화면으로 돌아가기\n";
    std::cout << "1. RUN\n";
    std::cout << "2. Test\n";
}


void printSelectionMsg(int step, int answer, const std::vector<std::shared_ptr<System>>& systems) {
    if (step == CarType_Q) {
        std::cout << "차량 타입으로 " << systems[step]->getTypeName(answer) << "을 선택하셨습니다.\n";
    }
    else if (step == Engine_Q) {
        std::cout << systems[step]->getTypeName(answer) << " 엔진을 선택하셨습니다.\n";
    }
    else if (step == BrakeSystem_Q) {
        std::cout << systems[step]->getTypeName(answer) << " 제동장치를 선택하셨습니다.\n";
    }
    else if (step == SteeringSystem_Q) {
        std::cout << systems[step]->getTypeName(answer) << " 조향장치를 선택하셨습니다.\n";
    }
}

bool isSystemTypeInvalid(int step, int answer, const std::vector<std::shared_ptr<System>>& systems) {

    if (step == CarType_Q && !systems[CarType_Q]->isValidTypeRange(answer))
    {
        std::cout << "ERROR :: 차량 타입은 1 ~ " << systems[CarType_Q]->numberOfAvailableTypes() << " 범위만 선택 가능\n";
        return true;
    }

    if (step == Engine_Q && !(answer == 0 || systems[Engine_Q]->isValidTypeRange(answer)))
    {
        std::cout << "ERROR :: 엔진은 1 ~ " << systems[Engine_Q]->numberOfAvailableTypes() << " 범위만 선택 가능\n";
        return true;
    }

    if (step == BrakeSystem_Q && !(answer == 0 || systems[BrakeSystem_Q]->isValidTypeRange(answer)))
    {
        std::cout << "ERROR :: 제동장치는 1 ~ " << systems[BrakeSystem_Q]->numberOfAvailableTypes() << " 범위만 선택 가능\n";
        return true;
    }

    if (step == SteeringSystem_Q && !(answer == 0 || systems[SteeringSystem_Q]->isValidTypeRange(answer)))
    {
        std::cout << "ERROR :: 조향장치는 1 ~ " << systems[SteeringSystem_Q]->numberOfAvailableTypes() << " 범위만 선택 가능\n";
        return true;
    }

    return false;
}

#endif