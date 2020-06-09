// volume SVRT
uniform mat4    u0m_ObjToTex;
uniform vec4    u0v_DeltaPos;

//varying vec3    v_TexCoordNextSample;
varying vec3    v_T00;
varying vec3    v_T01;
varying vec3    v_T02;
varying vec3    v_T03;
varying vec3    v_T04;
varying vec3    v_T05;
varying vec3    v_T06;


// volume VRT
uniform mat4    u1m_ObjToTex;

varying vec3    v_T10;


void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    
    v_T10       = (u1m_ObjToTex * gl_Vertex).xyz;
    v_T00       = (u0m_ObjToTex * gl_Vertex).xyz;
    
    v_T01 = v_T00 + vec3( u0v_DeltaPos.x, 0.0, 0.0 );
    v_T02 = v_T00 + vec3( 0.0, u0v_DeltaPos.y, 0.0 );
    v_T03 = v_T00 + vec3( 0.0, 0.0, u0v_DeltaPos.z );

    v_T04 = v_T00 - vec3( u0v_DeltaPos.x, 0.0, 0.0 );
    v_T05 = v_T00 - vec3( 0.0, u0v_DeltaPos.y, 0.0 );
    v_T06 = v_T00 - vec3( 0.0, 0.0, u0v_DeltaPos.z );
    
    // Tex Coords 2nd sample
//    v_TexCoordNextSample = v_T00 + gl_Normal; 
}