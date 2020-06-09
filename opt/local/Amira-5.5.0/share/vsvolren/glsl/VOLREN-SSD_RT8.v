uniform mat4 u0m_ObjToTex;

uniform vec4 u0v_PlaneDelta;

varying vec3 v_T0;
varying vec3 v_T1;


void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    
    v_T0 = ( u0m_ObjToTex * gl_Vertex ).xyz;
    
    ////////////////////////////////////////
    // compute position of the next sample (in object space)
    ////////////////////////////////////////

    vec4 posCurrP = gl_Position; // .. in projection space
    posCurrP /= posCurrP.w;

    vec4 posNextO = vec4( gl_Vertex.xyz + u0v_PlaneDelta.xyz, 1.0 ); // current position plus plane delta in object space (homogeneous)
    vec4 posNextP = vec4( gl_ModelViewProjectionMatrix * posNextO ); // .. projection space  (homogeneous)
    posNextP /= posNextP.w;
    
    posCurrP.z = posNextP.z;
    
    posNextO = gl_ModelViewProjectionMatrixInverse * posCurrP; // position of the next sample in object space (homogeneous)
    posNextO /= posNextO.w; // posNextO is now the position of the next sample

    ////////////////////////////////////////
    // compute texture coordinate of the next sample
    ////////////////////////////////////////
    
    v_T1 = ( u0m_ObjToTex * posNextO ).xyz;    
}