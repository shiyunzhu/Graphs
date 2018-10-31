/* debugging example */

/* 
*  There is nothing wrong with the depth first search algorithm below
*  The code uses recursion to go down the edges to search for a value
*  coming back to the previous node after all edges have been searched
*  However, in order to implement test code, I added a constructor and
*  function in the class in order to create nodes and test them
*/

#include <iostream>
#include <vector>


class Node
{
    int value;
    std::vector<Node*> edges;
public:
    // insert constructors, destructors,
    // accessors, and mutators here

    // constructor for the class
    Node(int val) {
        value = val;
    }
    // function to add node to edges vector
    void add(Node* edge);
    bool dfs(int to_find);
};

void Node::add(Node* edge) {
    this->edges.push_back(edge);
}
// true indicates that the value was found, and false indicates that the value was not found.
bool Node::dfs(int to_find)
{
    if(this->value == to_find)
    {
        return true;
    }
    std::vector<Node*>::iterator i;
    for(i = this->edges.begin(); i != this->edges.end(); i++)
    {
        Node * n = *i;
        bool r = n->dfs(to_find);
        if(r)
        {
            return r;
        }
    }
    return false;
}

int main(void)
{
    //Creating the nodes
    Node n = Node(1);
    Node n_1 = Node(2);
    Node n_2 = Node(3);
    Node n_1a = Node(4);
    Node n_2a = Node(4);
    Node n_3 = Node(5);

    //Creating pointers to point to some nodes
    Node * e_1 = &n_1;
    Node * e_2 = &n_2;
    Node * e_1a = &n_1a;
    Node * e_2a = &n_2a;
    Node * e_3 = &n_3;

    //Adding edges (pointers) to some nodes
    n_1.add(e_1a);
    n_2.add(e_2a);
    n.add(e_1);
    n.add(e_2);
    n.add(e_3);

    //Printing out the values and connections between nodes

    std::cout<< "The node n has value 1 and is connected to n_1 and n_2 and n_3" << std::endl;
    std::cout<< "The node n_1 has value 2 and is connected to n_1a and n" << std::endl;
    std::cout<< "The node n_2 has value 3 and is connected to n and n_2a" << std::endl;
    std::cout<< "The node n_1a has value 4 and is connected to n_1" << std::endl;
    std::cout<< "The node n_2a has value 4 and is connected to n_2" << std::endl;
    std::cout<< "The node n_3 has value 5 and is connected to n" << std::endl;

    //Testing out dfs for top node n
    std::cout<< "Checking the values: 2, 1, 11, 3, 4, 5, 6 with n (top node)" << std::endl;
    std::cout<< "This should print out true: " << n.dfs(2) << std::endl;
    std::cout<< "This should print out true: " << n.dfs(1) << std::endl;
    std::cout<< "This should print out false: " << n.dfs(11) << std::endl;
    std::cout<< "This should print out true: " << n.dfs(3) << std::endl;
    std::cout<< "This should print out true: " << n.dfs(4) << std::endl;
    std::cout<< "This should print out true: " << n.dfs(5) << std::endl;
    std::cout<< "This should print out false: " << n.dfs(6) << std::endl;

    //Testing out dfs for sub 1 level n_1
    std::cout<< "Checking the values: 4, 2, 1, 5 with n_1 (sub 1 level)" << std::endl;
    std::cout<< "This should print out true: " << n_1.dfs(4) << std::endl;
    std::cout<< "This should print out true: " << n_1.dfs(2) << std::endl;
    std::cout<< "This should print out false: " << n_1.dfs(1) << std::endl;
    std::cout<< "This should print out false: " << n_1.dfs(5) << std::endl;

    
    
    
    return 0;

}
