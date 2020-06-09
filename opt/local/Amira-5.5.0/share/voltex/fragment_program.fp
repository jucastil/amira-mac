!!FP1.0

# Lookup the volume data in texture unit 0
TEX R1, f[TEX0], TEX0, 2D;

# Lookup the colormap in texture unit 1
TEX R2, R1, TEX1, 1D;

# Set color
MOV o[COLR], R2;
 
END