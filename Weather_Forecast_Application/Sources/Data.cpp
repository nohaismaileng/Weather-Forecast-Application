#include "Data.h"

#include <cstdlib>
#include <cstring>


Data::Data()
{
    Response = nullptr;
    size = 0;
}


char* Data::GetResponse()
{
    return Response;
}


std::size_t Data::GetSize() const
{
    return size;
}


void Data::Clear()
{
    if (Response != nullptr)
    {
        std::free(Response);
        Response = nullptr;
    }

    size = 0;
}


std::size_t Data::write_chunk(
    void* data,
    std::size_t itemSize,
    std::size_t itemCount,
    void* userdata
)
{
    if (data == nullptr || userdata == nullptr)
    {
        return 0;
    }

    Data* receiver = static_cast<Data*>(userdata);
    std::size_t bytes = itemSize * itemCount;

    char* newBuffer = static_cast<char*>(
        std::realloc(
            receiver->Response,
            receiver->size + bytes + 1
        )
    );

    if (newBuffer == nullptr)
    {
        return 0;
    }

    receiver->Response = newBuffer;

    std::memcpy(
        receiver->Response + receiver->size,
        data,
        bytes
    );

    receiver->size += bytes;
    receiver->Response[receiver->size] = '\0';

    return bytes;
}


Data::~Data()
{
    Clear();
}