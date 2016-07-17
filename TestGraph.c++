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
