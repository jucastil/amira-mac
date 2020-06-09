!!ARBfp1.0
PARAM c0 = {0, 0, 0, 0};
PARAM offsetUv = program.local[0];
TEMP R0, tcoord, minMaxUv;

#clamp(texcoord, min, min+offsetUv.zw)
SWZ minMaxUv, fragment.texcoord[0], z,w,z,w;
ADD minMaxUv, minMaxUv, offsetUv;
MIN tcoord, minMaxUv.zwzw, fragment.texcoord[0];
MAX tcoord, minMaxUv.xyxy, tcoord;

TEX R0, tcoord, texture[0], 2D;
MUL result.color, R0, fragment.color;
END
