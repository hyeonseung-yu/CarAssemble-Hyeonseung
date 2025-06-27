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
            std::cout << "���̹���\n";
            break;
        }

        int answer;
        if (!parseInt(input, answer)) {
            std::cout << "ERROR :: ���ڸ� �Է� ����\n";
            delay(800);
            continue;
        }

        if (step <= SteeringSystem_Q && isSystemTypeInvalid( step, answer, systems ) ) {
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
            std::cout << "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : " << assembler.generateTestResultString(*car, *engine, *brake, *steering) << std::endl;
            delay(2000);
        }
    }
}

void runAssembledCar(const Assembler& assembler, const Car& car, const Engine& engine, const Brake& brake, const Steering& steering)
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

void printTypeQuestion(int step, const std::vector<std::shared_ptr<System>>& systems) {
    if (step == CarType_Q)
    {
        printf("        ______________\n");
        printf("       /|            | \n");
        printf("  ____/_|_____________|____\n");
        printf(" |                      O  |\n");
        printf(" '-(@)----------------(@)--'\n");
        printf("===============================\n");
        printf("� ���� Ÿ���� �����ұ��?\n");
    }
    else if (step == Engine_Q)
    {
        printf(CLEAR_SCREEN);
        printf("� ������ ž���ұ��?\n");
        printf("0. �ڷΰ���\n");
    }
    else if (step == BrakeSystem_Q)
    {
        printf(CLEAR_SCREEN);
        printf("� ������ġ�� �����ұ��?\n");
        printf("0. �ڷΰ���\n");
    }
    else if (step == SteeringSystem_Q)
    {
        printf(CLEAR_SCREEN);
        printf("� ������ġ�� �����ұ��?\n");
        printf("0. �ڷΰ���\n");
    }

    for (int type = 1; type <= systems[step]->numberOfAvailableTypes(); type++) {
        std::cout << type << ". " << systems[step]->getTypeName(type) << std::endl;
    }
}

void printRunTestQuestion() {
    std::cout << "���� ������ �ϼ��Ǿ����ϴ�.\n";
    std::cout << "� ������ �ұ��?\n";
    std::cout << "0. ó�� ȭ������ ���ư���\n";
    std::cout << "1. RUN\n";
    std::cout << "2. Test\n";
}


void printSelectionMsg(int step, int answer, const std::vector<std::shared_ptr<System>>& systems) {
    if (step == CarType_Q) {
        std::cout << "���� Ÿ������ " << systems[step]->getTypeName(answer) << "�� �����ϼ̽��ϴ�.\n";
    }
    else if (step == Engine_Q) {
        std::cout << systems[step]->getTypeName(answer) << " ������ �����ϼ̽��ϴ�.\n";
    }
    else if (step == BrakeSystem_Q) {
        std::cout << systems[step]->getTypeName(answer) << " ������ġ�� �����ϼ̽��ϴ�.\n";
    }
    else if (step == SteeringSystem_Q) {
        std::cout << systems[step]->getTypeName(answer) << " ������ġ�� �����ϼ̽��ϴ�.\n";
    }
}

bool isSystemTypeInvalid(int step, int answer, const std::vector<std::shared_ptr<System>>& systems) {

    if (step == CarType_Q && !systems[CarType_Q]->isValidTypeRange(answer))
    {
        std::cout << "ERROR :: ���� Ÿ���� 1 ~ " << systems[CarType_Q]->numberOfAvailableTypes() << " ������ ���� ����\n";
        return true;
    }

    if (step == Engine_Q && !(answer == 0 || systems[Engine_Q]->isValidTypeRange(answer)))
    {
        std::cout << "ERROR :: ������ 1 ~ " << systems[Engine_Q]->numberOfAvailableTypes() << " ������ ���� ����\n";
        return true;
    }

    if (step == BrakeSystem_Q && !(answer == 0 || systems[BrakeSystem_Q]->isValidTypeRange(answer)))
    {
        std::cout << "ERROR :: ������ġ�� 1 ~ " << systems[BrakeSystem_Q]->numberOfAvailableTypes() << " ������ ���� ����\n";
        return true;
    }

    if (step == SteeringSystem_Q && !(answer == 0 || systems[SteeringSystem_Q]->isValidTypeRange(answer)))
    {
        std::cout << "ERROR :: ������ġ�� 1 ~ " << systems[SteeringSystem_Q]->numberOfAvailableTypes() << " ������ ���� ����\n";
        return true;
    }

    return false;
}

#endif