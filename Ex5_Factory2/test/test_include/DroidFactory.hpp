#ifndef                 __DROIDFACTORY_HPP__
    #define             __DROIDFACTORY_HPP__

#include <iostream>
#include "Droid.hpp"
#include "Supply.hpp"
class                   DroidFactory
{
    public:
        explicit DroidFactory(size_t ratio = 2);
        DroidFactory(const DroidFactory &obj);
        ~DroidFactory(void);

        DroidFactory    &operator=(const DroidFactory &obj);
        Droid           *operator>>(Droid *&obj);
        DroidFactory    &operator<<(const Supply &obj);

        size_t          getRatio(void) const;
        void            setRatio(size_t ratio);

        size_t          getIron(void) const;
        void            setIron(size_t iron);

        size_t          getSilicon(void) const;
        void            setSilicon(size_t silicon);

        size_t          getWreck(void) const;
        void            setWreck(size_t wreck);

        size_t          getExp(void) const;
        void            setExp(size_t exp);

    private:
        size_t          _ratio;
        size_t          _Iron;
        size_t          _Silicon;
        size_t          _Wreck;
        size_t          _Exp;
};

// std::ostream& operator<<(std::ostream& os, const DroidFactory& factory) {
//     os << "DroidFactory status report :" << std::endl;
//     os << "Iron : " << factory.getIron() << std::endl;
//     os << "Silicon : " << factory.getSilicon() << std::endl;
//     os << "Exp : " << factory.getExp() << std::endl;
//     os << "End of status report.";
//     return os;
// }
#endif //               !__DROIDFACTORY_HPP__