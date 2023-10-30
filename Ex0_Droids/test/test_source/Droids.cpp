#include "../test_include/Droids.hpp"

Droids::Droids(void) :  _Id(""), _Energy(50), _Attack(25), _Toughness(15),
                        _Status(new std::string("Standing by"))
{
    std::cout << "Droid '" << _Id << "' Activated" << std::endl;
}

Droids::Droids(std::string Id) :    _Id(Id), _Energy(50), _Attack(25),
                                    _Toughness(15),
                                    _Status(new std::string("Standing by"))
{
    std::cout << "Droid '" << _Id << "' Activated" << std::endl;
}

Droids::Droids(const Droids& obj) : _Id(obj._Id), _Energy(obj._Energy),
                                    _Attack(obj._Attack), _Toughness(obj._Toughness),
                                    _Status(obj._Status)
{
    std::cout << "Droid '" << _Id << "' Activated, Memory Dumped" << std::endl;
}

std::string     Droids::getId(void) const
{
    return _Id;
}

size_t          Droids::getEnergy(void) const
{
    return _Energy;
}

size_t          Droids::getAttack(void) const
{
    return _Attack;
}

size_t          Droids::getToughness(void) const
{
    return _Toughness;
}

std::string     *Droids::getStatus(void) const
{
    return _Status;
}