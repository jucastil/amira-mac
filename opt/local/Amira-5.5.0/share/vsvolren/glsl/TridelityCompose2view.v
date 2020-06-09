uniform vec4 u0v_Break; // Display size

void main()
{
    gl_Position      = gl_Vertex;
    gl_TexCoord[1].x = 0.5 * (gl_Vertex.x + 1.0);
    gl_TexCoord[1].y = 0.5 * (gl_Vertex.y + 1.0);
    gl_TexCoord[0].x = gl_TexCoord[1].x * u0v_Break.x / 2.0;
    gl_TexCoord[0].y = gl_TexCoord[1].y * u0v_Break.y / 6.0;
}
