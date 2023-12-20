#ifndef                 __DROIDFACTORY_HPP__
    #define             __DROIDFACTORY_HPP__

#include <iostream>
#include "Droid.hpp"
class                   DroidFactory
{
    public:
        explicit DroidFactory(size_t ratio = 2);
        DroidFactory(const DroidFactory &obj);
        ~DroidFactory(void);

        DroidFactory    &operator=(const DroidFactory &obj);
        Droid           *operator>>(Droid *obj);

        size_t          getRatio(void) const;
        void            setRatio(size_t ratio);

        size_t          getIron(void) const;
        void            setIron(size_t iron);

        size_t          getSilicon(void) const;
        void            setSilicon(size_t silicon);

        size_t          getExp(void) const;
        void            setExp(size_t exp);

    private:
        size_t          _ratio;
        size_t          _Iron;
        size_t          _Silicon;
        size_t          _Exp;
};
#endif //               !__DROIDFACTORY_HPP__