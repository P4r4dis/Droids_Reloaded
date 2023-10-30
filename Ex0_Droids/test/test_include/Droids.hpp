#ifndef         __DROIDS_HPP__
    #define     __DROIDS_HPP__

#include <iostream>
class           Droids
{
    public:
        Droids(void);
        Droids(std::string Id);
        Droids(const Droids& obj);

        std::string         getId(void) const;
        size_t              getEnergy(void) const;
        size_t              getAttack(void) const;
        size_t              getToughness(void) const;
        std::string         *getStatus(void) const;
    private:
        std::string         _Id;
        size_t              _Energy;
        const size_t        _Attack;
        const size_t        _Toughness;
        std::string         *_Status;
};

#endif //       !__DROIDS_HPP__