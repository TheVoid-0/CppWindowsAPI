#pragma once
#include <iostream>

class Process
{
private:
    // override o operador <<. o friend é para permitir o acesso a membros privados
    friend std::ostream& operator<<(std::ostream&, const Process&);
    unsigned long id;
    std::string name;

public:
    Process();
    Process(unsigned long id, std::string name);
    unsigned long getId();
    void setId(unsigned long id);
    std::string getName();
    void setName(std::string name);
    std::string toString();
};
