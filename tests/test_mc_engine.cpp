#define BOOST_TEST_MODULE mcengine test

#include <boost/test/unit_test.hpp>
#include "../lib/mc_engine.h"
#include "../lib/stochastic_processes/geometric_brownian_motion.h"
#include "../lib/evolution_schemes/euler_scheme.h"
#include "../lib/parameters/parameter.h"
#include "../lib/interpolation/pwc_interpolator.h"
#include <tuple>

BOOST_AUTO_TEST_SUITE(mcengine)
using gbm_t = mc::geometric_brownian_motion<mc::constant_param, mc::constant_param>;
using param_t = mc::time_dep_param<utils::pwc_interp<utils::unchecked_boundaries>>;
using gbm2_t = mc::geometric_brownian_motion<param_t, mc::constant_param>;

BOOST_AUTO_TEST_CASE(constr_singlescheme)
{
	auto gbm = std::make_unique<gbm_t>(0.01, 0.2, 0.0, true);
	auto scheme = std::make_unique<mc::euler_scheme<gbm_t>>(0, 1, 0.1, std::move(gbm));

	mc::mc_engine< mc::euler_scheme<gbm_t>> engine(std::move(scheme));
    const bool is_mc_engine = std::is_same_v<mc::mc_engine< mc::euler_scheme<gbm_t>>, decltype(engine)>;

	BOOST_CHECK_EQUAL(is_mc_engine, true);
}


BOOST_AUTO_TEST_CASE(constr_tuple)
{
	auto gbm = std::make_unique<gbm_t>(0.01, 0.2, 0.0, true);
	auto scheme = std::make_unique<mc::euler_scheme<gbm_t>>(0, 1, 0.1, std::move(gbm));

    auto x = std::vector<double>{0.0, 1.0};
    auto t = std::vector<double>{0.0, 1.0};
    auto mu = std::make_unique<param_t>(x, t);
	auto gbm2 = std::make_unique<gbm2_t>(std::move(mu), std::make_unique<mc::constant_param>(0.1), 0.0); 
	auto scheme2 = std::make_unique<mc::euler_scheme<gbm2_t>>(0, 1, 0.1, std::move(gbm2));
    
    auto mc_engine = mc::make_mcengine(std::move(scheme), std::move(scheme2));
    const bool is_mc_engine = std::is_same_v<mc::mc_engine< mc::euler_scheme<gbm_t>, mc::euler_scheme<gbm2_t>>, decltype(mc_engine)>;
	BOOST_CHECK_EQUAL(is_mc_engine, true);
}

BOOST_AUTO_TEST_CASE(calculate)
{
	auto gbm = std::make_unique<gbm_t>(0.01, 0.2, 1.0, true);
	auto scheme = std::make_unique<mc::euler_scheme<gbm_t>>(0, 1, 0.1, std::move(gbm));

    auto x = std::vector<double>{0.0, 1.0};
    auto t = std::vector<double>{0.0, 1.0};
    auto mu = std::make_unique<param_t>(x, t);
	auto gbm2 = std::make_unique<gbm2_t>(std::move(mu), std::make_unique<mc::constant_param>(0.1), 0.0); 
	auto scheme2 = std::make_unique<mc::euler_scheme<gbm2_t>>(0, 1, 0.1, std::move(gbm2));
    
    auto mc_engine = mc::make_mcengine(std::move(scheme), std::move(scheme2));

	mc::dummy_payoff payoff{};
	auto result = mc_engine.calculate(payoff);
    
}




BOOST_AUTO_TEST_SUITE_END()
