// slot 0 VRT
uniform sampler3D   u0s_RGBA;
uniform sampler3D   u0s_Density;
uniform sampler1D   u0s_Lookup1D;
uniform vec4        u0v_LutScaleOff;
uniform vec4        u0v_AlphaCorrection;

varying vec3        v_T0;


// slot 1 VRT
uniform sampler3D   u1s_RGBA;
uniform sampler3D   u1s_Density;
uniform sampler1D   u1s_Lookup1D;
uniform vec4        u1v_LutScaleOff;
uniform vec4        u1v_AlphaCorrection;

varying vec3        v_T1;


void main()
{
    float data0;
    float data1;

    vec4  color0;
    vec4  color1;
    gl_FragColor = vec4(0.0);
    
    #ifdef M_RGBA_0
        color0 = texture3D( u0s_RGBA, v_T0 );
        color0.a = ( 1.0 - pow( 1.0-color0.a, u0v_AlphaCorrection.x ) ) * u0v_AlphaCorrection.y;
    #else
        data0  = texture3D( u0s_Density, v_T0 ).a;
        color0 = texture1D( u0s_Lookup1D, (data0-u0v_LutScaleOff.y) * u0v_LutScaleOff.x );
    #endif
            
    #ifdef M_RGBA_1
        color1 = texture3D( u1s_RGBA, v_T1 );
        color1.a = ( 1.0 - pow( 1.0-color1.a, u1v_AlphaCorrection.x ) ) * u1v_AlphaCorrection.y;
    #else
        data1  = texture3D( u1s_Density, v_T1 ).a;
        color1 = texture1D( u1s_Lookup1D, (data1-u1v_LutScaleOff.y) * u1v_LutScaleOff.x );
    #endif
    

    // blending
    float a01 = color0.a + color1.a;
    
    if ( a01 > 0.0 )
        gl_FragColor.rgb = (color0.rgb * color0.a + color1.rgb * color1.a) / a01;
        
    gl_FragColor.a   = 1.0 - (1.0-color0.a) * (1.0-color1.a);
}