#define BOOST_TEST_MODULE eigen test

#include <boost/test/unit_test.hpp>
#include <Eigen/Dense>

BOOST_AUTO_TEST_SUITE(eigen)


BOOST_AUTO_TEST_CASE(mapvector)
{
    Eigen::MatrixXd m(3, 3);
    m << 1, 2, 3,
        1, 2, 3,
        1, 2, 3;

    Eigen::Map<Eigen::VectorXd> v(m.data() + 3, 3, 1);

    std::cout << v;
    BOOST_CHECK_EQUAL(v[0], 2);
    BOOST_CHECK_EQUAL(v[1], 2);
    BOOST_CHECK_EQUAL(v[2], 2);
}

BOOST_AUTO_TEST_CASE(mapmatrix)
{
    Eigen::MatrixXd m(3, 3);
    m << 1, 2, 3,
        1, 2, 3,
        1, 2, 3;
    BOOST_TEST_MESSAGE("cout m");
    std::cout << m;

    Eigen::Map<Eigen::MatrixXd> v(m.data(), m.rows(), m.cols());

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
            BOOST_CHECK_EQUAL(m(i,j), v(i,j));
    }
}


BOOST_AUTO_TEST_SUITE_END()
