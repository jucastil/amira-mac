#define FIXED_UNIFORM_HACK 1

uniform sampler3D   u0s_RGBA;
uniform sampler3D   u0s_Density;
uniform sampler1D   u0s_Lookup1D;
uniform vec4        u0v_LutScaleOff;
uniform vec4        u0v_AlphaCorrection;

uniform vec4        u0v_LightW;
uniform vec4        u0v_HalfwayW;
uniform vec4        u0v_Ambient;
uniform vec4        u0v_Specular;
uniform vec4        u0v_MinTexCoord;
uniform vec4        u0v_MaxTexCoord;


varying vec3        v_T0;

#if FIXED_UNIFORM_HACK

varying vec3    v_DeltaPosA;
varying vec3    v_DeltaPosB;
varying vec3    v_DeltaPosC;

varying vec3    v_DeltaPosAT;
varying vec3    v_DeltaPosBT;
varying vec3    v_DeltaPosCT;

#else

uniform vec4        u0v_DeltaPosA;
uniform vec4        u0v_DeltaPosB;
uniform vec4        u0v_DeltaPosC;

varying vec3        v_T2;
varying vec3        v_T3;
varying vec3        v_T4;
varying vec3        v_T5;
varying vec3        v_T6;

#endif



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
    float data;
    vec4  color;
    vec3  norm;

    ////////////////////////////////////////
    // lookup center color
    ////////////////////////////////////////
    
    #ifdef M_RGBA_0
        color = texture3D( u0s_RGBA, v_T0 );
        color.a = ( 1.0 - pow( 1.0-color.a, u0v_AlphaCorrection.x ) ) * u0v_AlphaCorrection.y;
    #else
        data  = texture3D( u0s_Density, v_T0 ).a;
        color = texture1D( u0s_Lookup1D, (data-u0v_LutScaleOff.y) * u0v_LutScaleOff.x );
    #endif
    
        
    if ( color.a > 0.0001 )
    {

#if FIXED_UNIFORM_HACK

        vec3 v_T2 = v_T0 + v_DeltaPosBT;
        vec3 v_T3 = v_T0 + v_DeltaPosCT;
        vec3 v_T4 = v_T0 - v_DeltaPosAT;
        vec3 v_T5 = v_T0 - v_DeltaPosBT;
        vec3 v_T6 = v_T0 - v_DeltaPosCT;

#endif

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
#if FIXED_UNIFORM_HACK
        vec3 gradA = v_DeltaPosA.xyz * diff.x;
        vec3 gradB = v_DeltaPosB.xyz * diff.y;
        vec3 gradC = v_DeltaPosC.xyz * diff.z;
#else
        vec3 gradA = u0v_DeltaPosA.xyz * diff.x;
        vec3 gradB = u0v_DeltaPosB.xyz * diff.y;
        vec3 gradC = u0v_DeltaPosC.xyz * diff.z;
#endif
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

