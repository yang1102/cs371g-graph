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
#include <algorithm>    // std::max


// -----
// Graph
// -----

class Graph {
    public:
        // --------
        // typedefs
        // --------

        typedef int vertex_descriptor;  
        typedef std::pair<vertex_descriptor,vertex_descriptor> edge_descriptor;  

        typedef std::vector<vertex_descriptor>::const_iterator vertex_iterator;  
        typedef std::vector<edge_descriptor>::const_iterator  edge_iterator;    
        typedef std::vector<vertex_descriptor>::const_iterator adjacency_iterator;

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

    public:
        // --------
        // add_edge
        // --------

        /**
         * @param a is a vertex_descriptor
         * @param b is a vertex_descriptor
         * @param x is a Graph passed by reference
         * make an edge between the two vertices given, first is source, second is target
         * @return pair with edge_descriptor and bool
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor a, vertex_descriptor b, Graph& x) {
            edge_descriptor ed = std::make_pair(a,b);

            vertices_size_type v_size = num_vertices(x);
            if((unsigned)a>v_size||(unsigned)b>v_size){
                vertices_size_type new_size = std::max(a,b)+1;
                for(vertices_size_type i=0; i < new_size-v_size; ++i){
                    add_vertex(x);
                }
            }

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
         * @param x is a Graph passed by reference
         * Adds a vertex to the graph 
         * @return the vertex descriptor for the new vertex
         */
        friend vertex_descriptor add_vertex (Graph& x) {

            vertex_descriptor v = num_vertices(x);
            std::vector<vertex_descriptor> vs(1);

            vs[0] = v;
            x.g.push_back(vs);
            x.v.push_back(v);

            return v;}

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * @param a is a vertex_descriptor
         * @param x is a Graph passed by reference
         * @return pair of iterators providing access to the vertices adjacent to vertex a in graph x
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor a, const Graph& x) {

        	adjacency_iterator b = x.g[a].begin()+1;
        	adjacency_iterator e = x.g[a].end();


            return std::make_pair(b, e);
        }

        // ----
        // edge
        // ----

        /**
         * @param a is a vertex_descriptor
         * @param b is a vertex_descriptor
         * @param x is a Graph passed by reference
         * checks  if there is an edge between the a and b
         * @return pair with edge_descriptor and bool indicating if found
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor a, vertex_descriptor b, const Graph& x) {

        	edges_size_type num_e = num_edges(x);
        	edge_descriptor ed = std::make_pair(-1,-1);
            bool            contain  = false;

            	for(edges_size_type i = 0; i < num_e; ++i ){
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
         * @param x is a Graph passed by reference
         * @return pair of iterators providing access to the edges in this graph
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& x) {

            edge_iterator b = x.e.begin();
            edge_iterator e = x.e.end();

            return std::make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
         * @param x is a Graph passed by reference
         * @return number of edges graph x contain
         */
        friend edges_size_type num_edges (const Graph& x) {

            edges_size_type s = x.e.size(); 
            return s;}

        // ------------
        // num_vertices
        // ------------

        /**
         * @param x is a Graph passed by reference
         * @return number of vertices graph x contain
         */
        friend vertices_size_type num_vertices (const Graph& x) {

            vertices_size_type s = x.v.size(); 
            return s;}

        // ------
        // source
        // ------

        /**
         * @param a is a edge_descriptor
         * @param x is a Graph passed by reference
         * @return vertex_descriptor of the start vertex of an edge if the edge does not exist return -1
         */
        friend vertex_descriptor source (edge_descriptor a, const Graph& x) {

            if(std::find(x.e.begin(), x.e.end(), a) != x.e.end())
                return a.first;


            return -1;}

        // ------
        // target
        // ------

        /**
         * @param a is a edge_descriptor
         * @param x is a Graph passed by reference
         * @return vertex_descriptor of the end vertex of an edge if the edge does not exist return -1
         */
        friend vertex_descriptor target (edge_descriptor a, const Graph& x) {

           if(std::find(x.e.begin(), x.e.end(), a) != x.e.end())
                return a.second;

            return -1;}

        // ------
        // vertex
        // ------

        /**
         * @param n is a edge_descriptor
         * @param x is a Graph passed by reference
         * @return vertex_descriptor of the nth vertex of graph x
         */
        friend vertex_descriptor vertex (vertices_size_type n, const Graph& x) {

      
            vertex_descriptor v = n;
            return v;}

        // --------
        // vertices
        // --------

        /**
         * @param x is a Graph passed by reference
         * @return pair of iterators providing access to all the vertices in graph x
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& x) {
            vertex_iterator b = x.v.begin();
            vertex_iterator e = x.v.end();
            return std::make_pair(b, e);
        }

    private:
        // ----
        // data
        // ----

        std::vector< std::vector<vertex_descriptor>> g; // something like this
        std::vector<edge_descriptor> e;
        std::vector<vertex_descriptor> v;

        // -----
        // valid
        // -----

        /**
         * check if all the vector size are valid
         */
        bool valid () const {
             
            return g.size()>=0&&e.size()>=0&&v.size()>=0;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * Default graph constructor
         */
        Graph (): g(),e(),v() {

            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

#endif // Graph_h
