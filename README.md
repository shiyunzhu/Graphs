Caltech CS2 Assignment 5: Graphs

See [assignment5.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/graphs/blob/master/assignment5.html)

Answers to Part 0 Debugging:

There is nothing wrong with the depth first search algorithm in the snippet of code. The code uses recursion to go down the edges to search for a value. If the value is not found at the end to the line of edges, it goes back a node and searches the other edges at that node. 

However, in order to implement test code, I added a constructor and function in the class to add to the edges vector in order to create nodes and test dfs.
