#include <boost/test/unit_test.hpp>

#include "Coordinate.hpp"

BOOST_AUTO_TEST_SUITE(TestCoordinate)

BOOST_AUTO_TEST_CASE( Constructor )
{
    BOOST_CHECK_EQUAL( Coordinate(1,2).Row(), 1 );
    BOOST_CHECK_EQUAL( Coordinate(1,2).Column(), 2 );
}


BOOST_AUTO_TEST_SUITE_END()
