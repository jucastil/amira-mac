uniform mat4 u0m_ObjToTex;
uniform vec4 u0v_DeltaPosX;
uniform vec4 u0v_DeltaPosY;
uniform vec4 u0v_DeltaPosZ;
uniform vec4 u0v_NoJitter;

uniform vec4 u0v_PlaneDelta;
varying vec3 v0v_TexCoordNextSample;

varying vec3 v_T0;
varying vec3 v_T1;
varying vec3 v_T2;
varying vec3 v_T3;
varying vec3 v_T4;
varying vec3 v_T5;
varying vec3 v_T6;

#ifdef M_RROJECTIONINV_HACK
uniform mat4 u0m_ViewProjInv;
#define MVP_INV u0m_ViewProjInv
#else
#define MVP_INV gl_ModelViewProjectionMatrixInverse
#endif

void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    v_T0 = (u0m_ObjToTex * gl_Vertex).xyz;
  
    v_T1 = v_T0 + u0v_DeltaPosX.xyz;
    v_T2 = v_T0 + u0v_DeltaPosY.xyz;
    v_T3 = v_T0 + u0v_DeltaPosZ.xyz;

    v_T4 = v_T0 - u0v_DeltaPosX.xyz;
    v_T5 = v_T0 - u0v_DeltaPosY.xyz;
    v_T6 = v_T0 - u0v_DeltaPosZ.xyz;


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



/*
    vec3 camPosO = ( gl_ModelViewMatrixInverse * vec4( 0.0, 0.0, 0.0, 1.0 ) ).xyz;
    vec3 camDirO = normalize( gl_Vertex.xyz - camPosO );

    float h = dot( u0v_PlaneDelta, u0v_PlaneDelta ) / dot( camDirO, u0v_PlaneDelta );
    
    vec4 posNextO = vec4( camDirO * h + gl_Vertex.xyz, 1.0 );
*/
    if ( u0v_NoJitter.x != 0.0  )
        posNextO = gl_Vertex;


    ////////////////////////////////////////
    // compute texture coordinate of the next sample
    ////////////////////////////////////////
    
    v0v_TexCoordNextSample = ( u0m_ObjToTex * posNextO ).xyz;
    
    
#endif  
}
