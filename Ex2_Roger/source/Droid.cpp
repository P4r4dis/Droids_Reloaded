#include "../include/Droid.hpp"

Droid::Droid(std::string Id) :  _Id(Id), _Energy(50), _Attack(25),
                                _Toughness(15),
                                _Status(new std::string("Standing by")),
                                BattleData(new DroidMemory())
{
    std::cout << "Droid '" << _Id << "' Activated" << std::endl;
}

Droid::Droid(const Droid& obj) :    _Id(obj._Id), _Energy(obj._Energy),
                                    _Attack(obj._Attack), _Toughness(obj._Toughness),
                                    _Status(new std::string(obj._Status->data())),
                                    BattleData(new DroidMemory())
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

DroidMemory     *Droid::getBattleData(void) const
{
    return BattleData;
}

void            Droid::setId(std::string id)
{
    _Id = id;
}

void            Droid::setEnergy(size_t energy)
{
    _Energy = energy;
}

void            Droid::setStatus(const std::string *status)
{
    delete _Status;
    _Status = new std::string(*status);
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

std::ostream    &operator<<(std::ostream &ostream, const Droid &obj)
{
    return ostream  << "Droid '" << obj.getId() << "', " 
                    << obj.getStatus()->data() << ", "
                    << obj.getEnergy();
}

Droid           &Droid::operator<<(size_t &reload)
{
    size_t      diff;
    size_t      max;
    size_t      min;

    diff = 0;
    max = 100;
    min = 0;
    if (_Energy >= min && _Energy < max)
    {
        diff = max - _Energy;
        _Energy += diff;
		reload -= diff;
    }

    if (_Energy > max)
        _Energy = max;
    return *this;
}

bool            Droid::operator==(const Droid &rhs) const
{
    return (*_Status == *rhs._Status);
}

bool            Droid::operator!=(const Droid &rhs) const
{
    return !(*this == rhs);
}