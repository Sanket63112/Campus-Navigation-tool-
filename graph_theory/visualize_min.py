import json
import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

# Load JSON data from the file
with open('path_data.json', 'r') as file:
    data = json.load(file)

# Extract paths and min-cut edges from the JSON data
all_paths = data['paths']
mincut_edges = [tuple(edge) for edge in data['mincut_edges']]

# Load background image
img = mpimg.imread('./nitk_map.jpg')
height, width, _ = img.shape

# Define fixed node positions based on given coordinates
pos = {
    0: (36, 402), 1: (79, 402), 2: (79, 312), 3: (79, 453), 4: (79, 244), 5: (80, 213),
    6: (78.2, 131.6), 7: (157, 213), 8: (157, 306), 9: (205, 306), 10: (319, 304),
    11: (291, 354), 12: (247, 358), 13: (235.5, 393), 14: (219, 393.9), 15: (217.5, 460),
    16: (163.4, 393.9), 17: (276, 213), 18: (250, 186), 19: (301, 188.2), 20: (301, 133),
    21: (250, 138), 22: (365, 300), 23: (347, 184), 24: (373, 184), 25: (373, 225),
    26: (373, 273), 27: (326, 275), 28: (326, 241), 29: (280, 240), 30: (415, 274),
    31: (395, 302), 32: (438, 314), 33: (438, 391), 34: (438, 273), 35: (411, 207),
    36: (355, 391), 37: (38.4, 215), 38: (38.4, 71), 39: (78.2, 108), 40: (191, 108),
    41: (243, 108), 42: (305, 111), 43: (378, 111), 44: (430, 113), 45: (436, 196),
    46: (500, 196), 47: (528, 223), 48: (461, 394), 49: (461, 443), 50: (456, 491),
    51: (430, 512), 52: (528, 393), 53: (563, 369), 54: (574, 307), 55: (581, 248),
    56: (595, 192), 57: (590, 211), 58: (202, 212)
}

# Create a main graph and add all edges (assuming a connected graph)
edges = [
  (0, 1), (1, 2), (1, 3), (2, 4), (1, 16), (14, 16), (14, 15), (14, 13), (12, 13), (11, 12), (11, 10),
     (10, 9), (9, 8), (8, 7), (8, 7), (4, 5), (5, 7), (5, 6),
     (17, 19), (18, 17), (19, 20), (21, 18), (22, 10), (22, 31), (23, 19), (30, 34), (25, 24),
     (26, 25),
     (27, 26), (28, 27), (29, 28), (30, 26), (31, 30), (32, 31), (33, 32), (34, 32), (30, 35), (36, 33), (37, 38),
     (40, 39), (13, 36),
     (41, 40), (42, 41), (43, 42), (44, 43), (45, 44), (45, 34), (46, 45), (47, 46), (25, 45), (48, 33), (49, 48),
     (50, 49), (50, 51), (52, 48), (53, 52), (54, 53), (54, 55),
     (56, 57), (57, 56), (57, 55), (57, 46), (58, 17), (58, 18), (58, 7), (6, 39),(5,37),(23,24)
]

# Create the main graph and add nodes/edges
G = nx.Graph()
G.add_edges_from(edges)

# Create subgraphs for all paths and min-cut edges
path_graph = nx.Graph()
for path in all_paths:
    for i in range(len(path) - 1):
        path_graph.add_edge(path[i], path[i + 1])

mincut_graph = nx.Graph()
mincut_graph.add_edges_from(mincut_edges)

# Create Matplotlib figure
fig, ax = plt.subplots(figsize=(14, 10))
ax.imshow(img, extent=[0, width, 0, height])

# Draw all nodes in one color
nx.draw(G, pos, with_labels=True, node_color='lightblue', node_size=300, edge_color='gray', width=2, font_size=8, ax=ax)

# Draw paths in a different color
nx.draw(path_graph, pos, with_labels=False, node_color='lightyellow', node_size=300, edge_color='lightyellow', width=3, ax=ax)

# Draw min-cut edges in a third color
nx.draw(mincut_graph, pos, with_labels=False, node_color='yellow', node_size=300, edge_color='red', width=3, ax=ax)

# Display the graph
plt.title('Graph Visualization with Paths and Min-Cut Edges')
plt.show()
