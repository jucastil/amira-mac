!!FP1.0

DECLARE LightPos;
DEFINE spec_color = { 1.0, 1.0, 1.0, 1.0 };

# Lookup the volume data in texture unit 0
TEX R1, f[TEX0], TEX0, 2D;

# Lookup the colormap in texture unit 1
TEX R2, R1, TEX1, 1D;

# Lookup the gradient in texture unit 2
TEX R3, f[TEX0], TEX2, 2D;

# Normalize light vector
#DP3 R4, LightPos, LightPos;
#RSQ R4.w, R4.w;
#MUL R4.xyz, LightPos, R4.w;

# Compute dot product between normal and light vector
DP3 R9, LightPos, R3;

# Diffuse component
MUL R6, R2, R9;

# Specular exponent
POW R7, R9.x, { 1.0 }.x;

# Specular attenuation
MUL R8, spec_color, R7;

# Add diffuse and specular
ADD o[COLR], R8, R6;
# test - only specular
#MOV o[COLR], R8;


# Get alpha from colormap
MOV o[COLR].w, R2.w;

# test
#MAX R3, R3, -R3;
#MOV o[COLR].xyz, R9;
 
END