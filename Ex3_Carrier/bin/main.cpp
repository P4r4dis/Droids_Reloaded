#include "../include/Droid.hpp"
#include "../include/DroidMemory.hpp"

class Carrier
{
public:
    Carrier(std::string id = "");

    std::string getId(void) const;
    void setId(std::string id);

    size_t getEnergy(void) const;
    void setEnergy(size_t energy);

    size_t getAttack(void) const;
    size_t getToughness(void) const;

    size_t getSpeed(void) const;
    void setSpeed(size_t speed);

    Droid *getDroid(size_t posDroid);
    void setDroid(size_t posDroid, Droid *newDroid);

private:
    std::string Id;
    size_t Energy;
    const size_t Attack;
    const size_t Toughness;
    size_t Speed;
    Droid *droid[5];
    size_t nbDroid;
};
Carrier::Carrier(std::string id) : Id(id), Energy(300), Attack(100),
                                   Toughness(90), Speed(0), nbDroid(0)
{
    for (int i = 0; i < 5; i++)
        droid[i] = nullptr;
}

// GETTERS AND SETTERS
std::string Carrier::getId(void) const
{
    return Id;
}

void Carrier::setId(std::string id)
{
    Id = id;
}

size_t Carrier::getEnergy(void) const
{
    return Energy;
}

void Carrier::setEnergy(size_t energy)
{
    Energy = energy;
}

size_t Carrier::getAttack(void) const
{
    return Attack;
}

size_t Carrier::getToughness(void) const
{
    return Toughness;
}

size_t Carrier::getSpeed(void) const
{
    return Speed;
}

void Carrier::setSpeed(size_t speed)
{
    Speed = speed;
}

Droid *Carrier::getDroid(size_t posDroid)
{
    return droid[posDroid];
}

void Carrier::setDroid(size_t posDroid, Droid *newDroid)
{
    if (posDroid < 5)
    {
        // Delete the existing Droid at the position
        delete droid[posDroid];
        droid[posDroid] = nullptr;

        // Set the new Droid at the position
        droid[posDroid] = newDroid;

        // Update the number of Droids
        nbDroid = 0;
        for (size_t i = 0; i < 5; i++)
        {
            if (droid[i] != nullptr)
            {
                nbDroid++;
            }
        }

        // Update Speed based on the number of Droids on board
        Speed = 100 - (nbDroid * 10);
    }
}

int main(void)
{
    Carrier c("HellExpress");

    try
    {
        Droid *d1 = new Droid("Commander");
        Droid *d2 = new Droid("Sergent");
        Droid *d3 = new Droid("Troufiont");
        Droid *d4 = new Droid("Groupie");
        Droid *d5 = new Droid("BeerHolder");

        for (size_t i = 0; i < 5; i++)
        {
            switch (i)
            {
            case 0:
                c.setDroid(i, d1);
                break;
            case 1:
                c.setDroid(i, d2);
                break;
            case 2:
                c.setDroid(i, d3);
                break;
            case 3:
                c.setDroid(i, d4);
                break;
            case 4:
                c.setDroid(i, d5);
                break;
            }
        }
        c.setDroid(0, d1);
        std::cout << c.getSpeed() << std::endl;
        std::cout << c.getDroid(0)->getId() << std::endl;
        delete d1;
        delete d2;
        delete d3;
        delete d4;
        delete d5;
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Allocation failed: " << e.what() << std::endl;
    }
    return 0;
}