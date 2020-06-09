// volume SVRT
uniform mat4    u0m_ObjToTex;

uniform vec4    u0v_DeltaPosA;
uniform vec4    u0v_DeltaPosB;
uniform vec4    u0v_DeltaPosC;

uniform vec4    u0v_VoxelSizeO;


varying vec3    v_T00;
varying vec3    v_T02;
varying vec3    v_T03;
varying vec3    v_T04;
varying vec3    v_T05;
varying vec3    v_T06;


// volume SVRT
uniform mat4    u1m_ObjToTex;

uniform vec4    u1v_DeltaPosA;
uniform vec4    u1v_DeltaPosB;
uniform vec4    u1v_DeltaPosC;

uniform vec4    u1v_VoxelSizeO;


varying vec3    v_T10;



void main()
{
    float dist;
    vec4  center;
    
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    
    v_T00 = (u0m_ObjToTex * gl_Vertex).xyz;
    
    // normal lookup dist is this fraction of min voxel width
    dist = u0v_VoxelSizeO.w * 0.8; 

    // move the center for normal lookup a bit towards the positive side of 
    // the plane to make sure that all four planar samples are taken
    // inside the positive side
    center = gl_Vertex - 0.1 * (u0v_DeltaPosA * dist);
    
    v_T02 = (u0m_ObjToTex * (center + u0v_DeltaPosB * dist)).xyz;
    v_T03 = (u0m_ObjToTex * (center + u0v_DeltaPosC * dist)).xyz;

    v_T04 = (u0m_ObjToTex * (center - u0v_DeltaPosA * dist)).xyz;
    v_T05 = (u0m_ObjToTex * (center - u0v_DeltaPosB * dist)).xyz;
    v_T06 = (u0m_ObjToTex * (center - u0v_DeltaPosC * dist)).xyz;
    
        
    
    
    v_T10 = (u1m_ObjToTex * gl_Vertex).xyz;
}