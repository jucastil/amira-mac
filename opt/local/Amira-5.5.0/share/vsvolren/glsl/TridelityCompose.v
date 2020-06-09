void main()
{
    gl_Position      = gl_Vertex;
    gl_TexCoord[0].x = 0.5 * (gl_Vertex.x + 1.0);
    gl_TexCoord[0].y = 0.5 * (gl_Vertex.y + 1.0);
}
