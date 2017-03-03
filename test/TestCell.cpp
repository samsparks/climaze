#include <boost/test/unit_test.hpp>
#include "Cell.hpp"

BOOST_AUTO_TEST_SUITE(TestCell)

BOOST_AUTO_TEST_CASE( Initialization )
{
    Cell c;
    BOOST_CHECK_EQUAL( c.Visited(), false );
    BOOST_CHECK_EQUAL( c.Opened(), false );
}

BOOST_AUTO_TEST_CASE( Accessors )
{
    Cell c;
    BOOST_CHECK_EQUAL( c.Visited(), false );
    BOOST_CHECK_EQUAL( c.Visit().Visited(), true );
    BOOST_CHECK_EQUAL( c.Opened(), false );
    BOOST_CHECK_EQUAL( c.Open().Opened(), true );
}

BOOST_AUTO_TEST_SUITE_END()
