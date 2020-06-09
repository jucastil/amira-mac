// volume 0 SVRT
uniform sampler3D   u0s_RGBA;
uniform sampler3D   u0s_Density;
uniform sampler1D   u0s_Lookup1D;
uniform vec4        u0v_LutScaleOff;
uniform vec4        u0v_AlphaCorrection;
uniform vec4        u0v_LightW;
uniform vec4        u0v_HalfwayW;
uniform vec4        u0v_Ambient;
uniform vec4        u0v_Specular;

uniform vec4        u0v_DeltaPosA;
uniform vec4        u0v_DeltaPosB;
uniform vec4        u0v_DeltaPosC;

varying vec3        v_T00;
varying vec3        v_T02;
varying vec3        v_T03;
varying vec3        v_T04;
varying vec3        v_T05;
varying vec3        v_T06;


// volume 1 VRT
uniform sampler3D   u1s_RGBA;
uniform sampler3D   u1s_Density;
uniform sampler3D   u1s_Label;
uniform sampler2D   u1s_Lookup2D;
uniform vec4        u1v_LutScaleOff;
uniform vec4        u1v_AlphaCorrection;
uniform vec4        u1v_Ambient;

varying vec3        v_T10;





void main()
{
    gl_FragColor = vec4(0.0);
    
    vec3  d;
    vec3  e;    

    float densi0;
    float densi1;

    vec4  color0;
    vec4  color1;

    float label1;
    

    ////////////////////////////////////////
    // volume 0 SVRT
    ////////////////////////////////////////

    #ifdef M_RGBA_0
        color0 = texture3D( u0s_RGBA, v_T00.xyz );
        color0.a = ( 1.0 - pow( 1.0-color0.a, u0v_AlphaCorrection.x ) ) * u0v_AlphaCorrection.y;
    #else
        densi0 = texture3D( u0s_Density, v_T00.xyz ).a;
        color0 = texture1D( u0s_Lookup1D, (densi0-u0v_LutScaleOff.y) * u0v_LutScaleOff.x );
    #endif

    if ( color0.a > 0.0001 )
    {
        d.x = 0.0;
        
        #ifdef M_RGBA_0
            d.y = texture3D( u0s_RGBA, v_T02 ).r;
            d.z = texture3D( u0s_RGBA, v_T03 ).r;
            e.x = texture3D( u0s_RGBA, v_T04 ).r;
            e.y = texture3D( u0s_RGBA, v_T05 ).r;
            e.z = texture3D( u0s_RGBA, v_T06 ).r;    
        #else
            d.y = texture3D( u0s_Density, v_T02 ).a;
            d.z = texture3D( u0s_Density, v_T03 ).a;
            e.x = texture3D( u0s_Density, v_T04 ).a;
            e.y = texture3D( u0s_Density, v_T05 ).a;
            e.z = texture3D( u0s_Density, v_T06 ).a;    
        #endif
        
        vec3 diff = e - d;

        // determine gradients in directions A,B,C
        vec3 gradA = u0v_DeltaPosA.xyz * diff.x;
        vec3 gradB = u0v_DeltaPosB.xyz * diff.y;
        vec3 gradC = u0v_DeltaPosC.xyz * diff.z;

    
        // average gradients
        vec3 norm = gradA + gradB + gradC;
        
        // normalize
        float len2 = dot(norm,norm);
        if ( len2>0.0 )
           norm *= inversesqrt(len2);      
           
        float Idiff  = abs( dot( norm, u0v_LightW.xyz ) );
        
#ifdef M_NO_SPECULAR_0

        color0.rgb = (u0v_Ambient.x + Idiff) * color0.rgb;

#else

        float Ispec  = dot( norm, u0v_HalfwayW.xyz )  ;

        Ispec *= Ispec;
        Ispec *= Ispec;
        Ispec *= Ispec;

        color0.rgb = (u0v_Ambient.x + Idiff) * color0.rgb + Ispec * u0v_Specular.rgb;

#endif
    }
    
    ////////////////////////////////////////
    // volume 1 VRT
    ////////////////////////////////////////
    
    label1 = texture3D( u1s_Label, v_T10.xyz ).a;
    label1 = ( floor( label1 * 255.0 + 0.1) + 0.5 ) / 256.0;
        
    #ifdef M_RGBA_1
        color1 = texture3D( u1s_RGBA, v_T10.xyz );
        color1.a = ( 1.0 - pow( 1.0-color1.a, u1v_AlphaCorrection.x ) ) * u1v_AlphaCorrection.y;
        color1.a *= float( texture2D( u1s_Lookup2D, vec2(0.8,label1) ).a > 0.0 ); // HACK!!!
    #else
        densi1 = texture3D( u1s_Density, v_T10.xyz ).a;
        color1 = texture2D( u1s_Lookup2D, vec2( (densi1-u1v_LutScaleOff.y) * u1v_LutScaleOff.x, label1 ) );
    #endif
    

    ////////////////////////////////////////
    // blending
    ////////////////////////////////////////
    
    float a01 = color0.a + color1.a;
    
    if ( a01 > 0.0 )
        gl_FragColor.rgb = (color0.rgb * color0.a + color1.rgb * color1.a) / a01;
        
    gl_FragColor.a   = 1.0 - (1.0-color0.a) * (1.0-color1.a);
}