#include "process.h"

Process::Process() {}

Process::Process(unsigned long id, std::string name)
{
    this->id = id;
    this->name = name;
}

unsigned long Process::getId()
{
    return this->id;
}

void Process::setId(unsigned long id)
{
    this->id = id;
}

std::string Process::getName()
{
    return this->name;
}

void Process::setName(std::string name)
{
    this->name = name;
}

std::ostream& operator<<(std::ostream &strm, const Process &process) {
  return strm << process.name << " (PID:" << process.id << ")\n";
}
