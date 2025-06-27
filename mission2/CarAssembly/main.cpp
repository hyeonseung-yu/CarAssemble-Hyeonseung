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

#include "system.h"
#include "car.cpp"
#include "engine.cpp"
#include "brake.cpp"
#include "steering.cpp"
#include "assembler.cpp"

#define CLEAR_SCREEN "\033[H\033[2J"

void runProducedCar(const Assembler& assembler, const Car& car, const Engine& engine, const Brake& brake, const Steering& steering);
void delay(int ms);
bool parseInt(const std::string& input, int& answer);
void showCarTypeQuestion(const Car& car);
void showEngineTypeQuestion(const Engine& engine);
void showBrakeTypeQuestion(const Brake& brake);
void showSteeringTypeQuestion(const Steering& steering);
void showRunTestQuestion();
bool isSystemTypeInvalid(int step, int answer, const Car& car, const Engine& engine, const Brake& brake, const Steering& steering);

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
    Car car;
    Engine engine;
    Brake brake;
    Steering steering;
    Assembler& assembler = Assembler::getInstance();

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
            std::cout << "���̹���\n";
            break;
        }

        int answer;
        if (!parseInt(input, answer)) {
            std::cout << "ERROR :: ���ڸ� �Է� ����\n";
            delay(800);
            continue;
        }

        if (step <= SteeringSystem_Q && isSystemTypeInvalid( step, answer, car, engine, brake, steering ) ) {
            delay(800);
            continue;
        }

        if (step == Run_Test && !(answer >= 0 && answer <= 2))
        {
            std::cout << "ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n";
            delay(800);
            continue;
        }

        // ó������ ���ư���
        if (answer == 0 && step == Run_Test)
        {
            step = CarType_Q;
            continue;
        }

        // �������� ���ư���
        if (answer == 0 && step >= 1)
        {
            step -= 1;
            continue;
        }

        if (step <= SteeringSystem_Q) {
            if (step == CarType_Q) {
                car.setType(answer);
                std::cout << "���� Ÿ������ " << car.getTypeName(answer) << "�� �����ϼ̽��ϴ�.\n";
            }
            else if (step == Engine_Q) {
                engine.setType(answer);
                std::cout << engine.getTypeName(answer) << " ������ �����ϼ̽��ϴ�.\n";
            }
            else if (step == BrakeSystem_Q) {
                brake.setType(answer);
                std::cout << brake.getTypeName(answer) << " ������ġ�� �����ϼ̽��ϴ�.\n";
            }
            else if (step == SteeringSystem_Q) {
                steering.setType(answer);
                std::cout << steering.getTypeName(answer) << " ������ġ�� �����ϼ̽��ϴ�.\n";
            }
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
            std::cout << "Test..." << std::endl;
            delay(1500);
            std::cout << "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : " << assembler.generateTestResultString(car, engine, brake, steering) << std::endl;
            delay(2000);
        }
    }
}

void runProducedCar(const Assembler& assembler, const Car& car, const Engine& engine, const Brake& brake, const Steering& steering)
{
    if (!assembler.isValidAssembly(car, engine, brake, steering))
    {
        std::cout << "�ڵ����� ���۵��� �ʽ��ϴ�" << std::endl;
        return;
    }

    if ( engine.isEngineBroken() )
    {
        std::cout << "������ ���峪�ֽ��ϴ�." << std::endl;
        std::cout << "�ڵ����� �������� �ʽ��ϴ�." << std::endl;
        return;
    }

    std::cout << "Car Type : " << car.getTypeName(car.getType()) << std::endl;
    std::cout << "Engine : " << engine.getTypeName(engine.getType()) << std::endl;
    std::cout << "Brake System : " << brake.getTypeName(brake.getType()) << std::endl;
    std::cout << "SteeringSystem : " << steering.getTypeName(steering.getType()) << std::endl;
    std::cout << "�ڵ����� ���۵˴ϴ�." << std::endl;
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


void showCarTypeQuestion(const Car& car) {
    std::cout << "        ______________\n";
    std::cout << "       /|            | \n";
    std::cout << "  ____/_|_____________|____\n";
    std::cout << " |                      O  |\n";
    std::cout << " '-(@)----------------(@)--'\n";
    std::cout << "===============================\n";
    std::cout << "� ���� Ÿ���� �����ұ��?\n";
    for (int type = 1; type <= car.numberOfAvailableTypes(); type++) {
        std::cout << type << ". " << car.getTypeName(type) << std::endl;
    }
}

void showEngineTypeQuestion(const Engine& engine) {

    std::cout << "� ������ ž���ұ��?\n";
    std::cout << "0. �ڷΰ���\n";
    for (int type = 1; type <= engine.numberOfAvailableTypes(); type++) {
        std::cout << type << ". " << engine.getTypeName(type) << std::endl;
    }
}

void showBrakeTypeQuestion(const Brake& brake) {
    std::cout << "� ������ġ�� �����ұ��?\n";
    std::cout << "0. �ڷΰ���\n";
    for (int type = 1; type <= brake.numberOfAvailableTypes(); type++) {
        std::cout << type << ". " << brake.getTypeName(type) << std::endl;
    }
}
void showSteeringTypeQuestion(const Steering& steering) {
    std::cout << "� ������ġ�� �����ұ��?\n";
    std::cout << "0. �ڷΰ���\n";
    for (int type = 1; type <= steering.numberOfAvailableTypes(); type++) {
        std::cout << type << ". " << steering.getTypeName(type) << std::endl;
    }
}

void showRunTestQuestion() {
    std::cout << "���� ������ �ϼ��Ǿ����ϴ�.\n";
    std::cout << "� ������ �ұ��?\n";
    std::cout << "0. ó�� ȭ������ ���ư���\n";
    std::cout << "1. RUN\n";
    std::cout << "2. Test\n";
}


bool isSystemTypeInvalid(int step, int answer, const Car& car, const Engine& engine, const Brake& brake, const Steering& steering) {

    if (step == CarType_Q && !car.isValidTypeRange(answer))
    {
        std::cout << "ERROR :: ���� Ÿ���� 1 ~ " << car.numberOfAvailableTypes() << " ������ ���� ����\n";
        return true;
    }

    if (step == Engine_Q && !(answer == 0 || engine.isValidTypeRange(answer)))
    {
        std::cout << "ERROR :: ������ 1 ~ " << engine.numberOfAvailableTypes() << " ������ ���� ����\n";
        return true;
    }

    if (step == BrakeSystem_Q && !(answer == 0 || brake.isValidTypeRange(answer)))
    {
        std::cout << "ERROR :: ������ġ�� 1 ~ " << brake.numberOfAvailableTypes() << " ������ ���� ����\n";
        return true;
    }

    if (step == SteeringSystem_Q && !(answer == 0 || steering.isValidTypeRange(answer)))
    {
        std::cout << "ERROR :: ������ġ�� 1 ~ " << steering.numberOfAvailableTypes() << " ������ ���� ����\n";
        return true;
    }

    return false;
}

#endif