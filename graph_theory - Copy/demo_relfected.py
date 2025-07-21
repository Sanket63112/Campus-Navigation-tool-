import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import math


# Function to calculate Euclidean distance between two points
def euclidean_distance(p1, p2):
    return math.sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)


# Load your background image (adjust the path to your image)
img = mpimg.imread('./nitk_map.jpg')

# Get image dimensions (height, width, channels)
height, width, _ = img.shape

# Create a graph
G = nx.Graph()

# Add nodes and edges
G.add_edges_from(
    [(0, 1), (1, 2), (1, 3), (2, 4), (1, 16), (14, 16), (14, 15), (14, 13), (12, 13), (11, 12), (11, 10),
     (10, 9), (9, 8), (8, 7), (8, 7), (4, 5), (5, 7), (5, 6),
     (17, 19), (18, 17), (19, 20), (21, 18), (22, 10), (22, 31), (23, 19), (30, 34), (25, 24),
     (26, 25),
     (27, 26), (28, 27), (29, 28), (30, 26), (31, 30), (32, 31), (33, 32), (34, 32), (30, 35), (36, 33), (37, 38),
     (40, 39), (13, 36),
     (41, 40), (42, 41), (43, 42), (44, 43), (45, 44), (45, 34), (46, 45), (47, 46), (25, 35), (48, 33), (49, 48),
     (50, 49), (50, 51), (52, 48), (53, 52), (54, 53), (54, 55),
     (56, 57), (57, 56), (57, 55), (57, 46), (58, 17), (58, 18), (58, 7), (6, 39),(5,37),(23,24),(35,45)])

# Define fixed positions for nodes based on image coordinates
# Positions in pixel coordinates (x, y) corresponding to image locations
pos = {
    0: (36, 402),  # x, y coordinates on the image
    1: (79, 402),
    2: (79, 312),
    3: (79, 453),
    4: (79, 244),
    5: (80, 213),
    6: (78.2, 131.6),
    7: (157, 213),
    8: (157, 306),
    9: (205, 306),
    10: (319, 304),
    11: (291, 354),
    12: (247, 358),
    13: (235.5, 393),
    14: (219, 393.9),
    15: (217.5, 460),
    16: (163.4, 393.9),
    17: (276, 213),
    18: (250, 186),
    19: (301, 188.2),
    20: (301, 133),
    21: (250, 138),
    22: (365, 300),
    23: (347, 184),
    24: (373, 184),
    25: (373, 225),
    26: (373, 273),
    27: (326, 275),
    28: (326, 241),
    29: (280, 240),
    30: (415, 274),
    31: (395, 302),
    32: (438, 314),
    33: (438, 391),
    34: (438, 273),
    35: (411, 207),
    36: (355, 391),
    37: (38.4, 215),
    38: (38.4, 71),
    39: (78.2, 108),
    40: (191, 108),
    41: (243, 108),
    42: (305, 111),
    43: (378, 111),
    44: (430, 113),
    45: (436, 196),
    46: (500, 196),
    47: (528, 223),
    48: (461, 394),
    49: (461, 443),
    50: (456, 491),
    51: (430, 512),
    52: (528, 393),
    53: (563, 369),
    54: (574, 307),
    55: (581, 248),
    56: (595, 192),
    57: (590, 211),
    58: (202, 212)

}

# Create a Matplotlib figure
fig, ax = plt.subplots()

# Plot the background image with extent matching the image dimensions
ax.imshow(img, extent=[0, width, 0, height])

# Draw the graph with fixed node positions on top of the image
# Nodes and edges will be overlaid according to specified (x, y) positions
nx.draw(G, pos, with_labels=True, node_color='skyblue', node_size=400, edge_color='white', width=2, font_size=10, ax=ax)

# Create a copy of edges with distances as the third element
edges_with_distances = []
for edge in G.edges:
    node1, node2 = edge
    distance = euclidean_distance(pos[node1], pos[node2])
    edges_with_distances.append((node1, node2, int(round(distance, 1))))

# Print the new array
for e in edges_with_distances:
    print(e)

# No need to invert y-axis now since we adjusted y-coordinates to match image's origin
plt.show()
