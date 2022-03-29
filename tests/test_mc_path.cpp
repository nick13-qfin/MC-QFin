#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE mc_path test


#include <boost/test/unit_test.hpp>
#include "../lib/mc_path.h"

BOOST_AUTO_TEST_SUITE(mcpath)


BOOST_AUTO_TEST_CASE(getstate) 
{
    Eigen::MatrixXd m(3, 3);
    m << 1, 1.5, 1.3,
        1, 1.2, 1.3,
        1, 0.8, 0.7;
    mc::mc_path path(m);
    
    for (size_t j = 0; j < 3; j++)
    {
        const auto state = path.get_state(j);
        for (size_t i = 0; i < 3; i++)
        {
            BOOST_CHECK_EQUAL(state[i], m(i, j));
        }

    }
}

BOOST_AUTO_TEST_CASE(setvalue)
{
    Eigen::MatrixXd m(3, 3);
    m << 1, 1.5, 1.3,
        1, 1.2, 1.3,
        1, 0.8, 0.7;
    mc::mc_path path(m);

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            path.set_path_value(0.0, i, j);
            const auto state = path.get_state(j);
            const double val = state[i];
            BOOST_CHECK_EQUAL(val, 0.0);
            BOOST_CHECK_EQUAL(val, m(i, j)); // m is changed too!

        }
    }


}

BOOST_AUTO_TEST_SUITE_END()
