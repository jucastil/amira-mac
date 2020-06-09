// volume SVRT_MM
uniform sampler3D   u0s_RGBA;
uniform sampler3D   u0s_Density;
uniform sampler2D   u0s_Lookup2D;
uniform vec4        u0v_LutScaleOff;
uniform vec4        u0v_AlphaCorrection;
uniform vec4        u0v_LightO;
uniform vec4        u0v_HalfwayO;
uniform vec4        u0v_Ambient;
uniform vec4        u0v_Specular;
uniform sampler3D   u0s_Label;


varying vec3        v_T00;
varying vec3        v_T01;
varying vec3        v_T02;
varying vec3        v_T03;
varying vec3        v_T04;
varying vec3        v_T05;
varying vec3        v_T06;


// volume VRT
uniform sampler3D   u1s_RGBA;
uniform sampler3D   u1s_Density;
uniform sampler2D   u1s_Lookup2D;
uniform vec4        u1v_LutScaleOff;
uniform vec4        u1v_AlphaCorrection;

varying vec3        v_T10;


void main()
{
    float densi0;
    float densi1;
    
    vec4  color0;
    vec4  color1;
    
    
    gl_FragColor = vec4(0.0);
    
    ////////////////////////////////////////
    // slot 0 - SVRT
    ////////////////////////////////////////
    
    float label  = texture3D( u0s_Label  , v_T00 ).a;
    label        = ( floor( label * 255.0 + 0.1) + 0.5 ) / 256.0;

    
    #ifndef M_HIDE_LABEL_VOLUME
        
        vec3  d;
        vec3  e;    
    
        #ifdef M_RGBA_0
            color0    = texture3D( u0s_RGBA, v_T00.xyz );
            color0.a  = ( 1.0 - pow( 1.0-color0.a, u0v_AlphaCorrection.x ) ) * u0v_AlphaCorrection.y;
        #else
            densi0    = texture3D( u0s_Density, v_T00.xyz ).a;
            color0    = texture2D( u0s_Lookup2D, vec2( (densi0-u0v_LutScaleOff.y) * u0v_LutScaleOff.x, label ) );
        #endif

        color0.a *= u0v_LutScaleOff.z;
        
        if ( color0.a > 0.0001 )
        {
            #ifdef M_RGBA_0
                d.x = texture3D( u0s_RGBA, v_T01.xyz ).r;
                d.y = texture3D( u0s_RGBA, v_T02.xyz ).r;
                d.z = texture3D( u0s_RGBA, v_T03.xyz ).r;
                e.x = texture3D( u0s_RGBA, v_T04.xyz ).r;
                e.y = texture3D( u0s_RGBA, v_T05.xyz ).r;
                e.z = texture3D( u0s_RGBA, v_T06.xyz ).r;    
            #else
                d.x = texture3D( u0s_Density, v_T01.xyz ).a;
                d.y = texture3D( u0s_Density, v_T02.xyz ).a;
                d.z = texture3D( u0s_Density, v_T03.xyz ).a;
                e.x = texture3D( u0s_Density, v_T04.xyz ).a;
                e.y = texture3D( u0s_Density, v_T05.xyz ).a;
                e.z = texture3D( u0s_Density, v_T06.xyz ).a;    
            #endif
            
            vec3 norm = d - e;
            
            // normalize
            float len2 = dot(norm,norm);
            if ( len2>0.0 )
               norm *= inversesqrt(len2);      
               
            float Idiff  = abs( dot( norm, u0v_LightO.xyz ) );
            
            #ifdef M_NO_SPECULAR_0
            
                color0.rgb = (u0v_Ambient.x + Idiff) * color0.rgb;
            
            #else
    
                float Ispec  = dot( norm, u0v_HalfwayO.xyz )  ;
        
                Ispec *= Ispec;
                Ispec *= Ispec;
                Ispec *= Ispec;
        
                color0.rgb = (u0v_Ambient.x + Idiff) * color0.rgb + Ispec * u0v_Specular.rgb;
    
            #endif
        }
        
    #endif    
    
    
    ////////////////////////////////////////
    // slot 1 - VRT
    ////////////////////////////////////////
            
    #ifdef M_RGBA_1
        color1  = texture3D( u1s_RGBA, v_T10 );
        color1.a = ( 1.0 - pow( 1.0-color1.a, u1v_AlphaCorrection.x ) ) * u1v_AlphaCorrection.y;
    #else
        densi1  = texture3D( u1s_Density, v_T10 ).a;
        color1  = texture2D( u1s_Lookup2D, vec2( (densi1-u1v_LutScaleOff.y) * u1v_LutScaleOff.x, label ) );
    #endif
            
    color1.a *= u1v_LutScaleOff.z;
    

    ////////////////////////////////////////
    
    #ifdef M_HIDE_LABEL_VOLUME
    
        gl_FragColor = color1;
        
    #else
        // blending
        float a01 = color0.a + color1.a;
        
        if ( a01 > 0.0 )
            gl_FragColor.rgb = (color0.rgb * color0.a + color1.rgb * color1.a) / a01;
            
        gl_FragColor.a   = 1.0 - (1.0-color0.a) * (1.0-color1.a);

    #endif    
}