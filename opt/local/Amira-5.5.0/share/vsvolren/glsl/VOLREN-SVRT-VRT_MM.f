// volume SVRT
uniform sampler3D   u0s_Density;
uniform sampler2D   u0s_Lookup2D;
uniform vec4        u0v_LutScaleOff;
uniform vec4        u0v_LightO;
uniform vec4        u0v_HalfwayO;
uniform vec4        u0v_Ambient;
uniform vec4        u0v_Specular;

varying vec3        v_T00;
varying vec3        v_T01;
varying vec3        v_T02;
varying vec3        v_T03;
varying vec3        v_T04;
varying vec3        v_T05;
varying vec3        v_T06;


// volume VRT_MM
uniform sampler3D   u1s_Density;
uniform sampler2D   u1s_Lookup2D;
uniform vec4        u1v_LutScaleOff;
uniform sampler3D   u1s_Label;

varying vec3        v_T10;



void main()
{
    gl_FragColor = vec4(0.0);
    
    // volume SVRT
    vec3  d;
    vec3  e;    
    
    float label  = texture3D( u1s_Label  , v_T10 ).a;
    label        = ( floor( label * 255.0 + 0.1) + 0.5 ) / 256.0;
    
    float data0  = texture3D( u0s_Density, v_T00.xyz ).a;
    vec4  color0 = texture2D( u0s_Lookup2D, vec2( (data0-u0v_LutScaleOff.y) * u0v_LutScaleOff.x, label ) );
    color0.a    *= u0v_LutScaleOff.z;

    if ( color0.a > 0.0001 )
    {
        d.x = texture3D( u0s_Density, v_T01.xyz ).a;
        d.y = texture3D( u0s_Density, v_T02.xyz ).a;
        d.z = texture3D( u0s_Density, v_T03.xyz ).a;
        e.x = texture3D( u0s_Density, v_T04.xyz ).a;
        e.y = texture3D( u0s_Density, v_T05.xyz ).a;
        e.z = texture3D( u0s_Density, v_T06.xyz ).a;    
        
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
    
    
    // volume VRT
#ifndef M_HIDE_LABEL_VOLUME
  
    float data1  = texture3D( u1s_Density, v_T10 ).a;
    vec4  color1 = texture2D( u1s_Lookup2D, vec2( (data1-u1v_LutScaleOff.y) * u1v_LutScaleOff.x, label ) );
    color1.a    *= u1v_LutScaleOff.z;
    

    // blending
    float a01 = color0.a + color1.a;
    
    if ( a01 > 0.0 )
        gl_FragColor.rgb = (color0.rgb * color0.a + color1.rgb * color1.a) / a01;
        
    gl_FragColor.a   = 1.0 - (1.0-color0.a) * (1.0-color1.a);
    
#else

    gl_FragColor = color0;

#endif    
}