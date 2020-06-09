uniform sampler2D u0s_Depth;

void main()
{
    float depth = texture2D( u0s_Depth, gl_TexCoord[0].xy ).x;
    gl_FragDepth = depth;
}
