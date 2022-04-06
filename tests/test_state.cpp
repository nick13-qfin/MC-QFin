#define BOOST_TEST_MODULE state test

#include <boost/test/unit_test.hpp>
#include "../montecarlo/mc_representation/state.h"
#include <stdexcept>


BOOST_AUTO_TEST_SUITE(state)

BOOST_AUTO_TEST_CASE(defaultstate)
{
    size_t n_states{ 3 };
    mc::markovian_state state(n_states);
    BOOST_CHECK_EQUAL(state.n_states(), n_states);

    for(size_t i = 0; i < n_states; ++i)
        BOOST_CHECK_EQUAL(state[i], 0.0);
}

BOOST_AUTO_TEST_CASE(setstate)
{
    Eigen::MatrixXd m(3, 3);
    m << 1, 2, 3,
        1, 2, 3,
        1, 2, 3;
    mc::markovian_state state(0.0, std::vector<double>{0.0, 0.0, 0.0});

    BOOST_CHECK_EQUAL(state[0], 0.0);
    BOOST_CHECK_EQUAL(state[1], 0.0);
    BOOST_CHECK_EQUAL(state[2], 0.0);

    Eigen::Map<Eigen::MatrixXd> p(m.data(), 3, 3);

    state.set_state(p, 1);

    BOOST_CHECK_EQUAL(state[0], 2);
    BOOST_CHECK_EQUAL(state[1], 2);
    BOOST_CHECK_EQUAL(state[2], 2);
}

BOOST_AUTO_TEST_SUITE_END()
