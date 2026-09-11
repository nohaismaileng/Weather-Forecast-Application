#ifndef DATA_H
#define DATA_H

#include "DataAbstract.h"

#include <cstddef>

class Data : public DataAbstract
{
public:

    Data();
    char* GetResponse() override;
    std::size_t GetSize() const override;

    void Clear() override;

    static std::size_t write_chunk(
        void* data,
        std::size_t itemSize,
        std::size_t itemCount,
        void* userdata
    );

    ~Data() override;
};

#endif