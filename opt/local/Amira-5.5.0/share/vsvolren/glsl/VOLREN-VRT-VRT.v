uniform mat4    u0m_ObjToTex;
uniform mat4    u1m_ObjToTex;

varying vec3    v_T0;
varying vec3    v_T1;


void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    v_T0        = (u0m_ObjToTex * gl_Vertex).xyz;
    v_T1        = (u1m_ObjToTex * gl_Vertex).xyz;
}