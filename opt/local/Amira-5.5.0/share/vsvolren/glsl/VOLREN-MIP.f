uniform sampler3D   u0s_RGBA;
uniform sampler3D   u0s_Density;
uniform vec4        u0v_LutScaleOff;
uniform vec4        u0v_AlphaCorrection;

varying vec3        v0v_TexCoordNextSample;
uniform sampler2D   u0s_Jitter;
uniform vec4        u0v_MinClipTexCoord;
uniform vec4        u0v_MaxClipTexCoord;


void main()
{
    float data;
    float luminance;
    vec4  color;

#ifdef M_JITTER

    vec3  T0_o; // offsetted sample texture coordinate
    
    float t      = texture2D( u0s_Jitter, gl_FragCoord.xy / 64.0 ).x;
    vec3  offset = (v0v_TexCoordNextSample.xyz - gl_TexCoord[0].xyz) * t;
    T0_o         = gl_TexCoord[0].xyz + offset;
    
    #ifdef M_RGBA_0
        color        = texture3D( u0s_RGBA, T0_o );
        color.a     *= u0v_AlphaCorrection.y * float ( all( lessThanEqual( T0_o, u0v_MaxClipTexCoord.xyz ) ) && all( greaterThanEqual( T0_o, u0v_MinClipTexCoord.xyz ) ) );
    #else
        data         = texture3D( u0s_Density, T0_o ).a;
        luminance    = (data-u0v_LutScaleOff.y) * u0v_LutScaleOff.x;
        luminance   *= float ( all( lessThanEqual( T0_o, u0v_MaxClipTexCoord.xyz ) ) && all( greaterThanEqual( T0_o, u0v_MinClipTexCoord.xyz ) ) );
    #endif
        
#else

    #ifdef M_RGBA_0
        color     = texture3D( u0s_RGBA, gl_TexCoord[0].xyz );
        color.a  *= u0v_AlphaCorrection.y;
    #else
        data      = texture3D( u0s_Density, gl_TexCoord[0].xyz ).a;
        luminance = (data-u0v_LutScaleOff.y) * u0v_LutScaleOff.x;
    #endif
        
#endif

#ifdef M_RGBA_0
    color.r *= color.a;
    color.g *= color.a;
    color.b *= color.a;
#endif
    
#ifdef M_INVERSE_MIP    

    #ifdef M_RGBA_0
        gl_FragColor = vec4( 1.0-color.r, 1.0-color.g, 1.0-color.b, color.a );
    #else
        gl_FragColor = vec4( 1.0-luminance, 1.0-luminance, 1.0-luminance, luminance );
    #endif

#else

    #ifdef M_RGBA_0
        gl_FragColor = color;
    #else
        gl_FragColor = vec4(luminance);
    #endif

#endif    
}
