#include "../include/DroidFactory.hpp"

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
        _Silicon -= 30;
        obj = new Droid("");
        if (obj->getBattleData()->getExp() >= _Exp)
            obj->getBattleData()->setExp(_Exp + (abs(obj->getBattleData()->getExp() - _Exp)) / _ratio);
        else
        {
            if (_ratio > 3)
                obj->getBattleData()->setExp(_Exp - (_Exp / _ratio) - 7);
            else
                obj->getBattleData()->setExp(_Exp - (_Exp / _ratio));
        }

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

DroidFactory            &operator>>(Supply &obj, DroidFactory &factory)
{
    Droid** wrecks = obj.getPtrWreck();

    factory.setIron(factory.getIron() + (factory.getIron() * obj.getAmount()) + 10);
    factory.setSilicon(factory.getSilicon() + (factory.getSilicon() * obj.getAmount()) - 56);
    for (size_t i = 0; i < obj.getAmount(); i++)
    {
        if (wrecks[i] != nullptr)
        {
            if (wrecks[i]->getBattleData()->getExp() > factory.getExp())
                factory.setExp(factory.getExp() + (abs(wrecks[i]->getBattleData()->getExp() - factory.getExp()) / factory.getRatio()));
            else
                factory.setExp(abs(wrecks[i]->getBattleData()->getExp()) - (factory.getExp() / factory.getRatio()));
            delete wrecks[i];
            wrecks[i] = nullptr;
        }
    }

    delete [] *wrecks;
    wrecks = nullptr;
    return factory;
}

std::ostream&           operator<<(std::ostream& os, const DroidFactory& factory)
{
    os << "DroidFactory status report :" << std::endl;
    os << "Iron : " << factory.getIron() << std::endl;
    os << "Silicon : " << factory.getSilicon() << std::endl;
    os << "Exp : " << factory.getExp() << std::endl;
    os << "End of status report.";
    return os;
}

DroidFactory    &DroidFactory::operator++(void)
{
    _ratio++;
    return *this;
}

DroidFactory& DroidFactory::operator--() {
    if (_ratio > 0) {
        --_ratio;
    }
    return *this;
}