uniform sampler3D   u0s_Density;
uniform vec4        u0v_LutScaleOff;
uniform vec4        u0v_DRRScale;

#ifdef M_JITTER

varying vec3        v0v_TexCoordNextSample;
uniform sampler2D   u0s_Jitter; // the 2d-jitter texture
uniform vec4        u0v_MinClipTexCoord;
uniform vec4        u0v_MaxClipTexCoord;

#endif



void main()
{

#ifdef M_JITTER

    float t      = texture2D( u0s_Jitter, gl_FragCoord.xy / 64.0 ).x;
    vec3  offset = (v0v_TexCoordNextSample.xyz - gl_TexCoord[0].xyz) * t;
    vec3  T0_o   = gl_TexCoord[0].xyz + offset;
    
#else

    vec3  T0_o   = gl_TexCoord[0].xyz;

#endif


    float dens   = texture3D( u0s_Density, T0_o ).a;
    float data   = (dens-u0v_LutScaleOff.y) * u0v_LutScaleOff.x * u0v_DRRScale.x;
    data         = (data > 0.0) ? data : 0.0;


#ifdef M_JITTER
    
    data *= float ( all( lessThanEqual( T0_o, u0v_MaxClipTexCoord.xyz ) ) && all( greaterThanEqual( T0_o, u0v_MinClipTexCoord.xyz ) ) );
    
#endif
    
    gl_FragColor = data*vec4(1.0,0.3,3.0,1.0);
}
