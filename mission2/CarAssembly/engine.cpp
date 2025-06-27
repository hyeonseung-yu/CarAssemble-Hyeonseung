#pragma once
#include "system.h"

enum EngineType
{
    GM = 1,
    TOYOTA,
    WIA,
    BrokenEngine
};

class Engine : System {

public:
    Engine() {};

    bool isValidTypeRange(int answer) const override {
        return answer >= GM && answer <= BrokenEngine;
    }
    int numberOfAvailableTypes() const override {
        return 4;
    }

    std::string getTypeName(int type) const override {
        if (type == GM) return "GM";
        if (type == TOYOTA) return "TOYOTA";
        if (type == WIA) return "WIA";
        if (type == BrokenEngine) return "고장난 엔진";
        return "INVALID TYPE";
    }

    int getType() const override {
        return engineType;
    }

    void setType(int type) override {
        engineType = type;
    }

    bool isEngineBroken() const {
        return engineType == BrokenEngine;
    }


private:
    int engineType = -1;
};