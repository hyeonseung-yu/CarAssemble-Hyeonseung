#pragma once

#define interface struct

interface System {

public:
    virtual bool isValidTypeRange(int answer) const = 0;
    virtual int numberOfAvailableTypes() const = 0;
    virtual std::string getTypeName(int type) const = 0;
    virtual int getType() const = 0;
    virtual void setType(int type) = 0;
};