// --------------------------------
// projects/g++/graph/TestGraph.c++
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------------

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair

#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

#include "gtest/gtest.h"

#include "Graph.h"

using namespace std;

using testing::Test;
using testing::Types;

// ---------
// TestGraph
// ---------

template <typename G>
struct TestGraph : Test {
    // --------
    // typedefs
    // --------

    typedef          G                     graph_type;
    using vertex_descriptor   = typename G::vertex_descriptor;
    using edge_descriptor     = typename G::edge_descriptor;
    using vertex_iterator     = typename G::vertex_iterator;
    using edge_iterator       = typename G::edge_iterator;
    using adjacency_iterator  = typename G::adjacency_iterator;
    using vertices_size_type  = typename G::vertices_size_type;
    using edges_size_type     = typename G::edges_size_type;};

// directed, sparse, unweighted
// possibly connected
// possibly cyclic
typedef Types<
            boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>,
            Graph>
        graph_types;

TYPED_TEST_CASE(TestGraph, graph_types);

TYPED_TEST(TestGraph, test_vertex) {
    using graph_type         = typename TestFixture::graph_type;
    using vertex_descriptor  = typename TestFixture::vertex_descriptor;
    using vertices_size_type = typename TestFixture::vertices_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    vertex_descriptor vd = vertex(0, g);
    ASSERT_EQ(vdA, vd);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(1, vs);}

TYPED_TEST(TestGraph, test_edge) {
    using graph_type        = typename TestFixture::graph_type;
    using vertex_descriptor = typename TestFixture::vertex_descriptor;
    using edge_descriptor   = typename TestFixture::edge_descriptor;
    using edges_size_type   = typename TestFixture::edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(false, p1.second);

    pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);

    vertex_descriptor vd1 = source(edAB, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = target(edAB, g);
    ASSERT_EQ(vdB, vd2);}

TYPED_TEST(TestGraph, test_vertices) {
    using graph_type        = typename TestFixture::graph_type;
    using vertex_descriptor = typename TestFixture::vertex_descriptor;
    using vertex_iterator   = typename TestFixture::vertex_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                        b = p.first;
    vertex_iterator                        e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    ASSERT_EQ(e, b);}

TYPED_TEST(TestGraph, test_edges) {
    using graph_type        = typename TestFixture::graph_type;
    using vertex_descriptor = typename TestFixture::vertex_descriptor;
    using edge_descriptor   = typename TestFixture::edge_descriptor;
    using edge_iterator     = typename TestFixture::edge_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;

    pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                      b = p.first;
    edge_iterator                      e = p.second;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAB, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAC, ed);}
    ++b;
    ASSERT_EQ(e, b);}

TYPED_TEST(TestGraph, test_adjacent_vertices) {
    using graph_type          = typename TestFixture::graph_type;
    using vertex_descriptor   = typename TestFixture::vertex_descriptor;
    using adjacency_iterator  = typename TestFixture::adjacency_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);

    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator                           b = p.first;
    adjacency_iterator                           e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;
    ASSERT_EQ(e, b);}



TYPED_TEST(TestGraph, test_add_edge1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    

    pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(true, p1.second);


    pair<edge_descriptor, bool> p2 = add_edge(vdA, vdB, g);
    ASSERT_EQ(p2.first,  p1.first);
    ASSERT_EQ(false, p2.second);
}

TYPED_TEST(TestGraph, test_add_edge2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    

    pair<edge_descriptor, bool> p1 = add_edge(vdA, vdC, g);
    ASSERT_EQ(true, p1.second);


    pair<edge_descriptor, bool> p2 = add_edge(vdA, vdB, g);
    ASSERT_TRUE(p2.first != p1.first);
    ASSERT_EQ(true, p2.second);
}

TYPED_TEST(TestGraph, test_add_edge3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    

    pair<edge_descriptor, bool> p1 = add_edge(vdA, vdC, g);
    ASSERT_EQ(true, p1.second);


    pair<edge_descriptor, bool> p2 = add_edge(vdA, vdB, g);
    pair<edge_descriptor, bool> p3 = add_edge(vdB, vdA, g);
    ASSERT_EQ(true, p3.second);
    ASSERT_TRUE(p2.first != p3.first);

    ASSERT_EQ(true, p2.second);
    pair<edge_descriptor, bool> p4 = add_edge(vdE, vdE, g);
    ASSERT_EQ(true, p4.second);

    }

