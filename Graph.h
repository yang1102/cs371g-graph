// --------------------------
//  projects/c++/graph/Graph.h
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------

#ifndef Graph_h
#define Graph_h

// --------
// includes
// --------

#include <cassert> // assert
#include <cstddef> // size_t
#include <utility> // make_pair, pair
#include <vector>  // vector

// -----
// Graph
// -----

class Graph {
    public:
        // --------
        // typedefs
        // --------

        typedef int vertex_descriptor;  // fix!
        typedef std::pair<vertex_descriptor,vertex_descriptor> edge_descriptor;    // fix!

        typedef std::vector<vertex_descriptor>::const_iterator vertex_iterator;    // fix!
        typedef std::vector<edge_descriptor>::const_iterator  edge_iterator;      // fix!
        typedef std::vector<vertex_descriptor>::const_iterator adjacency_iterator; // fix!

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

    public:
        // --------
        // add_edge
        // --------

        /**
         * <your documentation>
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor a, vertex_descriptor b, Graph& x) {
            // <your code>
            edge_descriptor ed = std::make_pair(a,b);
            vertices_size_type v_size = num_vertices(x);
            assert(v_size >a && v_size >b );
            bool add = false;

            if(std::find(x.e.begin(), x.e.end(), ed) != x.e.end()){
            	return std::make_pair(ed,add);
            }
            else{
            	x.g[a].push_back(b);
            	x.e.push_back(ed);
            	add = true;
            }


            return std::make_pair(ed, add);
        }

        // ----------
        // add_vertex
        // ----------

        /**
         * <your documentation>
         */
        friend vertex_descriptor add_vertex (Graph& x) {
            // <your code>
            vertex_descriptor v = num_vertices(x);
            std::vector<vertex_descriptor> vs(1);

            vs[0] = v;

            x.g.push_back(vs);

            return v;}

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * <your documentation>
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor a, const Graph& x) {
            // <your code>
           // static adjacency_iterator v  = malloc((x.g[a].size()-1)* sizeof(int));     // dummy data


           // adjacency_iterator e = std::copy(x.g[a].begin()+1,x.g[a].end(),v);

           // adjacency_iterator b = v;
        	adjacency_iterator b = x.g[a].begin()+1;
        	adjacency_iterator e = x.g[a].end();

            // for(int i= 0 ; i < x.g[a].size(); ++ i){
            // 	std::cout<< "test 1 :"<< i << " " << x.g[a][i] << std::endl;
            // 	if(i<(x.g[a].size()-1))
            // 		std::cout<< "test 2 :"<< i << " " << v[i] << std::endl;
            // }


            return std::make_pair(b, e);
        }

        // ----
        // edge
        // ----

        /**
         * <your documentation>
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor a, vertex_descriptor b, const Graph& x) {
            // <your code>
        	edges_size_type num_e = num_edges(x);
        	edge_descriptor ed = std::make_pair(-1,-1);
            bool            contain  = false;

            	for(int i = 0; i < num_e; ++i ){
            		if(std::make_pair(a,b)==x.e[i]){
            			ed = std::make_pair(a,b);
            			contain = true;
            			break;
            		}
            	}

            return std::make_pair(ed, contain);
        }

        // -----
        // edges
        // -----

        /**
         * <your documentation>
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& g) {
            // <your code>
            // edge_descriptor es [num_edges(g)];     // dummy data
            // for(int i = 0 ; i < num_edges(g); ++i ){
            // 	es[i] = i;
            // }

            edge_iterator b = g.e.begin();
            edge_iterator e = g.e.end();

            // edge_iterator e = es + num_edges(g);
            return std::make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
         * <your documentation>
         */
        friend edges_size_type num_edges (const Graph& x) {
            // <your code>
            edges_size_type s = x.e.size(); // fix
            return s;}

        // ------------
        // num_vertices
        // ------------

        /**
         * <your documentation>
         */
        friend vertices_size_type num_vertices (const Graph& x) {
            // <your code>
            vertices_size_type s = x.g.size(); // fix
            return s;}

        // ------
        // source
        // ------

        /**
         * <your documentation>
         */
        // friend vertex_descriptor source (edge_descriptor, const Graph&) {
        //     // <your code>
        //     vertex_descriptor v = 0; // fix
        //     return v;}

        // ------
        // target
        // ------

        /**
         * <your documentation>
         */
        // friend vertex_descriptor target (edge_descriptor, const Graph&) {
        //     // <your code>
        //     vertex_descriptor v = 0; // fix
        //     return v;}

        // ------
        // vertex
        // ------

        /**
         * <your documentation>
         */
        // friend vertex_descriptor vertex (vertices_size_type, const Graph&) {
        //     // <your code>
        //     vertex_descriptor vd = 0; // fix

        //     return vd;}

        // --------
        // vertices
        // --------

        /**
         * <your documentation>
         */
        // friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph&) {
        //     // <your code>
        //     static int a [] = {0, 0};     // dummy data
        //     vertex_iterator b = a;
        //     vertex_iterator e = a + 2;
        //     return std::make_pair(b, e);}

    private:
        // ----
        // data
        // ----

        std::vector< std::vector<vertex_descriptor>> g; // something like this
        std::vector<edge_descriptor> e;

        // -----
        // valid
        // -----

        /**
         * <your documentation>
         */
        bool valid () const {
            // <your code>
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Graph (): g(),e() {
            // <your code>

            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

#endif // Graph_h
