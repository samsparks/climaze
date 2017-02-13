#include <algorithm>
#include <boost/test/unit_test.hpp>
#include "DepthFirstGenerator.hpp"

BOOST_AUTO_TEST_SUITE(TestDepthFirst)

BOOST_AUTO_TEST_CASE( VisitBorders )
{
    const size_t row_count = 15;
    const size_t col_count = 20;
    Maze maze(row_count, col_count);
    DepthFirstGenerator generator(maze);
    generator.VisitBorders();
    // first and last cell on each row should be visited and closed
    for(size_t i = 0; i < row_count; ++i)
    {
        BOOST_CHECK(maze.at(i,0).Visited());
        BOOST_CHECK(!maze.at(i,0).Opened());
        BOOST_CHECK(maze.at(i,col_count-1).Visited());
        BOOST_CHECK(!maze.at(i,col_count-1).Opened());
    }
    // first and last cell on each column should be visited and closed
    for(size_t i = 0; i < col_count; ++i)
    {
        BOOST_CHECK(maze.at(0,i).Visited());
        BOOST_CHECK(!maze.at(0,i).Opened());
        BOOST_CHECK(maze.at(row_count-1,i).Visited());
        BOOST_CHECK(!maze.at(row_count-1,i).Opened());
    }
}

BOOST_AUTO_TEST_CASE( NextCellNoneAvailable )
{
    Maze maze(3,3);
    DepthFirstGenerator generator(maze);

    // block off transition to all neighboring cells
    maze.at(0,0).Visit();
    maze.at(0,1).Visit();
    maze.at(0,2).Visit();
    maze.at(1,0).Visit();
    auto start = std::make_pair<size_t,size_t>(1,1);
    maze.at(1,2).Visit();
    maze.at(2,0).Visit();
    maze.at(2,1).Visit();
    maze.at(2,2).Visit();

    // return the same coordinate if none are available
    BOOST_CHECK( generator.NextCell(start) == start );
}

BOOST_AUTO_TEST_CASE( NextCellOneAvailable )
{
    Maze maze(2,2);
    DepthFirstGenerator generator(maze);

    // block off transition to all but the cell above the start
    maze.at(0,0).Visit();
    auto end = std::make_pair<size_t,size_t>(0,1);
    maze.at(0,2).Visit();
    maze.at(1,0).Visit();
    auto start = std::make_pair<size_t,size_t>(1,1);
    maze.at(1,2).Visit();
    maze.at(2,0).Visit();
    maze.at(2,1).Visit();
    maze.at(2,2).Visit();

    BOOST_CHECK( generator.NextCell(start) == end );
}

BOOST_AUTO_TEST_CASE( NextCellManyAvailable )
{
    Maze maze(2,2);
    DepthFirstGenerator generator(maze);
    //TODO: i feel like perfect forwarding should work here...
    std::vector<Maze::Coordinate> available_cells;

    // block off transition to the bottom row. 
    available_cells.push_back(std::make_pair<size_t,size_t>(0,0));
    available_cells.push_back(std::make_pair<size_t,size_t>(0,1));
    available_cells.push_back(std::make_pair<size_t,size_t>(0,2));
    available_cells.push_back(std::make_pair<size_t,size_t>(1,1));
    auto start = std::make_pair<size_t,size_t>(1,1);
    available_cells.push_back(std::make_pair<size_t,size_t>(1,2));
    maze.at(2,0).Visit();
    maze.at(2,1).Visit();
    maze.at(2,2).Visit();

    auto end = generator.NextCell(start);
    BOOST_CHECK( std::find(available_cells.begin(), available_cells.end(), end) != available_cells.end() );
}

BOOST_AUTO_TEST_CASE( Generate )
{
    // verify all cells are visited
    // verify start matches the one passed in
    // verify a end is set
}

BOOST_AUTO_TEST_SUITE_END()
