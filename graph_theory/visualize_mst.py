import json
import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

# Load the MST edges from the JSON file
with open('mst_edges.json', 'r') as file:
    data = json.load(file)

# Extract the MST edges
mst_edges = [(edge['u'], edge['v']) for edge in data['edges']]

# Load the background image (optional)
img = mpimg.imread('./nitk_map.jpg')
height, width, _ = img.shape

# Define the positions of the nodes (adjust based on your map)
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

# Create a graph with all nodes and edges
G = nx.Graph()
G.add_edges_from(mst_edges)

# Create a Matplotlib figure
fig, ax = plt.subplots()

# Display the background image
ax.imshow(img, extent=[0, width, 0, height])

# Draw the graph with all nodes
nx.draw_networkx_nodes(G, pos, node_color='lightgreen', node_size=300, ax=ax)
nx.draw_networkx_labels(G, pos, font_size=10, ax=ax)

# Highlight MST edges
nx.draw_networkx_edges(G, pos, edgelist=mst_edges, edge_color='white', width=2, ax=ax)

# Display the plot
plt.title("Minimum Spanning Tree Visualization")
plt.show()
