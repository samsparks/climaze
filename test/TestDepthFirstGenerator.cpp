#include <algorithm>
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <sstream>
#include "DepthFirstGenerator.hpp"

/// \brief define ostream operators in the std namespace so boost picks it up
namespace std
{
    
/// \brief define ostream operator to make BOOST_CHECK_EQUAL print a pretty comparision
std::ostream& operator<<(std::ostream& out, const Maze::Coordinate& coord)
{
    return out << "(" << coord.first << "," << coord.second << ")";
}

};

/// \brief define ostream operator to make BOOST_CHECK_EQUAL print a pretty comparision
template<typename T>
std::string ContainerToString(T container)
{
    if( container.empty() )
        return "";
    std::ostringstream ss;
    ss << "[";
    for( auto itr = std::begin(container); itr != std::end(container); ++itr )
    {
        if( itr != std::begin(container) )
            ss << ", ";
        ss << *itr;
    }
    ss << "]";
    return ss.str();
}

/// \brief custom predicate to test if an object is in a list
template<typename T>
boost::test_tools::predicate_result
Contains( const T& container, const typename T::value_type& value )
{
    if( std::find(std::begin(container), std::end(container), value) == std::end(container) )
    {
        boost::test_tools::predicate_result res( false );
        res.message() << "Element not found. [value=" << value << ", container=" << ContainerToString(container) << "]";
        return res;
    }

    return true;
}

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
        BOOST_CHECK(maze.At(i,0).Visited());
        BOOST_CHECK(!maze.At(i,0).Opened());
        BOOST_CHECK(maze.At(i,col_count-1).Visited());
        BOOST_CHECK(!maze.At(i,col_count-1).Opened());
    }
    // first and last cell on each column should be visited and closed
    for(size_t i = 0; i < col_count; ++i)
    {
        BOOST_CHECK(maze.At(0,i).Visited());
        BOOST_CHECK(!maze.At(0,i).Opened());
        BOOST_CHECK(maze.At(row_count-1,i).Visited());
        BOOST_CHECK(!maze.At(row_count-1,i).Opened());
    }
}

BOOST_AUTO_TEST_CASE( NextCellNoneAvailable )
{
    Maze maze(3,3);
    DepthFirstGenerator generator(maze);

    // block off transition to all neighboring cells
    maze.At(0,0).Visit();
    maze.At(0,1).Visit();
    maze.At(0,2).Visit();
    maze.At(1,0).Visit();
    auto start = std::make_pair<size_t,size_t>(1,1);
    maze.At(1,2).Visit();
    maze.At(2,0).Visit();
    maze.At(2,1).Visit();
    maze.At(2,2).Visit();

    // return the same coordinate if none are available
    BOOST_CHECK_EQUAL( generator.NextCell(start), start );
}

BOOST_AUTO_TEST_CASE( NextCellOneAvailable )
{
    Maze maze(3,3);
    DepthFirstGenerator generator(maze);

    // block off transition to all but the cell above the start
    maze.At(0,0).Visit();
    auto end = std::make_pair<size_t,size_t>(0,1);
    maze.At(0,2).Visit();
    maze.At(1,0).Visit();
    auto start = std::make_pair<size_t,size_t>(1,1);
    maze.At(1,2).Visit();
    maze.At(2,0).Visit();
    maze.At(2,1).Visit();
    maze.At(2,2).Visit();

    BOOST_CHECK_EQUAL( generator.NextCell(start), end );
}

BOOST_AUTO_TEST_CASE( NextCellManyAvailable )
{
    Maze maze(3,3);
    DepthFirstGenerator generator(maze);
    std::vector<Maze::Coordinate> available_cells;

    // block off transition to the bottom row. 
    available_cells.push_back(std::make_pair<size_t,size_t>(0,0));
    available_cells.push_back(std::make_pair<size_t,size_t>(0,1));
    available_cells.push_back(std::make_pair<size_t,size_t>(0,2));
    available_cells.push_back(std::make_pair<size_t,size_t>(1,0));
    auto start = std::make_pair<size_t,size_t>(1,1);
    available_cells.push_back(std::make_pair<size_t,size_t>(1,2));
    maze.At(2,0).Visit();
    maze.At(2,1).Visit();
    maze.At(2,2).Visit();

    auto end = generator.NextCell(start);
    BOOST_CHECK( Contains(available_cells, end) );
}

BOOST_AUTO_TEST_CASE( Generate )
{
    // verify all cells are visited
    // verify start matches the one passed in
    // verify a end is set
}

BOOST_AUTO_TEST_SUITE_END()
