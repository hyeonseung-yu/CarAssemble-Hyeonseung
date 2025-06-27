#pragma once

enum EngineType
{
    GM = 1,
    TOYOTA,
    WIA,
    BrokenEngine
};

class Engine {

public:
    Engine() {};

    bool isValidTypeRange(int answer) const {
        return answer >= GM && answer <= BrokenEngine;
    }

    bool isEngineBroken() const {
        return engineType == BrokenEngine;
    }

    int numberOfAvailableTypes() const{
        return 4;
    }

    std::string getTypeName(int type) const {
        if (type == GM) return "GM";
        if (type == TOYOTA) return "TOYOTA";
        if (type == WIA) return "WIA";
        if (type == BrokenEngine) return "고장난 엔진";
    }


    int getType() const {
        return engineType;
    }

    void setType(int type) {
        engineType = type;
    }

private:
    int engineType = -1;
};