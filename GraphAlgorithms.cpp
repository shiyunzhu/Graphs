/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2018
 * @copyright This code is in the public domain.
 *
 * @brief The MST and Shortest Path algorithms
 * (implementation).
 *
 */
#include "GraphAlgorithms.hpp"

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to GraphAlgorithms.hpp if you write a helper
 * function!
 *
 */

/**
 * TODO: Implement Prim's Algorithm to build the MST.
 *
 * @brief Builds the MST of the given graph with Prim's algorithm
 *
 * @param g 	Graph object containing vector of nodes and edges
 * 				Definition for struct Graph in structs.hpp
 * @param app	Graphics application class
 * 				Class definition in GraphApp.hpp
 * 				You should not need to use this class other than passing app
 * 				as a parameter to drawEdge
 *
 * @attention 	Some hints for implementation and how to interact with our code
 * 				onMST and notOnMST are two vectors defined in
 *				GraphAlgorithms.hpp
 * 				that you can use to store which nodes are both in/not in the
 * 				MST. These are cleared at the start of the MST computation for 
 * 				you. To access the nodes that a specific node connects to
 *				you, you can use the vector<Node *> edges which is part
 *				of the Node struct in structs.hpp
 * 				You can compare two nodes to see if they are the same by
 * 				comparing the id attribute of a Node.
 *				You can calculate distance from one node to another by calling
 * 				the double distance(Node a) function of the Node struct.
 * 				Whenever you decide to add an edge between two nodes
 *				to the MST, you can use the provided drawEdge function
 *				in GraphAlgorithms.cpp
 *
 * You can assume that the graph is completely connected. Also, we only use
 * existing edges for the MST.
 *
 * Add your outline here

Prim(Graph g, GraphApp *app) {

for (all nodes in g) {
    put in notOnMST
}

Node *c = first node in graph
add node to onMST
remove node from notOnMST

while (notOnMST.size() != 0) {
    Node *n
    Node *h
    low = big number
	for (all nodes in onMST) {
		c = current node in onMST
        for (all edges in c) {
            tempN = current edge
            if (distance(tempN, c) < low) {
                for (all nodes in onMST) {
                    if (current node in onMST == tempN) alreadyIn = true
                }
                if (!alreadyIn) {
                    n = tempN
                    h = c
                    low = distance(tempN, c)
                }
            }
        }
	}
    drawEdge(n,h,g.edges,true)
    add n to onMST
    remove n from notOnMST
}
 *
 *
 */
void buildMSTPrim(Graph g, GraphApp *app) {
    onMST.erase(onMST.begin(), onMST.end());
    notOnMST.erase(notOnMST.begin(), notOnMST.end());

    // Write your code here
    
    for (unsigned int i = 0; i < g.nodes.size(); i++) {
        notOnMST.push_back(g.nodes[i]);
    }
    
    // First node added to the tree
    Node * c = g.nodes[0];
    onMST.push_back(c);
	notOnMST.erase(notOnMST.begin(), notOnMST.begin() + 1);

    // While the MST doesn't include all of the nodes
    while (notOnMST.size() > 0) {
		Node *n;
		Node *h;
		double low = 99999999;

        // for all nodes in onMST find all possible other nodes to connect with
        for (unsigned int i = 0; i < onMST.size(); i++) {
            c = onMST[i];
            for (unsigned int j = 0; j < c->edges.size(); j++) {
                Node * tempN = c->edges[j];
                bool alreadyin = false;
                if (c->distance(*tempN) < low) {
                    for (unsigned int k = 0; k < onMST.size(); k++) {
                       if (onMST[k]->id == tempN->id) {
                            alreadyin = true;
                        }
         			}
                	if (!alreadyin) {
                    	n = tempN;
						h = c;
                    	low = c->distance(*tempN);
                	}
				}	
            }
        }
        onMST.push_back(n);
		for(int j = 0; (unsigned) j < notOnMST.size(); j++)
			if(notOnMST[j]->id == n->id){
				notOnMST.erase(notOnMST.begin() + j, notOnMST.begin() + j + 1);
				break;
			}
        drawEdge(n, h, g.edges, app, true);
    }

}

/**
 * TODO: Implement Kruskal's Algorithm to build the MST.
 *
 * @brief Builds the MST of the given graph with Kruskal's algorithm
 *
 * @param g 	Graph object containing vector of nodes and edges
 * 				Definition for struct Graph in structs.hpp
 * @param app	Graphics application class
 * 				Class definition in GraphApp.hpp
 * 				You should not need to use this class other than
 *passing app
 * 				as a parameter to drawEdge
 *
 * @attention 	Some hints for implementation and how to interact with our code
 * 				You'll want to use a priority queue to determine which edges
 * 				to add first. We've created the priority queue for you
 * 				along with the compare function it uses. All you need to do
 * 				is call edge_queue.top(), edge_queue.pop(), edge_queue.push()
 * 				The data type that this priority queue stores, KruskalEdge 
 *              is defined in GraphAlgorithms.hpp and is an edge between
 *              any two trees. Each Node has a kruskal_edges attribute to store
 *              all the nodes it connects to in the MST. Make sure to use this
 *				to be able to join trees later!
 * 				To know which tree a node is in, use the which_tree attribute.
 * 				You can still use the edges, distance, and id
 *				attributes of a Node.
 * 				When connecting trees, you can call the
 *				kruskalFloodFill function
 * 				defined in structs.hpp on a node to convert it and its
 * 				MST connected nodes to a different tree number recursively.
 *				As in Prim's algorith, call drawEdge to add a connection between
 * 				two nodes to the MST
 *
 * You can assume that the graph is completely connected. Also, we only use
 * existing edges for the MST.
 *
 * Add your outline here
 *
 *
 */
