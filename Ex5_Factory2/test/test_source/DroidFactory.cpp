#include "../test_include/DroidFactory.hpp"

DroidFactory::DroidFactory(size_t ratio)    :   _ratio(ratio), _Iron(0),
                                                _Silicon(0), _Exp(0)
{}

DroidFactory::DroidFactory(const DroidFactory &obj) :   _ratio(obj._ratio),
                                                        _Iron(obj._Iron),
                                                        _Silicon(obj._Silicon),
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