TYPED_TEST(TestGraph, test_add_edge4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;  

    pair<edge_descriptor, bool> p1 = add_edge(3, 5, g);
    ASSERT_EQ(true, p1.second);


    pair<edge_descriptor, bool> p2 = add_edge(3, 7, g);
    pair<edge_descriptor, bool> p3 = add_edge(3, 4, g);
    ASSERT_EQ(true, p3.second);
    ASSERT_TRUE(p2.first != p3.first);

    ASSERT_EQ(true, p2.second);

    }

TYPED_TEST(TestGraph, test_add_edge5) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;  

    pair<edge_descriptor, bool> p1 = add_edge(3, 3, g);
    ASSERT_EQ(true, p1.second);

    }


TYPED_TEST(TestGraph, test_add_vertex1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    typedef typename TestFixture::vertices_size_type vertices_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    ASSERT_TRUE(vdA != vdB);

    ASSERT_EQ(vdB , 1);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(2, vs);}


TYPED_TEST(TestGraph, test_add_vertex2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    typedef typename TestFixture::vertices_size_type vertices_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);

    ASSERT_TRUE(vdA != vdD);

    ASSERT_EQ(vdD , 3);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(4, vs);}

TYPED_TEST(TestGraph, test_add_vertex3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
   
    typedef typename TestFixture::vertices_size_type vertices_size_type;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);

    ASSERT_TRUE(vdA != vdC);

    ASSERT_EQ(vdF , 5);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(6, vs);}


TYPED_TEST(TestGraph, test_adjacent_vertices1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    typedef typename TestFixture::adjacency_iterator adjacency_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);

    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator                           b = p.first;
    adjacency_iterator                           e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;

    ASSERT_EQ(e, b);}


TYPED_TEST(TestGraph, test_adjacent_vertices2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    typedef typename TestFixture::adjacency_iterator adjacency_iterator;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);
    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);
    add_edge(vdA, vdD, g);
    add_edge(vdA, vdE, g);
    add_edge(vdC, vdA, g);
    add_edge(vdA, vdF, g);


    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator                           b = p.first;
    adjacency_iterator                           e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdD, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdE, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdF, vd);}
    ++b;

    ASSERT_EQ(e, b);}


TYPED_TEST(TestGraph, test_adjacent_vertices3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    typedef typename TestFixture::adjacency_iterator adjacency_iterator;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);
    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);
    add_edge(vdC, vdA, g);
    add_edge(vdC, vdB, g);


    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator                           b = p.first;
    adjacency_iterator                           e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;

    pair<adjacency_iterator, adjacency_iterator> p2 = adjacent_vertices(vdC, g);
    adjacency_iterator                           b2 = p2.first;
    adjacency_iterator                           e2 = p2.second;
    if (b2 != e2) {
        vertex_descriptor vd = *b2;
        ASSERT_EQ(vdA, vd);}
    ++b2;
    if (b2 != e2) {
        vertex_descriptor vd = *b2;
        ASSERT_EQ(vdB, vd);}
    ++b2;

    pair<adjacency_iterator, adjacency_iterator> p3 = adjacent_vertices(vdB, g);
    adjacency_iterator                           b3 = p3.first;
    adjacency_iterator                           e3 = p3.second;

    ASSERT_EQ(e, b);
    ASSERT_EQ(e2, b2);
    ASSERT_EQ(e3, b3);}

TYPED_TEST(TestGraph, test_edge1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    pair<edge_descriptor, bool> p1 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p1.first);
    ASSERT_EQ(true, p1.second);

    pair<edge_descriptor, bool> p2 = edge(vdB, vdA, g);
    ASSERT_TRUE(edAB != p2.first);
    ASSERT_EQ(false, p2.second);
}




TYPED_TEST(TestGraph, test_edge2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD= add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edCA = add_edge(vdC, vdA, g).first;

    pair<edge_descriptor, bool> p1 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p1.first);
    ASSERT_EQ(true, p1.second);

    pair<edge_descriptor, bool> p2 = edge(vdC, vdD, g);
    ASSERT_FALSE(edCA == p2.first);
    ASSERT_EQ(false, p2.second);
}

TYPED_TEST(TestGraph, test_edges1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    typedef typename TestFixture::edge_iterator      edge_iterator;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);

    pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;

    ASSERT_EQ(e, b);}


TYPED_TEST(TestGraph, test_edges2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    typedef typename TestFixture::edge_iterator      edge_iterator;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);

    edge_descriptor eAB = add_edge(vdA, vdB, g).first;
    edge_descriptor eAC = add_edge(vdA, vdC, g).first;
    edge_descriptor eCA = add_edge(vdC, vdA, g).first;

    pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(eAB, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(eAC, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(eCA, ed);}
    ++b;

    ASSERT_EQ(e, b);}



