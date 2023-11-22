#ifndef         __DROID_HPP__
    #define     __DROID_HPP__

#include <iostream>
#include <ostream>
#include "DroidMemory.hpp"
class           Droid
{
    public:
        Droid(std::string Id);
        Droid(const Droid& obj);

        ~Droid(void);

        std::string         getId(void) const;
        size_t              getEnergy(void) const;
        size_t              getAttack(void) const;
        size_t              getToughness(void) const;
        std::string         *getStatus(void) const;
        DroidMemory         *getBattleData(void) const;

        void                setId(std::string id);
        void                setEnergy(size_t energy);
        void                setStatus(const std::string *status);
        void                setBattleData(const DroidMemory *newBattleData);

        Droid               &operator=(const Droid &rhs);
        Droid               &operator<<(size_t &reload);
        bool                operator==(const Droid &rhs) const;
        bool                operator!=(const Droid &rhs) const;
        bool                operator()(const std::string *task, size_t expRequired);
    private:
        std::string         _Id;
        size_t              _Energy;
        const size_t        _Attack;
        const size_t        _Toughness;
        std::string         *_Status;
        DroidMemory         *BattleData;
};

std::ostream                &operator<<(std::ostream &ostream,
                                        const Droid &obj);


#endif //       !__DROID_HPP__