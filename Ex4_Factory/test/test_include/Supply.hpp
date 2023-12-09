#ifndef                 __SUPPLY_HPP__
    #define             __SUPPLY_HPP__

#include <iostream>
#include "Droid.hpp"
class                   Supply
{
    public:
        enum            Types
        {
            Iron = 1, 
            Silicon = 2, 
            Wreck = 3
        };

        Supply(Supply::Types type, size_t amount);
        Supply(Supply::Types type, size_t amount, Droid **droid);
        ~Supply(void);

        Types           getType(void) const;
        void            setType(Types type);

        size_t          getAmount(void) const;
        void            setAmount(size_t amount);

        Droid           **getPtrWreck(void) const;
        Droid           *getWreck(void) const;
        Droid           *getWreck(size_t index) const;
        void            setWreck(Droid **wreck);

    private:
        Types           Type;
        size_t          Amount;
        Droid           **Wrecks;
};

std::ostream          &operator<<(std::ostream &os, const Supply &obj);

#endif //               !__SUPPLY_HPP__