void buildMSTKruskal(Graph g, GraphApp *app) {
    auto compare_func = [](KruskalEdge *a, KruskalEdge *b) {
        return (a->weight > b->weight);
    };
    std::priority_queue<KruskalEdge *, std::vector<KruskalEdge *>,
                        decltype(compare_func)>
        edge_queue(compare_func);

    // Write code here
}

/**
 * TODO: Implement Djikstra's shortest path algorithm.
 *
 * @brief Find the shortest path between start and end nodes with Djikstra's
 * 		  shortest path algorithm
 *
 * @param start	Index of start node of path to find
 * 				Can access the Node * element by using
 *				g.nodes[start]
 * @param end	Index of end node of path to find
 * 				Can access the Node * element by using g.nodes[end]
 * @param g 	Graph object containing vector of nodes and edges
 * 				Definition for struct Graph in structs.hpp
 * @param app	Graphics application class
 * 				Class definition in GraphApp.hpp
 * 				You should not need to use this class other than passing app
 * 				as a parameter to drawEdge
 *
 * @attention 	Some hints for implementation and how to interact with our code
 * 				You can use the distance_to_start attribute of the Node struct
 * 				in structs.hpp to keep track of what the distance from each
 * 				Node to the start node during computation
 * 				You can use the previous attribute of the Node struct
 *				in structs.hpp to keep track of the path you are taking to
 *				later backtrack.
 *				To access the nodes that a specific node connects to you, you
 * 				can use the vector<Node *> edges which is part of the Node struct
 * 				in structs.hpp
 *				Whenever you decide to add an edge between two nodes
 *				to the MST, you can use the provided drawEdge function in
 *				GraphAlgorithms.cpp
 *
 * findShortestPath(start, end, graph g, app) {
 *     Q.erase(Q.begin(),Q.end())
 *     source = g[start]
 *     goal = g[end]
 *     source.distance = 0
 *     source.previous = nothing
 *     
 *     
 *     for (all the nodes in g) {
 *         if (node is not source) {
 *             node.distance = INFINITY
 *             node.previous = nothing
 *         }
 *         add node to vector Q //not yet visited nodes
 *     }
 *     
 *     node * u
 *
 *     while(u != goal) {
 *         low = Q[0].distance
 *         u = Q[0]
 *         ind = 0
 *         for (all nodes in Q) {
 *             if (node.distance < low) {
 *                 low = node.distance
 *                 u = node
 *                 ind = i
 *             }
 *         }
 *         remove u from Q
 *         
 *         for (all nodes in edges of U) {
 *             tempD = u.distance + distance(u,node)
 *             if (tempD < node.distance) {
 *                 node.distance = tempD
 *                 node.previous = u
 *             }
 *         }
 *      }
 *
 *      previous = u.previous
 *      while (goal != source) {
 *           drawEdge(previous, u, g.edges, False)
 *           u = previous
 *           previous = u.previous
 *      }
 *      drawEdge(previous, u, g.edges, False)
 * }               
 *
 *
 */
void findShortestPath(int start, int end, Graph g, GraphApp *app) {
    // erase Q
    Q.erase(Q.begin(), Q.end());
    

    // set source and goal
    Node * source = g.nodes[start];
    Node * goal = g.nodes[end];
    source->distance_to_start = 0;
    source->previous = nullptr;

    // initialize Q
    for (unsigned int i = 0; i < g.nodes.size(); i++) {
        if (g.nodes[i]->id != source->id) {
            g.nodes[i]->distance_to_start = 999999;
            g.nodes[i]->previous = nullptr;
        }
        Q.push_back(g.nodes[i]);
    }
    
    // algorithm
    Node * u = nullptr;
    
    while(u != goal) {
        double low = Q[0]->distance_to_start;
        u = Q[0];
        int ind = 0;
        
        // find the closest node in Q
        for (unsigned int i = 0; i < Q.size(); i++) {
            if (Q[i]->distance_to_start < low) {
                low = Q[i]->distance_to_start;
                u = Q[i];
                ind = i;
            }
        }
        Q.erase(Q.begin() + ind, Q.begin() + 1 + ind);
        
        // check and update neighbouring nodes' path lengths
        for (unsigned int i = 0; i < u->edges.size(); i++) {
            double tempD = u->distance_to_start + u->distance(*(u->edges[i]));   
            if (tempD < u->edges[i]->distance_to_start) {
                u->edges[i]->distance_to_start = tempD;
                u->edges[i]->previous = u;
            }
        }
    }

    // trace back path from goal
    Node * previous = u->previous;
    while(u->id != source->id) {
        drawEdge(previous, u, g.edges, app, false);
        u = previous;
        previous = u->previous;
    }
    drawEdge(previous, u, g.edges, app, false);   
    
    
}

/**
 * @brief Adds an edge to either the MST or the shortest path based on the
 * 			nodes to connect given. This is done by iterating through the edges
 * 			to find the correct edge given the nodes.
 *
 * @param pt1	One side of edge to draw
 * @param pt2	Other side of edge to draw
 * @param edges	Vector of edges in the graph
 * @param app	Graphics application class
 * @param mst	True if we are adding edge to MST, False if we are adding edge
 * 				to shortest path
 **/

void drawEdge(Node *pt1, Node *pt2, vector<Edge *> edges, GraphApp *app,
              bool mst) {
    for (unsigned int i = 0; i < edges.size(); i++) {
        if ((edges[i]->a == pt1 && edges[i]->b == pt2) ||
            (edges[i]->a == pt2 && edges[i]->b == pt1)) {
            if (mst)
                app->add_to_mst(edges[i]);
            else
                app->add_to_path(edges[i]);
            break;
        }
    }
    return;
}
