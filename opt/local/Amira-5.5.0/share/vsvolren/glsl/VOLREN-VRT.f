uniform sampler3D   u0s_RGBA;
uniform sampler3D   u0s_Density;
uniform sampler1D   u0s_Lookup1D;
uniform vec4        u0v_LutScaleOff;
uniform vec4        u0v_AlphaCorrection;

varying vec3        v0v_TexCoordNextSample;
uniform sampler2D   u0s_Jitter; // the 2d-jitter texture
uniform vec4        u0v_MinClipTexCoord;
uniform vec4        u0v_MaxClipTexCoord;


void main()
{
    float data;
    vec4  color;
    
#ifdef M_JITTER

    vec3  T0_o; // offsetted sample texture coordinate
    
    float t      = texture2D( u0s_Jitter, gl_FragCoord.xy / 64.0 ).x;
    vec3  offset = (v0v_TexCoordNextSample - gl_TexCoord[0].xyz) * t;
    T0_o         = gl_TexCoord[0].xyz + offset;
    
    #ifdef M_RGBA_0
        color = texture3D( u0s_RGBA, T0_o );
        color.a = ( 1.0 - pow( 1.0-color.a, u0v_AlphaCorrection.x ) ) * u0v_AlphaCorrection.y;
    #else
        data  = texture3D( u0s_Density, T0_o ).a;
    #endif
    
#else

    #ifdef M_RGBA_0
        color = texture3D( u0s_RGBA, gl_TexCoord[0].xyz );
        color.a = ( 1.0 - pow( 1.0-color.a, u0v_AlphaCorrection.x ) ) * u0v_AlphaCorrection.y;
    #else
        data  = texture3D( u0s_Density, gl_TexCoord[0].xyz ).a;
    #endif
    
#endif
    
    #ifndef M_RGBA_0
        color = texture1D( u0s_Lookup1D, (data-u0v_LutScaleOff.y) * u0v_LutScaleOff.x );
    #endif

#ifdef M_JITTER
    
    color.a *= float ( all( lessThanEqual( T0_o, u0v_MaxClipTexCoord.xyz ) ) && all( greaterThanEqual( T0_o, u0v_MinClipTexCoord.xyz ) ) );
    
#endif

    gl_FragColor = color;
}