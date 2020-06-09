uniform mat4 u0m_ObjToTex;

uniform vec4 u0v_DeltaPosA;
uniform vec4 u0v_DeltaPosB;
uniform vec4 u0v_DeltaPosC;

uniform vec4 u0v_VoxelSizeO;

varying vec3 v_T0;

varying vec3 v_DeltaPosA;
varying vec3 v_DeltaPosB;
varying vec3 v_DeltaPosC;

varying vec3 v_DeltaPosAT;
varying vec3 v_DeltaPosBT;
varying vec3 v_DeltaPosCT;


void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    v_T0 = (u0m_ObjToTex * gl_Vertex).xyz;

    

    // normal lookup dist is this fraction of min voxel width
    float dist   = u0v_VoxelSizeO.w * 0.8; 

    // move the center for normal lookup a bit towards the positive side of 
    // the plane to make sure that all four planar samples are taken
    // inside the positive side
    vec4  center = gl_Vertex - 0.1 * (u0v_DeltaPosA * dist);
    
    vec3 T0 = (u0m_ObjToTex * center).xyz;

    v_T0 = T0;

    v_DeltaPosAT = (u0m_ObjToTex * (center + u0v_DeltaPosA * dist)).xyz - T0;
    v_DeltaPosBT = (u0m_ObjToTex * (center + u0v_DeltaPosB * dist)).xyz - T0;
    v_DeltaPosCT = (u0m_ObjToTex * (center + u0v_DeltaPosC * dist)).xyz - T0;

    v_DeltaPosA = u0v_DeltaPosA.xyz;
    v_DeltaPosB = u0v_DeltaPosB.xyz;
    v_DeltaPosC = u0v_DeltaPosC.xyz;
}
