#include <boost/test/unit_test.hpp>
#include "Maze.hpp"

BOOST_AUTO_TEST_SUITE(TestMaze)

BOOST_AUTO_TEST_CASE( Initialization )
{
    BOOST_CHECK_EQUAL( Maze(2,4).Rows(), 2 );
    BOOST_CHECK_EQUAL( Maze(2,4).Columns(), 4 );
    BOOST_CHECK_EQUAL( Maze(10,2).Rows(), 10 );
    BOOST_CHECK_EQUAL( Maze(10,2).Columns(), 2 );

    BOOST_CHECK_THROW( Maze(0,4), std::invalid_argument );
    BOOST_CHECK_THROW( Maze(2,0), std::invalid_argument );
}


BOOST_AUTO_TEST_CASE( AccessByRowAndColumn )
{
    Maze maze(2,4);

    // valid cells
    for( size_t r = 0; r < 2; ++r )
    {
        for( size_t c = 0; c < 4; ++c )
        {
            BOOST_REQUIRE_EQUAL( maze.Contains(r,c), true );
            BOOST_CHECK_EQUAL( maze.At(r,c).Visited(), false );
            maze.At(r,c).Visit();
        }
    }

    // invalid cells. size_t is usigned, so only test upper bound
    BOOST_CHECK_THROW( maze.At(2,1), std::out_of_range );
    BOOST_CHECK_EQUAL( maze.Contains(2,1), false );
    BOOST_CHECK_THROW( maze.At(1,4), std::out_of_range );
    BOOST_CHECK_EQUAL( maze.Contains(1,4), false );
}

BOOST_AUTO_TEST_CASE( AccessByCoordinate )
{
    Maze maze(1,3);

    // valid cells
    for( size_t r = 0; r < 1; ++r )
    {
        for( size_t c = 0; c < 3; ++c )
        {
            auto coord = std::make_pair(r, c);
            BOOST_REQUIRE_EQUAL( maze.Contains(coord), true );
            BOOST_CHECK_EQUAL( maze.At(coord).Opened(), false );
            maze.At(coord).Open();
        }
    }
            
    // invalid cells. size_t is usigned, so only test upper bound
    BOOST_CHECK_THROW( maze.At(std::make_pair<size_t, size_t>(1,1)), std::out_of_range );
    BOOST_CHECK_EQUAL( maze.Contains(std::make_pair<size_t, size_t>(1,3)), false );
    BOOST_CHECK_THROW( maze.At(std::make_pair<size_t, size_t>(1,1)), std::out_of_range );
    BOOST_CHECK_EQUAL( maze.Contains(std::make_pair<size_t, size_t>(1,3)), false );
}

BOOST_AUTO_TEST_CASE( Accessors )
{
    Cell c;
    BOOST_CHECK_EQUAL( c.Visited(), false );
    BOOST_CHECK_EQUAL( c.Visit().Visited(), true );
    BOOST_CHECK_EQUAL( c.Opened(), false );
    BOOST_CHECK_EQUAL( c.Open().Opened(), true );
    BOOST_CHECK_EQUAL( c.Close().Opened(), false );
}

BOOST_AUTO_TEST_SUITE_END()
