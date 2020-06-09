uniform sampler3D   u0s_RGBA;
uniform sampler3D   u0s_Density;
uniform vec4        u0v_LutScaleOff;
uniform vec4        u0v_AlphaCorrection;

uniform sampler3D   u0s_Label;
uniform sampler1D   u0s_Lookup1D;
uniform sampler2D   u0s_Lookup2D;

varying vec3        v0v_TexCoordNextSample;
uniform sampler2D   u0s_Jitter;
uniform vec4        u0v_MinClipTexCoord;
uniform vec4        u0v_MaxClipTexCoord;


void main()
{
    vec4  color;
    float data;
    float label;
    
#ifdef M_JITTER

    vec3  T0_o; // offsetted sample texture coordinate
    
    float t      = texture2D( u0s_Jitter, gl_FragCoord.xy / 64.0 ).x;
    vec3  offset = (v0v_TexCoordNextSample.xyz - gl_TexCoord[0].xyz) * t;
    T0_o         = gl_TexCoord[0].xyz + offset;
    
    label    = texture3D( u0s_Label, T0_o ).a;
    label    = ( floor( label * 255.0 + 0.1) + 0.5 ) / 256.0;

    #ifdef M_RGBA_0
        color    = texture3D( u0s_RGBA , T0_o );
        color.a  = ( 1.0 - pow( 1.0-color.a, u0v_AlphaCorrection.x ) ) * u0v_AlphaCorrection.y;
        color.a *= float( texture2D( u0s_Lookup2D, vec2(0.8,label) ).a > 0.0 ); // HACK!!!
    #else
        data     = texture3D( u0s_Density  , T0_o ).a;
        color    = texture2D( u0s_Lookup2D, vec2( (data-u0v_LutScaleOff.y) * u0v_LutScaleOff.x, label ) );
    #endif

    color.a *= float ( all( lessThanEqual( T0_o, u0v_MaxClipTexCoord.xyz ) ) && all( greaterThanEqual( T0_o, u0v_MinClipTexCoord.xyz ) ) );

#else

    label    = texture3D( u0s_Label, gl_TexCoord[0].xyz ).a;
    label    = ( floor( label * 255.0 + 0.1) + 0.5 ) / 256.0;
    
    #ifdef M_RGBA_0
        color    = texture3D( u0s_RGBA , gl_TexCoord[0].xyz );
        color.a  = ( 1.0 - pow( 1.0-color.a, u0v_AlphaCorrection.x ) ) * u0v_AlphaCorrection.y;
        color.a *= float( texture2D( u0s_Lookup2D, vec2(0.8,label) ).a > 0.0 ); // HACK!!!
    #else
        data     = texture3D( u0s_Density  , gl_TexCoord[0].xyz ).a;
        color    = texture2D( u0s_Lookup2D, vec2( (data-u0v_LutScaleOff.y) * u0v_LutScaleOff.x, label ) );
    #endif
    
#endif

    gl_FragColor = color; 
}