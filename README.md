# Projects
Projects/implmentations done during Engineering

## A Star Search Algorithm

It is a path search algorithm widely used in AI to navigate robots in completely known terrains. 
It finds the shortest obstacle-free path in a given graph or grid.
It only works on the static map of the environment, i.e., the map should be known apriori. It is not able to dynamically find the shortest obstacle-free path. Some other algorithms can extend the idea of the A* algorithm for dynamic terrain, where it can replan the pathfinding calculations to find the new shortest path.

In the file AStarAlgo.cpp, a simple modular version of the A* algorithm is implemented. There is a predefined 2D grid (which we can change later if we wish) with obstacles shown as value one and an obstacle-free grid represented by value zero. 
Here is the [motion planning pdf](https://www.cs.cmu.edu/~motionplanning/lecture/AppH-astar-dstar_howie.pdf)  which was referred to understand and implement the algorithm, which also shows a step-by-step execution of the algorithm on a simple example (Shown under the D* search algorithm).

## Socket Programming

A folder named Socket programming contains basic socket programming to communicate between server and client. 
The working of the program is similar to any client-server application using sockets. The difference lies in how it uses OOP (Object Oriented Programming) concepts. It exercises the knowledge of OOP like Classes, constructors, Error handling, public-private functions, and their scopes in actual implementation to make it more robust, readable, and maintainable.

Given program has a server that continuously looks for any client connections, If a client is connected to the server, it will read data from the client and sends some additional data back to the client.


