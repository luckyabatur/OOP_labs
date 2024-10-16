#include "Eleven.h"


int main(void)
{
    Eleven p{"12345A9A"};
    Eleven b{"AA1312409"};
    Eleven t = p.add(b);
    t.print(std::cout);




    return 0;
}
