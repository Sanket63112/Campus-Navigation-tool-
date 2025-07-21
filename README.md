
# 🧭 Campus Navigation Tool

A Dijkstra-based pathfinding tool designed to compute and visualize the shortest path between two nodes in a **campus layout**. This project is implemented in C++ using STL containers such as `unordered_map`, `list`, `set`, and `vector`.

## 🚀 Features

- Calculates the shortest path between two points using **Dijkstra’s algorithm**
- Tracks and prints the **distance from source to all nodes**
- Outputs the **parent array** used for path reconstruction
- Reconstructs and prints the **actual path** from source to destination
- Reads **custom graph input** representing a campus map with weighted edges

---

## 🧠 How It Works

- The campus is modeled as a **graph** with nodes and weighted edges.
- The user provides:
  - Number of nodes
  - Number of edges
  - Edge list (`u`, `v`, `weight`)
  - Source and destination nodes
- The graph is stored as an adjacency list.
- Dijkstra’s algorithm is applied to compute shortest distances from the source node.
- A `parent[]` array is maintained to trace the actual path.
- Final results include:
  - Shortest distances from source
  - The shortest path from source to destination

---

## 📄 Sample Input Format

```text
58
64
0 1 43
1 2 90
...
56 57 19
````

* **58**: Number of nodes
* **64**: Number of edges
* **Following lines**: Edges in format `u v weight`

---

## 📥 Input & Output Example

### Input:

```
Source: 0  
Destination: 57
```

### Output:

```
0 to 0 shortest path 0
0 to 1 shortest path 43
...
Shortest path from 0 to 57:
0->1->3->16->14->13->36->33->48->52->53->54->55->57->
```

---

## 🛠️ Technologies & Concepts Used

* **C++ STL**: `unordered_map`, `list`, `set`, `vector`
* **Graphs**: Adjacency list representation
* **Dijkstra’s Algorithm**: For shortest path finding
* **Path Reconstruction**: Using a parent array

---

## 💡 Future Enhancements

* Visualize the graph and path on a campus map using a frontend interface (e.g., HTML + JS or Python + matplotlib)
* Integrate location names or coordinates
* Add GUI using Qt or a web app using React + Flask

---

## 📁 File Structure

```
CampusNavigation.cpp     // Main program logic
README.md                // Project description
```

---

## 📬 Contact

* 📧 Email: [sanket.sakharenitk@gmail.com](mailto:sanket.sakharenitk@gmail.com
* 🌐 GitHub: [Sanket63112](https://github.com/Sanket63112)

---

© 2024 Sanket Sakhare — Dijkstra’s algorithm-based smart campus navigator

