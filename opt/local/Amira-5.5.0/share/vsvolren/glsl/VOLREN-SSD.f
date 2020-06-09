uniform sampler3D   u0s_Density;

uniform vec4        u0v_Threshold;

uniform vec4        u0v_DeltaPosX;
uniform vec4        u0v_DeltaPosY;
uniform vec4        u0v_DeltaPosZ;

uniform vec4        u0v_MinTexCoord;
uniform vec4        u0v_MaxTexCoord;

uniform vec4        u0v_MinClipTexCoord;
uniform vec4        u0v_MaxClipTexCoord;

varying vec3        v_T0;
varying vec3        v_T1;


void main()
{
    // lookup sample 1
    float   f0      = texture3D( u0s_Density, v_T0 ).a;
        
    // clamp the second sample into the volume bound
    vec3    x1      = clamp( v_T1, u0v_MinClipTexCoord.xyz, u0v_MaxClipTexCoord.xyz );
        
    // threshold
    float   t       = u0v_Threshold.x;
    
    // lookup sample 2
    float   f1      = texture3D( u0s_Density, x1 ).a;
    
    // difference
    float   d       = f1 - f0;

    // u is offset from sample 1 to surface [0..1] or NAN
    float   u       = (t-f0) / d; // u may become a NAN if d is zero

    // discard if no surface detected
    if ( u>-0.025 && u<1.025 ) // if u is NAN, this evaluates to FALSE
    {
        // lookup normal with offset between sample 1 and sample 2
 
        // vec3 tc = x0 + u*(x1-x0);
        vec3  tc = clamp(v_T0 + u*(x1-v_T0), u0v_MinTexCoord.xyz, u0v_MaxTexCoord.xyz);

        vec3  norm;
        vec3  s0;
        vec3  s1;
        
        s0.x   = texture3D( u0s_Density, tc + u0v_DeltaPosX.xyz ).a;
        s0.y   = texture3D( u0s_Density, tc + u0v_DeltaPosY.xyz ).a;
        s0.z   = texture3D( u0s_Density, tc + u0v_DeltaPosZ.xyz ).a;
        
        s1.x   = texture3D( u0s_Density, tc - u0v_DeltaPosX.xyz ).a;
        s1.y   = texture3D( u0s_Density, tc - u0v_DeltaPosY.xyz ).a;
        s1.z   = texture3D( u0s_Density, tc - u0v_DeltaPosZ.xyz ).a;

        norm = s0-s1;        

        // Normalize in post-pass. Possible on float target only.

        gl_FragColor = vec4( norm, 1.0 );
    }
    else
    {
        discard;    
    }
}