uniform mat4 u0m_ObjToTex;
uniform vec4 u0v_NoJitter;

uniform vec4 u0v_PlaneDelta;
varying vec3 v0v_TexCoordNextSample;

#ifdef M_RROJECTIONINV_HACK
uniform mat4 u0m_ViewProjInv;
#define MVP_INV u0m_ViewProjInv
#else
#define MVP_INV gl_ModelViewProjectionMatrixInverse
#endif

    
void main()
{
    gl_Position    = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = u0m_ObjToTex * gl_Vertex;
    
#ifdef M_JITTER

    ////////////////////////////////////////
    // compute position of the next sample (in object space)
    ////////////////////////////////////////

    vec4 posCurrP = gl_Position; // .. in projection space
    posCurrP /= posCurrP.w;

    vec4 posNextO = vec4( gl_Vertex.xyz + u0v_PlaneDelta.xyz, 1.0 ); // current position plus plane delta in object space (homogeneous)
    vec4 posNextP = vec4( gl_ModelViewProjectionMatrix * posNextO ); // .. projection space  (homogeneous)
    posNextP /= posNextP.w;
    
    posCurrP.z = posNextP.z;
    
    posNextO = MVP_INV * posCurrP; // position of the next sample in object space (homogeneous)
    posNextO /= posNextO.w; // posNextO is now the position of the next sample

    if ( u0v_NoJitter.x != 0.0  )
        posNextO = gl_Vertex;
        
    ////////////////////////////////////////
    // compute texture coordinate of the next sample
    ////////////////////////////////////////
    
    v0v_TexCoordNextSample = ( u0m_ObjToTex * posNextO ).xyz;
    
#endif
}
