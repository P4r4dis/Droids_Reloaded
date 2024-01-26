#include "../include/Droid.hpp"
#include "../include/DroidMemory.hpp"
#include "../include/Carrier.hpp"
#include "../include/Supply.hpp"
#include "../include/DroidFactory.hpp"


int main(void)
{
    DroidFactory factory(3);
    Droid **w = new Droid*[10];
    Droid *newbie = nullptr;
    char c = '0';
    for (int i = 0; i < 3; ++i)
    {
        w[i] = new Droid(std::string("wreck: ") + (char)(c + i));
        *(w[i]->getBattleData()) += (i * 100);
    }

    Supply s1(Supply::Silicon, 42);
    Supply s2(Supply::Iron, 70);
    Supply s3(Supply::Wreck, 3, w);

    factory >> newbie;
    std::cout << newbie << std::endl;

    factory << s1 << s2;
    std::cout << factory << std::endl;

    s3 >> factory >> newbie;
    std::cout << factory << std::endl;
    ++factory >> newbie;
    std :: cout << *newbie->getBattleData() << std::endl;

    --factory >> newbie;
    std :: cout << *newbie->getBattleData() << std::endl;
    return 0;
}