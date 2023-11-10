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

Test(Droid, test_Droid_setId, .init = redirect_all_stdout)
{
    Droid   d;

    cr_assert(d.getId() == "");
    d.setId("Droid");
    cr_assert(d.getId() == "Droid");
}

Test(Droid, test_Droid_setEnergy, .init = redirect_all_stdout)
{
    Droid   d;

    cr_assert(d.getEnergy() == 50);
    d.setEnergy(100);
    cr_assert(d.getEnergy() == 100);
}

Test(Droid, test_Droid_setStatus, .init = redirect_all_stdout)
{
    Droid   d;

    cr_assert_str_eq(d.getStatus()->data(), "Standing by");
    d.setStatus("Pending");
    cr_assert_str_eq(d.getStatus()->data(), "Pending");
    d.~Droid();
    d.setStatus("Updated");
}

Test(Droid, test_Droid_operator_equal_overloading, .init = redirect_all_stdout)
{
    Droid d;
    Droid d1("Avanger");

    cr_assert(d.getId() != d1.getId());
    cr_assert(d.getEnergy() == d1.getEnergy());
    cr_assert(d.getAttack() == d1.getAttack());
    cr_assert(d.getToughness() == d1.getToughness());
    cr_assert(d.getStatus()->data() != d1.getStatus()->data());

    d = d1;

    cr_assert(d.getId() == d1.getId());
    cr_assert(d.getEnergy() == d1.getEnergy());
    cr_assert(d.getAttack() == d1.getAttack());
    cr_assert(d.getToughness() == d1.getToughness());
    cr_assert_str_eq(d.getStatus()->data(), d1.getStatus()->data());
}

Test(Droid, test_Droid_left_stream_operator_overloading, .init = redirect_all_stdout)
{
    {
        Droid d("Avenger");

        std::cout << d << std::endl;
    }
    cr_assert_stdout_eq_str(
        "Droid 'Avenger' Activated\n"
        "Droid 'Avenger', Standing by, 50\n"
        "Droid 'Avenger' Destroyed\n");
}