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

        size_t          getNbWreck(void) const;
        void            setNbWreck(size_t nb);

        operator size_t(void) const;

        Droid           *&operator*(void) const;
        Droid           *operator->(void) const;
        Supply          &operator++(void);
        Supply          &operator--(void);
        Supply          &operator!(void);

    private:
        Types           Type;
        size_t          Amount;
        Droid           **Wrecks;
        size_t          nbWreck;
};

std::ostream          &operator<<(std::ostream &os, const Supply &obj);

#endif //               !__SUPPLY_HPP__