#ifndef DATAABSTRACT_H
#define DATAABSTRACT_H

#include <cstddef>

class DataAbstract
{
protected:

    char* Response;
    std::size_t size;

public:

    DataAbstract();
    virtual char* GetResponse() = 0;
    virtual std::size_t GetSize() const = 0;
    virtual void Clear() = 0;
    virtual ~DataAbstract();
};

#endif