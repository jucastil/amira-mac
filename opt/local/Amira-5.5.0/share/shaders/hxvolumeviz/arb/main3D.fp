!!ARBfp1.0
PARAM c0 = {0, 0, 0, 0};
PARAM invSliceDensity = program.local[0];
TEMP R0;
TEX R0.w, fragment.texcoord[0], texture[0], 3D;
MOV R0.x, R0.w;
MOV R0.y, c0.y;
TEX R0, R0, texture[1], 2D;
MUL R0, R0, fragment.color;

#Do opacity correction 1-(1-a)^(InvSliceDencity)
SUB R0.w, 1, R0.w;
#POW instruction doesn't work on negative numbers
MAX R0.w, R0.w, c0.x;
POW R0.w, R0.w, invSliceDensity.x;
SUB R0.w, 1, R0.w;

MOV result.color, R0;
END
