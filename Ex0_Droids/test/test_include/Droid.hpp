#ifndef         __DROID_HPP__
    #define     __DROID_HPP__

#include <iostream>
#include <ostream>
class           Droid
{
    public:
        Droid(void);
        Droid(std::string Id);
        Droid(const Droid& obj);

        ~Droid(void);

        std::string         getId(void) const;
        size_t              getEnergy(void) const;
        size_t              getAttack(void) const;
        size_t              getToughness(void) const;
        std::string         *getStatus(void) const;

        void                setId(std::string id);
        void                setEnergy(size_t energy);
        void                setStatus(const std::string &status);

        Droid               &operator=(const Droid &rhs);
        Droid               &operator<<(size_t &reload);
        bool                operator==(const Droid &rhs) const;
        bool                operator!=(const Droid &rhs) const;
    private:
        std::string         _Id;
        size_t              _Energy;
        const size_t        _Attack;
        const size_t        _Toughness;
        std::string         *_Status;
};

std::ostream                &operator<<(std::ostream &ostream,
                                        const Droid &obj);


#endif //       !__DROID_HPP__