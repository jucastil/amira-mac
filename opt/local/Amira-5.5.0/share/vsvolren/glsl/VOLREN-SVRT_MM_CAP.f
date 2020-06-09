uniform sampler3D   u0s_RGBA;
uniform sampler3D   u0s_Density;
uniform sampler3D   u0s_Label;
uniform sampler2D   u0s_Lookup2D;
uniform vec4        u0v_LutScaleOff;
uniform vec4        u0v_AlphaCorrection;
uniform vec4        u0v_LightW;
uniform vec4        u0v_HalfwayW;
uniform vec4        u0v_Ambient;
uniform vec4        u0v_Specular;
uniform vec4        u0v_MinTexCoord;
uniform vec4        u0v_MaxTexCoord;

varying vec3        v_DeltaPosA;
varying vec3        v_DeltaPosB;
varying vec3        v_DeltaPosC;

varying vec3        v_DeltaPosAT;
varying vec3        v_DeltaPosBT;
varying vec3        v_DeltaPosCT;

varying vec3        v_T0;



float inBrickTex( vec3 inCoord )
{
    return  float(  all( lessThanEqual   ( inCoord, u0v_MaxTexCoord.xyz ) ) 
                &&  all( greaterThanEqual( inCoord, u0v_MinTexCoord.xyz ) ) 
                 );
}


void main()
{
    vec3  d;
    vec3  e;
    
    float label;
    float densi;
    vec3  norm;
    vec4  color;
    
    ////////////////////////////////////////
    // lookup center label
    ////////////////////////////////////////
    
    label  = texture3D( u0s_Label,   v_T0.xyz ).a;
    label  = ( floor( label * 255.0 + 0.1) + 0.5 ) / 256.0;

    #ifdef M_RGBA_0
        color    = texture3D( u0s_RGBA, v_T0.xyz );
        color.a  = ( 1.0 - pow( 1.0-color.a, u0v_AlphaCorrection.x ) ) * u0v_AlphaCorrection.y;
        color.a *= float( texture2D( u0s_Lookup2D, vec2(0.8,label) ).a > 0.0 ); // HACK!!!
        color.r *= color.a;
        color.g *= color.a;
        color.b *= color.a;
    #else
        densi = texture3D( u0s_Density, v_T0.xyz ).a;
        color = texture2D( u0s_Lookup2D, vec2( (densi-u0v_LutScaleOff.y) * u0v_LutScaleOff.x, label ) );
    #endif
    
    ////////////////////////////////////////
    // lookup center color
    ////////////////////////////////////////

    if ( color.a > 0.0001 )
    {
        vec3 v_T2 = v_T0 + v_DeltaPosBT;
        vec3 v_T3 = v_T0 + v_DeltaPosCT;
        vec3 v_T4 = v_T0 - v_DeltaPosAT;
        vec3 v_T5 = v_T0 - v_DeltaPosBT;
        vec3 v_T6 = v_T0 - v_DeltaPosCT;
                
        ////////////////////////////////////////
        // lookup normal vector
        ////////////////////////////////////////
        
        // get samples in gradient directions
        d.x = 0.0;
        
        #ifdef M_RGBA_0
            d.y = texture3D( u0s_RGBA, v_T2 ).r;
            d.z = texture3D( u0s_RGBA, v_T3 ).r;
            e.x = texture3D( u0s_RGBA, v_T4 ).r;
            e.y = texture3D( u0s_RGBA, v_T5 ).r;
            e.z = texture3D( u0s_RGBA, v_T6 ).r;
        #else
            d.y = texture3D( u0s_Density, v_T2 ).a;
            d.z = texture3D( u0s_Density, v_T3 ).a;
            e.x = texture3D( u0s_Density, v_T4 ).a;
            e.y = texture3D( u0s_Density, v_T5 ).a;
            e.z = texture3D( u0s_Density, v_T6 ).a;
        #endif

        vec3 dmask = vec3(                1.0, inBrickTex( v_T2 ), inBrickTex( v_T3 ) );
        vec3 emask = vec3( inBrickTex( v_T4 ), inBrickTex( v_T5 ), inBrickTex( v_T6 ) );

        vec3 diff = e * emask - d * dmask;

        // determine gradients in directions A,B,C
        vec3 gradA = v_DeltaPosA.xyz * diff.x;
        vec3 gradB = v_DeltaPosB.xyz * diff.y;
        vec3 gradC = v_DeltaPosC.xyz * diff.z;

    
        // average gradients
        norm = gradA + gradB + gradC;
       

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
        
        float Idiff  = abs( dot( norm, u0v_LightW.xyz ) );

        #ifdef M_NO_SPECULAR_0
            gl_FragColor.rgb = (u0v_Ambient.x + Idiff) * color.rgb;
        #else

            float Ispec  = dot( norm, u0v_HalfwayW.xyz )  ;
    
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
