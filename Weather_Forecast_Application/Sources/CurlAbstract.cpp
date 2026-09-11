#include "CurlAbstract.h"


CurlAbstract::CurlAbstract()
    : curl(nullptr),
      result(CURLE_OK),
      weatherAPI("")
{
}


CurlAbstract::~CurlAbstract()
{
}