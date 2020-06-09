!!ARBfp1.0
PARAM c0 = {0, 0, 0, 0};
TEMP R0;
TEX R0.w, fragment.texcoord[0], texture[0], 2D;
MOV R0.x, R0.w;
MOV R0.y, c0.y;
TEX R0, R0, texture[1], 2D;
MUL result.color, R0, fragment.color;
END
