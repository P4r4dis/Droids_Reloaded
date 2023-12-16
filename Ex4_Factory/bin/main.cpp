#include "../include/Droid.hpp"
#include "../include/DroidMemory.hpp"
#include "../include/Carrier.hpp"
#include "../include/Supply.hpp"

int main(void)
{
    Droid **w = new Droid*[10];
    char c = '0';

    for (int i = 0; i < 3; ++i)
        w[i] = new Droid(std::string("wreck: ") + (char)(c + i));

    Supply s1(Supply::Silicon, 42);
    Supply s2(Supply::Iron, 70);
    Supply s3(Supply::Wreck, 3, w);

    std::cout << s3 << std::endl;

    size_t s = s2;
    std::cout << s << std::endl;
    std::cout << *(*(--s3)) << std::endl;
    std::cout << *(++s3)->getStatus() << std::endl;
    ++s3;
    *s3 = 0;
    std::cout << *s3 << std::endl;
    std::cout << s2 << std::endl;
    std::cout << !s3 << std::endl;
    
    return 0;
}