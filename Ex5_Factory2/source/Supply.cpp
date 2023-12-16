#include "../include/Supply.hpp"

Supply::Supply(Supply::Types type, size_t amount)   :   Type(type),
                                                        Amount(amount),
                                                        Wrecks(nullptr),
                                                        nbWreck(0)
{}

Supply::Supply(Supply::Types type, size_t amount, Droid **wreck) :  Type(type),
                                                                    Amount(amount),
                                                                    Wrecks(wreck),
                                                                    nbWreck(0) // amount
{}

Supply::~Supply(void)
{
     if (Type == Wreck)
    {
        for (size_t i = 0; i < Amount; i++)
        {
            if (Wrecks && Wrecks[i])  // Check if Wrecks[i] is not nullptr
            {
                delete Wrecks[i];
                Wrecks[i] = nullptr;  // Set the pointer to nullptr after deletion
            }
        }
        delete [] Wrecks;  // Use delete[] for an array of pointers
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
    if (Wrecks)
        return Wrecks;
    else
        return nullptr;
}

Droid               *Supply::getWreck(void) const
{
    if (Wrecks)
        return *Wrecks;
    else
        return nullptr;
}

Droid               *Supply::getWreck(size_t index) const
{
    if (Wrecks && Wrecks[index] != nullptr)
        return Wrecks[index];
    else
        return nullptr;
}

void                Supply::setWreck(Droid **wreck)
{
    Wrecks = wreck;
}

size_t              Supply::getNbWreck(void) const
{
    return nbWreck;
}

void                Supply::setNbWreck(size_t nb)
{
    nbWreck = nb;
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

    os << "Supply : " << obj.getAmount() << ", " << type;
    if (obj.getPtrWreck())
    {
        os << std::endl;
        for (size_t i = 0; i < obj.getAmount(); i++)
        {
            os << *obj.getWreck(i);
            if (i < obj.getAmount() - 1)
                os << std::endl;
        }
    }
    return os;
}

Supply::operator size_t(void) const
{
    return Amount;
}

Droid               *&Supply::operator*(void) const
{
    if (nbWreck <= 2)
        return Wrecks[nbWreck];
    else
        return Wrecks[nbWreck - 1];
}

Droid               *Supply::operator->(void) const
{
    return this->operator*();
}

Supply              &Supply::operator++(void)
{
    if (Wrecks)
    {
        if (nbWreck >= Amount)
            nbWreck = 0;
        else
            nbWreck++;
    }
    return *this;
}

Supply                  &Supply::operator--(void)
{
    if (Wrecks)
    {
        if (nbWreck <= 0)
            nbWreck = Amount;
        else
            nbWreck--;
    }
    return *this;
}

Supply                  &Supply::operator!(void)
{
    if (Type == Wreck)
    {
        for (size_t i = 0; i < Amount; i++)
        {
            delete Wrecks[i];
            Wrecks[i] = nullptr;
        }
    }
    delete [] Wrecks;
    Wrecks = nullptr;
    Amount = 0;

    return *this;
}

bool                    Supply::operator==(const Types rhs)
{
    return Type == rhs;
}

bool                    Supply::operator!=(const Types rhs)
{
    return !(this->operator==(rhs));
}