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
        std::cout << "� ���� Ÿ���� �����ұ��?\n";
        std::cout << "1. Sedan\n";
        std::cout << "2. SUV\n";
        std::cout << "3. Truck\n";
    }
    else if (step == Engine_Q)
    {
        std::cout << "� ������ ž���ұ��?\n";
        std::cout << "0. �ڷΰ���\n";
        std::cout << "1. GM\n";
        std::cout << "2. TOYOTA\n";
        std::cout << "3. WIA\n";
        std::cout << "4. ���峭 ����\n";
    }
    else if (step == BrakeSystem_Q)
    {
        std::cout << "� ������ġ�� �����ұ��?\n";
        std::cout << "0. �ڷΰ���\n";
        std::cout << "1. MANDO\n";
        std::cout << "2. CONTINENTAL\n";
        std::cout << "3. BOSCH\n";
    }
    else if (step == SteeringSystem_Q)
    {
        std::cout << "� ������ġ�� �����ұ��?\n";
        std::cout << "0. �ڷΰ���\n";
        std::cout << "1. BOSCH\n";
        std::cout << "2. MOBIS\n";
    }
    else if (step == Run_Test)
    {
        std::cout << "���� ������ �ϼ��Ǿ����ϴ�.\n";
        std::cout << "� ������ �ұ��?\n";
        std::cout << "0. ó�� ȭ������ ���ư���\n";
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
            std::cout << "���̹���\n";
            break;
        }

        int answer;
        if (!parseInt(input, answer)) {
            std::cout << "ERROR :: ���ڸ� �Է� ����\n";
            delay(800);
            continue;
        }


        if (step == CarType_Q && !(answer >= 1 && answer <= 3))
        {
            std::cout << "ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n";
            delay(800);
            continue;
        }

        if (step == Engine_Q && !(answer >= 0 && answer <= 4))
        {
            std::cout << "ERROR :: ������ 1 ~ 4 ������ ���� ����\n";
            delay(800);
            continue;
        }

        if (step == BrakeSystem_Q && !(answer >= 0 && answer <= 3))
        {
            std::cout << "ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n";
            delay(800);
            continue;
        }

        if (step == SteeringSystem_Q && !(answer >= 0 && answer <= 2))
        {
            std::cout << "ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n";
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
    if (step == CarType_Q) std::cout << "���� Ÿ������ " << getCarTypeName(answer) << "�� �����ϼ̽��ϴ�.\n";
    if (step == Engine_Q) std::cout << getEngineName(answer) << " ������ �����ϼ̽��ϴ�.\n";
    if (step == BrakeSystem_Q) std::cout << getBrakeName(answer) << " ������ġ�� �����ϼ̽��ϴ�.\n";
    if (step == SteeringSystem_Q) std::cout << getSteeringName(answer) << " ������ġ�� �����ϼ̽��ϴ�.\n";
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
        std::cout << "�ڵ����� ���۵��� �ʽ��ϴ�\n";
    }
    else
    {
        if (answers[Engine_Q] == BrokenEngine)
        {
            std::cout << "������ ���峪�ֽ��ϴ�.\n";
            std::cout << "�ڵ����� �������� �ʽ��ϴ�.\n";
        }
        else
        {
            std::cout << "Car Type : " << getCarTypeName(answers[CarType_Q]) << std::endl;
            std::cout << "Engine : " << getEngineName(answers[Engine_Q]) << std::endl;
            std::cout << "Brake System : " << getBrakeName(answers[BrakeSystem_Q]) << std::endl;
            std::cout << "SteeringSystem : " << getSteeringName(answers[SteeringSystem_Q]) << std::endl;
            std::cout << "�ڵ����� ���۵˴ϴ�." << std::endl;
        }
    }
}

void testProducedCar()
{
    if (answers[CarType_Q] == SEDAN && answers[BrakeSystem_Q] == CONTINENTAL)
    {
        std::cout << "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n";
        std::cout << "Sedan���� Continental������ġ ��� �Ұ�\n";
    }
    else if (answers[CarType_Q] == SUV && answers[Engine_Q] == TOYOTA)
    {
        std::cout << "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n";
        std::cout << "SUV���� TOYOTA���� ��� �Ұ�\n";
    }
    else if (answers[CarType_Q] == TRUCK && answers[Engine_Q] == WIA)
    {
        std::cout << "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n";
        std::cout << "Truck���� WIA���� ��� �Ұ�\n";
    }
    else if (answers[CarType_Q] == TRUCK && answers[BrakeSystem_Q] == MANDO)
    {
        std::cout << "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n";
        std::cout << "Truck���� Mando������ġ ��� �Ұ�\n";
    }
    else if (answers[BrakeSystem_Q] == BOSCH_B && answers[SteeringSystem_Q] != BOSCH_S)
    {
        std::cout << "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n";
        std::cout << "Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n";
    }
    else
    {
        std::cout << "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n";
    }
}

#endif