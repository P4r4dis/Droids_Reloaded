#ifndef                 __DROIDFACTORY_HPP__
    #define             __DROIDFACTORY_HPP__

#include <iostream>

class                   DroidFactory
{
    public:
        explicit DroidFactory(size_t ratio = 2);
        DroidFactory(const DroidFactory &obj);
        ~DroidFactory(void);

        DroidFactory    &operator=(const DroidFactory &obj);

        size_t          getRatio(void) const;
        void            setRatio(size_t ratio);
    private:
        size_t          _ratio;
};
#endif //               !__DROIDFACTORY_HPP__