#include "RunGame.h"
#include <iostream>
#include <time.h>

int main()
{
    srand(time(nullptr));  // NOLINT(clang-diagnostic-shorten-64-to-32, cert-msc51-cpp)
    Menu();
    return 0;
}
