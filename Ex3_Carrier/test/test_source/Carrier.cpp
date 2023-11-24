#include "../test_include/Carrier.hpp"

Carrier::Carrier(std::string id) :  Id(id), Energy(300), Attack(100),
                                    Toughness(90), Speed(0)
{
    for (int i = 0; i < 5; i++)
    {
        droid[i] = nullptr;
        if (droid[i] == nullptr)
            Speed = 0;
    }
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

Droid               *Carrier::getDroid(size_t posDroid)
{
    return droid[posDroid];
}

void                Carrier::setDroid(size_t posDroid, Droid *&newDroid)
{
    if (posDroid < 5)
    {
    // Remove the existing Droid at the position
        if (droid[posDroid])
        {
            delete droid[posDroid];
            droid[posDroid] = nullptr;
        }

    // Set the new Droid at the position
        droid[posDroid] = new Droid(*newDroid);

    // Update Speed based on the number of Droids on board
        Speed = 100 - ((posDroid + 1) * 10);
    }
}