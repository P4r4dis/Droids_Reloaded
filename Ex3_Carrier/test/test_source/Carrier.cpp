#include "../test_include/Carrier.hpp"

Carrier::Carrier(std::string id) :  Id(id), Energy(300), Attack(100),
                                    Toughness(90), Speed(0), droid(new Droid*[5]), nbDroid(0)
                                    
{
    for (int i = 0; i < 5; i++)
        droid[i] = nullptr;
}

Carrier::~Carrier(void)
{
    for (size_t i = 0; i < 5; i++)
        delete droid[i];
}

// GETTERS AND SETTERS
std::string         Carrier::getId(void) const
{
    return Id;
}

void                Carrier::setId(std::string id)
{
    Id = id;
}

size_t              Carrier::getEnergy(void) const
{
    return Energy;
}

void                Carrier::setEnergy(size_t energy)
{
    Energy = energy;
}

size_t              Carrier::getAttack(void) const
{
    return Attack;
}

size_t              Carrier::getToughness(void) const
{
    return Toughness;
}

size_t              Carrier::getSpeed(void) const
{
    return Speed;
}

void                Carrier::setSpeed(size_t speed)
{
    Speed = speed;
}

size_t              Carrier::getNbDroid(void) const
{
    return nbDroid;
}

Droid               *Carrier::getDroid(size_t posDroid) const
{
    return droid[posDroid];
}

void                Carrier::setDroid(size_t posDroid, Droid *newDroid)
{
    if (posDroid < 5)
    {
        // Check if the new Droid is the same as the existing one
        if (droid[posDroid] != newDroid)
        {
            // Remove the existing Droid at the position
            delete droid[posDroid];
            droid[posDroid] = nullptr;

            // Set the new Droid at the position without using copy constructor or assignment operator
            droid[posDroid] = newDroid;

            // Recalculate the number of Droids
            nbDroid = 0;
            for (size_t i = 0; i < 5; i++)
            {
                if (droid[i] != nullptr)
                    nbDroid++;
            }
        }
        // Update Speed based on the number of Droids on board
        Speed = 100 - (nbDroid * 10);
    }
}


Carrier             &Carrier::operator<<(Droid *&rhs)
{
    if (nbDroid < 5 && droid[nbDroid] == nullptr)
    {
        droid[nbDroid] = rhs;
        nbDroid++;
        Speed = 100 - (nbDroid * 10);
        rhs = nullptr;
        return *this;
    }
    return *this;
}

Carrier             &Carrier::operator>>(Droid *&rhs)
{   
    for (size_t i = 0; i < nbDroid; i++)
    {
        if (droid[i])
        {
            rhs = droid[i];
            droid[i] = nullptr;
            nbDroid--;
            Speed = 100 - (nbDroid * 10);
            return *this;
        }
    }
    return *this;
}

Droid               *&Carrier::operator[](size_t index)
{
    return droid[index];
}

Carrier             &Carrier::operator~(void)
{
    nbDroid = 0;
    for (size_t i = 0; i < 5; i++)
    {
        if (droid[i])
            nbDroid++;
        Speed = 100 - (nbDroid * 10);
    }
    return *this;
}

bool                Carrier::operator()(int x, int y)
{
    size_t energyCost = (std::abs(x) + std::abs(y)) * (10 + nbDroid);
    
    if (Speed > 0 && Energy > energyCost)
    {
        Energy -= energyCost;
        return true;
    }
    else
        return false;
}