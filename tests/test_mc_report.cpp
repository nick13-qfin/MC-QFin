#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE mc_report test


#include <boost/test/unit_test.hpp>
#include "../lib/mc_representation/output_report.h"

BOOST_AUTO_TEST_SUITE(mc_report)


BOOST_AUTO_TEST_CASE(moveassignement)
{
    auto rep1 = mc::mc_report();
    rep1.add_result(0.1);
    BOOST_CHECK_EQUAL(rep1[0], 0.1);
    BOOST_CHECK_EQUAL(rep1.get_n(), 1);

    mc::mc_report rep2(std::move(rep1));
    BOOST_CHECK_EQUAL(rep1.get_n(), 0);
    BOOST_CHECK_EQUAL(rep2.get_n(), 1);
    BOOST_CHECK_EQUAL(rep2[0], 0.1);

}


BOOST_AUTO_TEST_SUITE_END()
