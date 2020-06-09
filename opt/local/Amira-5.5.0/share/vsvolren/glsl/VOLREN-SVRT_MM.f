uniform sampler3D   u0s_RGBA;
uniform sampler3D   u0s_Density;
uniform sampler3D   u0s_Label;
uniform sampler2D   u0s_Lookup2D;
uniform vec4        u0v_LutScaleOff;
uniform vec4        u0v_AlphaCorrection;
uniform vec4        u0v_LightO;
uniform vec4        u0v_HalfwayO;
uniform vec4        u0v_Ambient;
uniform vec4        u0v_Specular;
uniform vec4        u0v_MinTexCoord;
uniform vec4        u0v_MaxTexCoord;


varying vec3        v_T0;
varying vec3        v_T1;
varying vec3        v_T2;
varying vec3        v_T3;
varying vec3        v_T4;
varying vec3        v_T5;
varying vec3        v_T6;


varying vec3        v0v_TexCoordNextSample;
uniform sampler2D   u0s_Jitter;
uniform vec4        u0v_MinClipTexCoord;
uniform vec4        u0v_MaxClipTexCoord;


void main()
{
    vec3  d;
    vec3  e;
    
    float label;
    float densi;
    vec3  norm;
    vec4  color;
    
    ////////////////////////////////////////
    // lookup center label/density/color
    ////////////////////////////////////////
    
    #ifdef M_JITTER
    
        vec3  T0_o; // offsetted sample texture coordinate
        
        float t      = texture2D( u0s_Jitter, gl_FragCoord.xy / 64.0 ).x;
        vec3  offset = (v0v_TexCoordNextSample.xyz - v_T0.xyz) * t;
        T0_o         = v_T0.xyz + offset;
        
        label  = texture3D( u0s_Label,   T0_o ).a;
        label  = ( floor( label * 255.0 + 0.1) + 0.5 ) / 256.0;
        
        #ifdef M_RGBA_0
            color    = texture3D( u0s_RGBA, T0_o );
            color.a  = ( 1.0 - pow( 1.0-color.a, u0v_AlphaCorrection.x ) ) * u0v_AlphaCorrection.y;
            color.a *= float( texture2D( u0s_Lookup2D, vec2(0.8,label) ).a > 0.0 ); // HACK!!!
        #else
            densi = texture3D( u0s_Density, T0_o ).a;
            color = texture2D( u0s_Lookup2D, vec2( (densi-u0v_LutScaleOff.y) * u0v_LutScaleOff.x, label ) );
        #endif
        
    #else
    
        #ifdef M_RGBA_0
            color    = texture3D( u0s_RGBA, v_T0.xyz );
            color.a  = ( 1.0 - pow( 1.0-color.a, u0v_AlphaCorrection.x ) ) * u0v_AlphaCorrection.y;
            color.a *= float( texture2D( u0s_Lookup2D, vec2(0.8,label) ).a > 0.0 ); // HACK!!!
        #else
            label  = texture3D( u0s_Label,   v_T0.xyz ).a;
            label  = ( floor( label * 255.0 + 0.1) + 0.5 ) / 256.0;
            densi  = texture3D( u0s_Density, v_T0.xyz ).a;
            color  = texture2D( u0s_Lookup2D, vec2( (densi-u0v_LutScaleOff.y) * u0v_LutScaleOff.x, label ) );
        #endif
                
    #endif     
    
    #ifdef M_RGBA_0
        color.r *= color.a;
        color.g *= color.a;
        color.b *= color.a;
    #endif 
    

    if ( color.a > 0.0001 )
    {
        ////////////////////////////////////////
        // lookup normal vector
        ////////////////////////////////////////
        
        #ifdef M_JITTER

            #ifdef M_RGBA_0
                d.x = texture3D( u0s_RGBA, v_T1 + offset ).r;
                d.y = texture3D( u0s_RGBA, v_T2 + offset ).r;
                d.z = texture3D( u0s_RGBA, v_T3 + offset ).r;
                e.x = texture3D( u0s_RGBA, v_T4 + offset ).r;
                e.y = texture3D( u0s_RGBA, v_T5 + offset ).r;
                e.z = texture3D( u0s_RGBA, v_T6 + offset ).r;
            #else
                d.x = texture3D( u0s_Density, v_T1 + offset ).a;
                d.y = texture3D( u0s_Density, v_T2 + offset ).a;
                d.z = texture3D( u0s_Density, v_T3 + offset ).a;
                e.x = texture3D( u0s_Density, v_T4 + offset ).a;
                e.y = texture3D( u0s_Density, v_T5 + offset ).a;
                e.z = texture3D( u0s_Density, v_T6 + offset ).a;
            #endif
                    
            color.a *= float ( all( lessThanEqual( T0_o, u0v_MaxClipTexCoord.xyz ) ) && all( greaterThanEqual( T0_o, u0v_MinClipTexCoord.xyz ) ) );

        #else
        
            #ifdef M_RGBA_0
                d.x = texture3D( u0s_RGBA, v_T1 ).r;
                d.y = texture3D( u0s_RGBA, v_T2 ).r;
                d.z = texture3D( u0s_RGBA, v_T3 ).r;
                e.x = texture3D( u0s_RGBA, v_T4 ).r;
                e.y = texture3D( u0s_RGBA, v_T5 ).r;
                e.z = texture3D( u0s_RGBA, v_T6 ).r;
            #else
                d.x = texture3D( u0s_Density, v_T1 ).a;
                d.y = texture3D( u0s_Density, v_T2 ).a;
                d.z = texture3D( u0s_Density, v_T3 ).a;
                e.x = texture3D( u0s_Density, v_T4 ).a;
                e.y = texture3D( u0s_Density, v_T5 ).a;
                e.z = texture3D( u0s_Density, v_T6 ).a;
            #endif
            
        #endif        

        ////////////////////////////////////////
        // near bound -> make normal vector parallel to the bound 
        ////////////////////////////////////////

        #define M_NO_NORMALCLIP

        #ifdef M_NO_NORMALCLIP
            
            norm = d - e;
            
        #else
        
            vec3 dmask;
            vec3 emask;
            
            #ifdef M_JITTER
                dmask = vec3( lessThan   ( T0_o, u0v_MaxTexCoord.xyz ) );
                emask = vec3( greaterThan( T0_o, u0v_MinTexCoord.xyz ) );
            #else
                dmask = vec3( lessThan   ( v_T0, u0v_MaxTexCoord.xyz ) );
                emask = vec3( greaterThan( v_T0, u0v_MinTexCoord.xyz ) );
            #endif       
             
            norm = d * dmask - e * emask;
            
        #endif


        ////////////////////////////////////////
        // normalize normal
        ////////////////////////////////////////

        #if 0
            norm = normalize(norm);
        #else
            float len2 = dot(norm,norm);
            if ( len2>0.0 )
               norm *= inversesqrt(len2);
        #endif

        ////////////////////////////////////////
        // compute lighting factors
        ////////////////////////////////////////
        
        float Idiff  = abs( dot( norm, u0v_LightO.xyz ) );

        #ifdef M_NO_SPECULAR_0
            gl_FragColor.rgb = (u0v_Ambient.x + Idiff) * color.rgb;
        #else
        
            float Ispec  = dot( norm, u0v_HalfwayO.xyz )  ;
        
            Ispec *= Ispec;
            Ispec *= Ispec;
            Ispec *= Ispec;
    
            gl_FragColor.rgb = (u0v_Ambient.x + Idiff)*color.rgb + Ispec*u0v_Specular.rgb;
        
        #endif

        gl_FragColor.a = color.a;

    }
    else
    {
        gl_FragColor   = color;
        gl_FragColor.a = 0.0;
    }
}
