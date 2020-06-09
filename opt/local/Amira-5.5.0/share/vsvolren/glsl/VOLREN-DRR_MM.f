uniform sampler3D   u0s_Density;
uniform sampler3D   u0s_Label;  // label texture
uniform sampler1D   u0s_Lookup1D;    // color tables (we just need alpha here)
uniform vec4        u0v_LutScaleOff;


#ifdef M_JITTER

varying vec3        v0v_TexCoordNextSample;
uniform sampler2D   u0s_Jitter;
uniform vec4        u0v_MinClipTexCoord;
uniform vec4        u0v_MaxClipTexCoord;

#endif



void main()
{
#ifdef M_JITTER

    float t      = texture2D( u0s_Jitter, gl_FragCoord.xy / 64.0 ).x;
    vec3  offset = (v0v_TexCoordNextSample.xyz - gl_TexCoord[0].xyz) * t;
    vec3  T0_o   = gl_TexCoord[0].xyz + offset;

#else

    vec3  T0_o   = gl_TexCoord[0].xyz;
    
#endif

    float dens   = texture3D( u0s_Density, T0_o ).a;
    float data   = max((dens-u0v_LutScaleOff.y) * u0v_LutScaleOff.x, 0.0);
    float label  = texture3D( u0s_Label, T0_o ).a;
    label        = ( floor( label * 255.0 + 0.1) + 0.5 ) / 256.0;
    float alpha  = texture1D( u0s_Lookup1D, label ).a;
    data        *= alpha;

   
// cleanup the border    
#ifdef M_JITTER

    data *= float ( all( lessThanEqual( T0_o, u0v_MaxClipTexCoord.xyz ) ) && all( greaterThanEqual( T0_o, u0v_MinClipTexCoord.xyz ) ) );

#endif    
    
    gl_FragColor = vec4(data,0.3*data,3.0*data,1.0);   
}
