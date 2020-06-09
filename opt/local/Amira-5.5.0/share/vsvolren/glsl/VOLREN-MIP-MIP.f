// slot 0 MIP
uniform sampler3D   u0s_RGBA;
uniform sampler3D   u0s_Density;
uniform vec4        u0v_LutScaleOff;
uniform vec4        u0v_AlphaCorrection;

varying vec3        v_T0;

// slot 1 MIP
uniform sampler3D   u1s_RGBA;
uniform sampler3D   u1s_Density;
uniform vec4        u1v_LutScaleOff;
uniform vec4        u1v_AlphaCorrection;

varying vec3        v_T1;


void main()
{
    float data0;
    float data1;
    
    float lumi0;
    float lumi1;
    float lumi;
    
    vec4  color0;
    vec4  color1;
    vec4  color;
    
    ////////////////////////////////////////
    // slot 0
    ////////////////////////////////////////
    #ifdef M_RGBA_0
        color0    = texture3D( u0s_RGBA, v_T0 );
        color0.a *= u0v_AlphaCorrection.y;
        color0.r *= color0.a;
        color0.g *= color0.a;
        color0.b *= color0.a;
    #else
        data0   = texture3D( u0s_Density, v_T0 ).a;
        lumi0   = (data0-u0v_LutScaleOff.y) * u0v_LutScaleOff.x;
    #endif

    ////////////////////////////////////////
    // slot 1
    ////////////////////////////////////////
    #ifdef M_RGBA_1
        color1    = texture3D( u1s_RGBA, v_T1 );
        color1.a *= u1v_AlphaCorrection.y;
        color1.r *= color1.a;
        color1.g *= color1.a;
        color1.b *= color1.a;
    #else
        data1   = texture3D( u1s_Density, v_T1 ).a;
        lumi1   = (data1-u1v_LutScaleOff.y) * u1v_LutScaleOff.x;
    #endif

    ////////////////////////////////////////
    // blending
    ////////////////////////////////////////
    
    #if    defined(M_RGBA_0) &&  defined(M_RGBA_1)
        color = max( color0, color1 );
    #elif  defined(M_RGBA_0) && !defined(M_RGBA_1)
        color = max( color0, vec4(lumi1) );
    #elif !defined(M_RGBA_0) &&  defined(M_RGBA_1)
        color = max( vec4(lumi1), color1 );
    #else
        lumi = max( lumi0, lumi1 );
    #endif
    
    

#ifdef M_INVERSE_MIP

    #if defined(M_RGBA_0) || defined(M_RGBA_1)
        gl_FragColor = vec4( 1.0-color.r, 1.0-color.g, 1.0-color.b, color.a );
    #else
        gl_FragColor = vec4( 1.0-lumi, 1.0-lumi, 1.0-lumi, lumi );
    #endif

#else

    #if defined(M_RGBA_0) || defined(M_RGBA_1)
        gl_FragColor = color;
    #else
        gl_FragColor = vec4(lumi);
    #endif

#endif    
}