TYPED_TEST(TestGraph, test_source1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edBA = add_edge(vdB, vdA, g).first;


    vertex_descriptor sr1 = source(edAB, g);
    ASSERT_EQ(vdA, sr1);

    vertex_descriptor sr2 = source(edBA, g);
    ASSERT_EQ(vdB, sr2);
    ASSERT_TRUE(sr2 != vdC);}


TYPED_TEST(TestGraph, test_source2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);
    
    edge_descriptor edFD = add_edge(vdF, vdD, g).first;
    edge_descriptor edBC = add_edge(vdB, vdC, g).first;
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edFF = add_edge(vdF, vdF, g).first;

    vertex_descriptor sr1 = source(edFD, g);
    ASSERT_EQ(vdF, sr1);

    vertex_descriptor sr2 = source(edBC, g);
    ASSERT_EQ(vdB, sr2);
    ASSERT_FALSE(sr2 == vdC);

    vertex_descriptor sr3 = source(edAB, g);
    ASSERT_EQ(vdA,sr3);
    vertex_descriptor sr4 = source(edFF, g);
    ASSERT_EQ(vdF,sr4);}

TYPED_TEST(TestGraph, test_target1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edBA = add_edge(vdB, vdA, g).first;


    vertex_descriptor ta1 = target(edAB, g);
    ASSERT_EQ(vdB, ta1);

    vertex_descriptor ta2 = target(edBA, g);
    ASSERT_EQ(vdA, ta2);
    ASSERT_TRUE(ta2 != vdC);}


TYPED_TEST(TestGraph, test_target2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);
    
    edge_descriptor edFD = add_edge(vdF, vdD, g).first;
    edge_descriptor edBC = add_edge(vdB, vdC, g).first;
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edFF = add_edge(vdF, vdF, g).first;

    vertex_descriptor ta1 = target(edFD, g);
    ASSERT_EQ(vdD, ta1);

    vertex_descriptor ta2 = target(edBC, g);
    ASSERT_EQ(vdC, ta2);
    ASSERT_FALSE(ta2 == vdB);

    vertex_descriptor ta3 = target(edAB, g);
    ASSERT_EQ(vdB,ta3);
    vertex_descriptor ta4 = target(edFF, g);
    ASSERT_EQ(vdF,ta4);}


TYPED_TEST(TestGraph, test_vertex1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    

    vertex_descriptor vd1 = vertex(0, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = vertex(1, g);
    ASSERT_EQ(vdB, vd2);

    vertex_descriptor vd3 = vertex(2, g);
    ASSERT_EQ(vdC, vd3);}


TYPED_TEST(TestGraph, test_vertex2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);

    vertex_descriptor vd1 = vertex(5, g);
    ASSERT_FALSE(vdE == vd1);
    vertex_descriptor vd2 = vertex(4, g);
    ASSERT_FALSE(vdD == vd2);
    vertex_descriptor vd3 = vertex(3, g);
    ASSERT_FALSE(vdC == vd3);
    vertex_descriptor vd4 = vertex(2, g);
    ASSERT_FALSE(vdB == vd4);
    vertex_descriptor vd5 = vertex(1, g);
    ASSERT_FALSE(vdA == vd5);
    vertex_descriptor vd6 = vertex(0, g);
    ASSERT_FALSE(vdF == vd6);}

TYPED_TEST(TestGraph, test_vertex3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    graph_type g;
    
    vertex_descriptor vd1 = vertex(3, g);
    ASSERT_EQ(3, vd1);

    vertex_descriptor vd2 = vertex(5, g);
    ASSERT_EQ(5, vd2);
    add_vertex(g);
    add_vertex(g);
    ASSERT_EQ(2, num_vertices(g));}


TYPED_TEST(TestGraph, test_vertices1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    typedef typename TestFixture::vertex_iterator    vertex_iterator;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);

    pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                           b = p.first;
    vertex_iterator                           e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;

    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;

    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdD, vd);}
    ++b;
        ASSERT_EQ(e, b);}

TYPED_TEST(TestGraph, test_vertices2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;


    graph_type g;


    pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                           b = p.first;
    vertex_iterator                           e = p.second;
    ASSERT_EQ(e, b);}

TYPED_TEST(TestGraph, test_vertices3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    typedef typename TestFixture::vertex_iterator    vertex_iterator;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);

    pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                           b = p.first;
    vertex_iterator                           e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;

    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;

    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdD, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor ve = *b;
        ASSERT_EQ(vdE, ve);}
    ++b;
    if (b != e) {
        vertex_descriptor vf = *b;
        ASSERT_EQ(vdF, vf);}
    ++b;
        ASSERT_EQ(e, b);}