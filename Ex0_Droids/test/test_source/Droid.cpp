#include "../test_include/Droid.hpp"

Droid::Droid(void) :    _Id(""), _Energy(50), _Attack(25), _Toughness(15),
                        _Status(new std::string("Standing by"))
{
    std::cout << "Droid '" << _Id << "' Activated" << std::endl;
}

Droid::Droid(std::string Id) :  _Id(Id), _Energy(50), _Attack(25),
                                _Toughness(15),
                                _Status(new std::string("Standing by"))
{
    std::cout << "Droid '" << _Id << "' Activated" << std::endl;
}

Droid::Droid(const Droid& obj) :    _Id(obj._Id), _Energy(obj._Energy),
                                    _Attack(obj._Attack), _Toughness(obj._Toughness),
                                   _Status(new std::string(obj._Status->data()))
{
    std::cout << "Droid '" << _Id << "' Activated, Memory Dumped" << std::endl;

}


Droid::~Droid(void)
{
    if (_Status)
    {
        delete _Status;
        _Status = nullptr;
        std::cout << "Droid '" << _Id << "' Destroyed" << std::endl;
    }
}

std::string     Droid::getId(void) const
{
    return _Id;
}

size_t          Droid::getEnergy(void) const
{
    return _Energy;
}

size_t          Droid::getAttack(void) const
{
    return _Attack;
}

size_t          Droid::getToughness(void) const
{
    return _Toughness;
}

std::string     *Droid::getStatus(void) const
{
    return _Status;
}

void            Droid::setId(std::string id)
{
    _Id = id;
}

void            Droid::setEnergy(size_t energy)
{
    _Energy = energy;
}

void            Droid::setStatus(const std::string &status)
{
    if (!_Status)
        _Status = new std::string(status);
    else
        *_Status = status;
}

Droid           &Droid::operator=(const Droid &rhs)
{
    if (this != &rhs)
    {
        _Id = rhs._Id;
        _Energy = rhs._Energy;
        if (_Status)
            delete _Status;
        _Status = new std::string(rhs._Status->data());
    }
    return *this;
}