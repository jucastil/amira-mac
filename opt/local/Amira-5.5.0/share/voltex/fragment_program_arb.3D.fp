!!ARBfp1.0

# Declare temporary variables
TEMP	c1, c2;

# Lookup the volume data in texture unit 0
TEX	c1, fragment.texcoord[0], texture[0], 3D;

# Lookup the colormap in texture unit 1
TEX	c2, c1, texture[1], 1D;

# Set color
MOV	result.color, c2;

END
