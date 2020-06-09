// slot 0 VRT
uniform sampler3D   u0s_RGBA;
uniform sampler3D   u0s_Density;
uniform sampler2D   u0s_Lookup2D;
uniform vec4        u0v_LutScaleOff;
uniform vec4        u0v_AlphaCorrection;

varying vec3        v_T0;

// slot 1 VRT
uniform sampler3D   u1s_RGBA;
uniform sampler3D   u1s_Density;
uniform sampler2D   u1s_Lookup2D;
uniform vec4        u1v_LutScaleOff;
uniform vec4        u1v_AlphaCorrection;

uniform sampler3D   u1s_Label;

varying vec3        v_T1;


void main()
{
    float densi0;
    float densi1;
    
    vec4  color0;
    vec4  color1;
    
    gl_FragColor = vec4(0.0);
    
    float label  = texture3D( u1s_Label  , v_T1 ).a;
    label        = ( floor( label * 255.0 + 0.1) + 0.5 ) / 256.0;
    
    
    ////////////////////////////////////////
    // slot 0
    ////////////////////////////////////////
    #ifdef M_RGBA_0
        color0    = texture3D( u0s_RGBA, v_T0 );
        color0.a  = ( 1.0 - pow( 1.0-color0.a, u0v_AlphaCorrection.x ) ) * u0v_AlphaCorrection.y;
        color0.a *= float( texture2D( u0s_Lookup2D, vec2(0.8,label) ).a > 0.0 ); // HACK!!!
    #else
        densi0 = texture3D( u0s_Density, v_T0 ).a;
        color0 = texture2D( u0s_Lookup2D, vec2( (densi0-u0v_LutScaleOff.y) * u0v_LutScaleOff.x, label ) );
    #endif
    
    color0.a *= u0v_LutScaleOff.z;

    ////////////////////////////////////////
    // slot 1
    ////////////////////////////////////////
    #ifndef M_HIDE_LABEL_VOLUME
    
        #ifdef M_RGBA_1
            color1    = texture3D( u1s_RGBA, v_T1 );
            color1.a  = ( 1.0 - pow( 1.0-color1.a, u1v_AlphaCorrection.x ) ) * u1v_AlphaCorrection.y;
            color1.a *= float( texture2D( u1s_Lookup2D, vec2(0.8,label) ).a > 0.0 ); // HACK!!!
        #else
            densi1 = texture3D( u1s_Density, v_T1 ).a;
            color1 = texture2D( u1s_Lookup2D, vec2( (densi1-u1v_LutScaleOff.y) * u1v_LutScaleOff.x, label ) );
        #endif
            
        color1.a *= u1v_LutScaleOff.z;
        
    #endif

    
    #ifndef M_HIDE_LABEL_VOLUME    
        
        // blending
        float a01 = color0.a + color1.a;
        
        if ( a01 > 0.0 )
            gl_FragColor.rgb = (color0.rgb * color0.a + color1.rgb * color1.a) / a01;
            
        gl_FragColor.a   = 1.0 - (1.0-color0.a) * (1.0-color1.a);
    
    #else
    
        gl_FragColor = color0;
        
    #endif
}