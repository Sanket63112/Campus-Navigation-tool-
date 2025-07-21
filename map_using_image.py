import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

# Load your background image (make sure to adjust the path to your image)
img = mpimg.imread('./nitk_map.jpg')

# Get image dimensions (height, width, channels)
height, width, _ = img.shape
print(height,width)
# Create a graph
G = nx.Graph()

# Add nodes and edges
G.add_edges_from([(0, 1), (1, 2), (2, 3), (2, 4), (0, 3)])

# Define fixed positions for nodes based on image coordinates
# For example, node 0 at (100, 200), node 1 at (400, 500), etc.
pos = {
    0: (36, 119),  # x, y coordinates on the image
    1: (38, 213),
    2: (79, 208),
    3: (79, 119),
    4: (79, 317)
}

# Create a Matplotlib figure
fig, ax = plt.subplots()

# Plot the background image with extent matching the image dimensions
ax.imshow(img, extent=[0, width, 0, height])

# Draw the graph with fixed node positions on top of the image
# Flip the y-axis to match the image's coordinate system (top-down)
nx.draw(G, pos, with_labels=True, node_color='skyblue', node_size=500, edge_color='black', width=2, font_size=10, ax=ax)

# Invert the y-axis to align with the image coordinates
plt.gca().invert_yaxis()

# Show the plot
plt.show()
