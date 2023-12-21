#include "../test_include/DroidFactory.hpp"

DroidFactory::DroidFactory(size_t ratio)    :   _ratio(ratio), _Iron(0),
                                                _Silicon(0), _Wreck(0),
                                                _Exp(0)
{}

DroidFactory::DroidFactory(const DroidFactory &obj) :   _ratio(obj._ratio),
                                                        _Iron(obj._Iron),
                                                        _Silicon(obj._Silicon),
                                                        _Wreck(obj._Wreck),
                                                        _Exp(obj._Exp)
{}

DroidFactory::~DroidFactory(void)
{}

DroidFactory            &DroidFactory::operator=(const DroidFactory &obj)
{
    if (this != &obj)
    {
        _ratio = obj._ratio;
        _Iron = obj._Iron;
        _Silicon = obj._Silicon;
        _Wreck = obj._Wreck;
        _Exp = obj._Exp;
    }
    return *this;
}

size_t                  DroidFactory::getRatio(void) const
{
    return _ratio;
}

void                    DroidFactory::setRatio(size_t ratio)
{
    _ratio = ratio;
}

size_t                  DroidFactory::getIron(void) const
{
    return _Iron;
}

void                    DroidFactory::setIron(size_t iron)
{
    _Iron = iron;
}

size_t                  DroidFactory::getSilicon(void) const
{
    return _Silicon;
}

void                    DroidFactory::setSilicon(size_t silicon)
{
    _Silicon = silicon;
}

size_t                  DroidFactory::getWreck(void) const
{
    return _Wreck;
}

void                    DroidFactory::setWreck(size_t wreck)
{
    _Wreck = wreck;
}

size_t                  DroidFactory::getExp(void) const
{
    return _Exp;
}

void                    DroidFactory::setExp(size_t exp)
{
    _Exp = exp;
}

Droid                   *DroidFactory::operator>>(Droid *&obj)
{
    if (_Iron >= 100 && _Silicon >= 50)
    {
        _Iron -= 80;
        _Silicon -= 50;
        _Exp = _Exp - (_Exp / _ratio); // maybe false
        obj = new Droid("");
        return obj;
    }
    else
    {
        obj = nullptr;
        return obj;
    }
}

DroidFactory            &DroidFactory::operator<<(const Supply &obj)
{
    switch (obj.getType())
    {
        case 1:
            _Iron += obj.getAmount();
            break;
        case 2:
            _Silicon += obj.getAmount();
            break;
        case 3:
            if (obj.getPtrWreck())
            {
                for (size_t i = 0; i < obj.getAmount(); i++)
                {
                    if (obj.getWreck(i))
                    {
                        _Wreck = obj.getAmount();
                        _Exp += obj.getWreck(i)->getBattleData()->getExp();
                    }
                }
            }
            break;
    }
    return *this;
}