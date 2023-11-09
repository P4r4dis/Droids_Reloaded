#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <criterion/logging.h>
#include <criterion/parameterized.h>
#include <signal.h>

#include "../test_include/Droid.hpp"

void    redirect_all_stdout(void) {
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(Droid, test_Droid_ctor_dtor__without_parameters, .init = redirect_all_stdout)
{
    {
        Droid d;
        cr_assert(d.getId() == "");
        cr_assert(d.getEnergy() == 50);
        cr_assert(d.getAttack() == 25);
        cr_assert(d.getToughness() == 15);
        cr_assert(d.getStatus()->compare("Standing by") == 0);
        cr_assert_str_eq(d.getStatus()->data(), "Standing by");
    }

    cr_assert_stdout_eq_str("Droid '' Activated\nDroid '' Destroyed\n");
}

Test(Droid, test_Droid_constructor_with_parameters, .init = redirect_all_stdout)
{
    {
        Droid  d("Avenger");

        cr_assert(d.getId() == "Avenger");
        cr_assert(d.getEnergy() == 50);
        cr_assert(d.getAttack() == 25);
        cr_assert(d.getToughness() == 15);
        cr_assert(d.getStatus()->compare("Standing by") == 0);
        cr_assert_str_eq(d.getStatus()->data(), "Standing by");
    }

    cr_assert_stdout_eq_str("Droid 'Avenger' Activated\nDroid 'Avenger' Destroyed\n");
}

Test(Droid, test_Droid_copy_Constructor, .init = redirect_all_stdout)
{
    {    
        Droid  d0("Avenger");
        Droid  d(d0);

        cr_assert(d.getId() == "Avenger");
        cr_assert(d.getEnergy() == 50);
        cr_assert(d.getAttack() == 25);
        cr_assert(d.getToughness() == 15);
        cr_assert(d.getStatus()->compare("Standing by") == 0);
        cr_assert_str_eq(d.getStatus()->data(), "Standing by");
    }
    cr_assert_stdout_eq_str("Droid 'Avenger' Activated\n"
    "Droid 'Avenger' Activated, Memory Dumped\n"
    "Droid 'Avenger' Destroyed\n"
    "Droid 'Avenger' Destroyed\n");
}
