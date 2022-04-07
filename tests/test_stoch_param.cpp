#define BOOST_TEST_MODULE stochparam test

#include <boost/test/unit_test.hpp>
#include "../montecarlo/parameters/stoch_dep_param.h"
#include "../montecarlo/stochastic_processes/geometric_brownian_motion.h"

BOOST_AUTO_TEST_SUITE(stochparam)
using gbm_t = mc::geometric_brownian_motion<mc::constant_param, mc::constant_param>;

BOOST_AUTO_TEST_CASE(makefromptr)
{
    auto gbm = std::make_unique<gbm_t>( 0.01, 0.2, 1 );
    mc::dummy_lambda l{};
    auto sqrdgbm = mc::make_stoch_param(std::move(gbm), l);


    BOOST_CHECK_EQUAL(0.0, 0.0);

}

BOOST_AUTO_TEST_CASE(makefromobj)
{
    gbm_t gbm{ 0.01, 0.2, 1 };//
    mc::dummy_lambda l{};
    auto sqrdgbm = mc::make_stoch_param(gbm, l);


    BOOST_CHECK_EQUAL(0.0, 0.0);

}


BOOST_AUTO_TEST_SUITE_END()
