import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

# Create a graph
G = nx.Graph()

# Add nodes and edges
G.add_edges_from([(0, 1), (1, 2), (2, 3), (3, 4), (0, 4)])

# Define fixed positions for each node (x, y coordinates)
# Example: Node 0 at (0.1, 0.2), Node 1 at (0.4, 0.5), etc.
pos = {
    0: (0.5, 0.2),
    1: (0.4, 0.5),
    2: (0.7, 0.8),
    3: (0.9, 0.4),
    4: (0.3, 0.7)
}

# Load your background image (e.g., a map)
img = mpimg.imread('./nitk_map.jpg')

# Create a Matplotlib figure
fig, ax = plt.subplots()

# Plot the background image
ax.imshow(img, extent=[0, 1, 0, 1], aspect='auto')

# Draw the graph with the fixed node positions on top of the image
nx.draw(G, pos, with_labels=True, node_color='skyblue', node_size=500, edge_color='black', width=2, font_size=10, ax=ax)

# Show the plot
plt.show()
