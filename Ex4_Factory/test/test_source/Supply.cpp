#include "../test_include/Supply.hpp"

Supply::Supply(Supply::Types type, size_t amount)   :   Type(type),
                                                        Amount(amount),
                                                        Wrecks(nullptr),
                                                        nbWreck(0)
{}

Supply::Supply(Supply::Types type, size_t amount, Droid **wreck) :   Type(type),
                                                                    Amount(amount),
                                                                    Wrecks(wreck),
                                                                    nbWreck(0)
{}

Supply::~Supply(void)
{
    if (Type == Wreck)
    {
        for (size_t i = 0; i < Amount; i++)
        {
            if (Wrecks)
                delete Wrecks[i];
        }
        delete Wrecks;
    }
}


////////////////Getters And Setters
Supply::Types       Supply::getType(void) const
{
    return Type;
}

void                Supply::setType(Types type)
{
    Type = type;
}

size_t              Supply::getAmount(void) const
{
    return Amount;
}

void                Supply::setAmount(size_t amount)
{
    Amount = amount;
}

Droid               **Supply::getPtrWreck(void) const
{
    return Wrecks;
}

Droid               *Supply::getWreck(void) const
{
    return *Wrecks;
}

Droid               *Supply::getWreck(size_t index) const
{
    return Wrecks[index];
}

void                Supply::setWreck(Droid **wreck)
{
    Wrecks = wreck;
}

size_t              Supply::getNbWreck(void) const
{
    size_t i = 0;

    if (Wrecks)
        while (Wrecks[i] != nullptr)
            i++;
    return i;
}

std::ostream        &operator<<(std::ostream &os, const Supply &obj)
{    
    std::string type;
    if (obj.getType() == 1)
        type = "Iron";
    else if (obj.getType() == 2)
        type = "Silicon";
    else
        type = "Wreck";

    os << "Supply : " << obj.getType() << ", " << type;
    if (obj.getPtrWreck())
    {
        os << std::endl;
        for (size_t i = 0; i < obj.getNbWreck(); i++)
        {
            os << *obj.getWreck(i);
            if (i != obj.getNbWreck() - 1)
                os << std::endl;
        }
    }
    return os;
}