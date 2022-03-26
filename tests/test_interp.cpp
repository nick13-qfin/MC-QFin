//#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE interpolator test


#include <boost/test/unit_test.hpp>
#include "../lib/interpolator_base.h"


BOOST_AUTO_TEST_SUITE(interp)

BOOST_AUTO_TEST_CASE(movevectors)
{
    std::vector<double> x{ 0.0, 1.0, 2.0 };
    std::vector<double> f{ -1.0, -3.0, 5.0 };

    const auto interp = utils::pwc_interp<void>(std::move(x), std::move(f));
    BOOST_CHECK_EQUAL(x.size(), 0);
    BOOST_CHECK_EQUAL(f.size(), 0);

}

BOOST_AUTO_TEST_CASE(pwc1)
{
    std::vector<double> x{ 0.0, 1.0, 2.0 };
    std::vector<double> f{ -1.0, -3.0, 5.0 };

    const auto interp = utils::pwc_interp<void>(x, f);
    BOOST_CHECK_EQUAL(x.size(), 3);
    BOOST_CHECK_EQUAL(f.size(), 3);

    BOOST_CHECK_EQUAL(interp.value(0.0), -1.0);
    BOOST_CHECK_EQUAL(interp.value(1.0), -3.0);
    BOOST_CHECK_EQUAL(interp.value(2.0), -3.0); // TODO: check
}

BOOST_AUTO_TEST_SUITE_END()