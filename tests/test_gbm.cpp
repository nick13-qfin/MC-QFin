
#define BOOST_TEST_MODULE gbm test

#include <boost/test/unit_test.hpp>
#include "../lib/stochastic_processes/geometric_brownian_motion.h"
#include <stdexcept>


BOOST_AUTO_TEST_SUITE(gbm)
using gbm_t = mc::geometric_brownian_motion<mc::constant_param, mc::constant_param>;
BOOST_AUTO_TEST_CASE(gbmtest1)
{
	mc::constant_param p();
	
    gbm_t gbm(0.1, 0.2, 0.0);
    
    mc::dummy_state state(0.0, std::vector<double>{2.0});
    
    const auto drift_term = gbm.drift(state);
    const auto vol_term = gbm.diffusion(state);
    
	BOOST_CHECK_EQUAL(drift_term, 0.2);
	BOOST_CHECK_EQUAL(vol_term, 0.4);

}

BOOST_AUTO_TEST_CASE(gbmtest2)
{
	mc::constant_param p();
	bool reset_processes = true; //you need to reset the process counter
    
    gbm_t gbm(0.1, 0.2, 0.0, reset_processes);
    gbm_t gbm_2nd(0.1, 0.2, 0.0); // this will break with a single state
    
    mc::dummy_state state(0.0, std::vector<double>{2.0, 1.0});
    const auto drift_term = gbm_2nd.drift(state);
    const auto vol_term = gbm_2nd.diffusion(state);
    
    BOOST_CHECK_EQUAL(drift_term, 0.1);
	BOOST_CHECK_EQUAL(vol_term, 0.2);
    
//     BOOST_CHECK_THROW (const auto drift_term = gbm_2nd.drift(state), std::out_of_range);

}


BOOST_AUTO_TEST_SUITE_END()