#ifndef                 __CARRIER_HPP__
    #define             __CARRIER_HPP__

#include "Droid.hpp"

class                   Carrier
{
    public:
        Carrier(std::string id = "");
        ~Carrier(void);

        std::string     getId(void) const;
        void            setId(std::string id);

        size_t          getEnergy(void) const;
        void            setEnergy(size_t energy);

        size_t          getAttack(void) const;
        size_t          getToughness(void) const;

        size_t          getSpeed(void) const;
        void            setSpeed(size_t speed);

        Droid           *getDroid(size_t posDroid) const;
        void            setDroid(size_t posDroid, Droid *newDroid);

        size_t          getNbDroid(void) const;

        Carrier         &operator<<(Droid *&rhs);
        Carrier         &operator>>(Droid *&rhs);
        Droid           *&operator[](size_t index);
        Carrier         &operator~(void);
        bool            operator()(int x, int y);

    private:
        std::string     Id;
        size_t          Energy;
        const size_t    Attack;
        const size_t    Toughness;
        size_t          Speed;
        Droid           **droid;
        size_t          nbDroid;
};

#endif //               !__CARRIER_HPP__