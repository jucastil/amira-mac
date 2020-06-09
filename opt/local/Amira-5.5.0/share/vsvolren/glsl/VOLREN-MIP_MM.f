uniform sampler3D   u0s_RGBA;
uniform sampler3D   u0s_Density;
uniform vec4        u0v_LutScaleOff;
uniform vec4        u0v_AlphaCorrection;

uniform sampler3D   u0s_Label;
uniform sampler1D   u0s_Lookup1D;



varying vec3        v0v_TexCoordNextSample;

uniform sampler2D   u0s_Jitter;
uniform vec4        u0v_MinClipTexCoord;
uniform vec4        u0v_MaxClipTexCoord;


void main()
{
    float data;
    float luminance;
    float label;
    float factorClip;
    vec4  color;
        
#ifdef M_JITTER

    vec3  T0_o; // offsetted sample texture coordinate
    
    float t      = texture2D( u0s_Jitter, gl_FragCoord.xy / 64.0 ).x;
    vec3  offset = (v0v_TexCoordNextSample - gl_TexCoord[0].xyz) * t;
    T0_o         = gl_TexCoord[0].xyz + offset;
    
    #ifdef M_RGBA_0
        color     = texture3D( u0s_RGBA, T0_o );
        color.a  *= u0v_AlphaCorrection.y * float ( all( lessThanEqual( T0_o, u0v_MaxClipTexCoord.xyz ) ) && all( greaterThanEqual( T0_o, u0v_MinClipTexCoord.xyz ) ) );
    #else
        data      = texture3D( u0s_Density, T0_o ).a;
        luminance = (data-u0v_LutScaleOff.y) * u0v_LutScaleOff.x;
        luminance*= float ( all( lessThanEqual( T0_o, u0v_MaxClipTexCoord.xyz ) ) && all( greaterThanEqual( T0_o, u0v_MinClipTexCoord.xyz ) ) );
    #endif
    
    label     = texture3D( u0s_Label, T0_o ).a;

#else

    #ifdef M_RGBA_0
        color     = texture3D( u0s_RGBA, gl_TexCoord[0].xyz );
        color.a  *= u0v_AlphaCorrection.y;
    #else
        data      = texture3D( u0s_Density, gl_TexCoord[0].xyz ).a;
        luminance = (data-u0v_LutScaleOff.y) * u0v_LutScaleOff.x;
    #endif

    label     = texture3D( u0s_Label, gl_TexCoord[0].xyz ).a;

#endif 


    label     = ( floor( label * 255.0 + 0.1) + 0.5 ) / 256.0;
    factorClip= texture1D( u0s_Lookup1D, label ).a;
    
#ifdef M_RGBA_0
    color.a *= factorClip;
    color.r *= color.a;
    color.g *= color.a;
    color.b *= color.a;
#else
    luminance *= factorClip;
#endif
        
#ifdef M_INVERSE_MIP    

    #ifdef M_RGBA_0
        gl_FragColor = vec4( 1.0-color.r, 1.0-color.g, 1.0-color.b, color.a );
    #else
        gl_FragColor = vec4( 1.0-luminance, 1.0-luminance, 1.0-luminance, luminance );
    #endif

    #ifdef M_SELECTION_HIGHLIGHT
        gl_FragColor.g = 1.0 - floor( label / 0.5 );
    #endif

#else

    #ifdef M_RGBA_0
        gl_FragColor = color;
    #else
        gl_FragColor = vec4(luminance);
    #endif

    #ifdef M_SELECTION_HIGHLIGHT
        gl_FragColor.g = floor( label / 0.5 );
    #endif

#endif



}
