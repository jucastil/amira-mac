uniform sampler2D   u0s_RGBA;
uniform sampler1D   u0s_LookupDensity;

uniform vec4        u0v_LutScaleOff;


void main()
{
    vec4  data     = texture2D( u0s_RGBA, gl_TexCoord[0].xy );
    vec4  outColor = texture1D( u0s_LookupDensity, 1.5*data.a );

    outColor.rgb = data.rgb;

    gl_FragColor = outColor;
}
