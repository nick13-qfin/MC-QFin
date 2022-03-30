
#define BOOST_TEST_MODULE evol test

#include <boost/test/unit_test.hpp>
#include "../lib/evolution_schemes/euler_scheme.h"
#include "../lib/stochastic_processes/geometric_brownian_motion.h"
#include <stdexcept>


BOOST_AUTO_TEST_SUITE(evolscheme)
using gbm_t = mc::geometric_brownian_motion<mc::constant_param, mc::constant_param>;
BOOST_AUTO_TEST_CASE(timeline)
{
    mc::timeline t(0, 1, 0.1);
    auto n = t.get_n(); // todo wrong

    BOOST_CHECK_EQUAL(t.get_time(0), 0.0);
    BOOST_CHECK_EQUAL(t.get_time(n - 1), 1.0);

}

BOOST_AUTO_TEST_CASE(constructor)
{
    mc::timeline t(0, 1, 0.1);
    auto n = t.get_n(); // todo wrong
    auto gbm = std::make_unique<gbm_t>(0.2, 0.2, 0.0);

    mc::euler_scheme<gbm_t> scheme(0.0, 1.0, 0.1, std::move(gbm));

    BOOST_CHECK_EQUAL(t.get_time(0), 0.0);
    BOOST_CHECK_EQUAL(t.get_time(n - 1), 1.0);

}




BOOST_AUTO_TEST_SUITE_END()
