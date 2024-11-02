# Flight Planning for Fumigation

This project aims to plan the flight path of a drone to reach locations with weeds and apply herbicide. It achieves this by using a graph to represent the layout of crops, weeds, and obstacles within the terrain.

### Authors:
- **Franco Nicolas Bottini**
- **Valentin Robledo**

## Development

### Implemented Classes

1. **`Map`**: Generates random maps containing crops, weeds, and obstacles. The generation follows certain rules, such as ensuring square or rectangular patches of weeds. It provides a graphical representation of the problem.

2. **`Drone`**: Draws the drone within the map and manages all movements, including the fumigation phase.

3. **`Filter`**: Identifies weed clusters that are at least 3x3 in size, generating a list containing each cluster. It also provides a list of obstacles.

4. **`Graph`**: Creates a graph where each node represents a cluster of weeds, and edges between nodes represent possible connections between clusters, as long as no obstacles lie in between.

### Hamiltonian Cycle Algorithm

We implemented a heuristic algorithm to find a Hamiltonian Cycle within the graph. The process follows these steps:

1. Starting from the initial node, move to the node with the lowest-weight edge.
2. Mark the edge as visited and repeat the process until all nodes have been visited, ensuring that the final node in the path is connected back to the starting node.
3. This approach yields a Hamiltonian Cycle, though it does not guarantee optimality.

## Graphical Representation

In the graphical representation of the problem:

- Green represents crops.
- Yellow represents weeds.
- Red represents obstacles.
- Green squares indicate fumigated weeds.
- The gray dot represents the drone.
