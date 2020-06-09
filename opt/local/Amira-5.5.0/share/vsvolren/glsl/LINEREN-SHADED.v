varying vec3 tangent;
varying vec4 color;

void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    tangent     = gl_NormalMatrix * gl_Normal;
    color       = gl_Color;
}
