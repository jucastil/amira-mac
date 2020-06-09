uniform sampler2D   u0s_Density;
uniform sampler1D   u0s_LookupDensity;

uniform vec4        u0v_LutScaleOff;


void main()
{
    float data     = texture2D( u0s_Density, gl_TexCoord[0].xy ).x;
    vec4  outColor = texture1D( u0s_LookupDensity, (data-u0v_LutScaleOff.y) * u0v_LutScaleOff.x );
 
    // Ignore alpha channel of lookup table as default
    if (u0v_LutScaleOff.z == 0.0)
    	outColor.a = 1.0;

    // gl_FragColor   = (data-u0v_LutScaleOff.y) * u0v_LutScaleOff.x;
    gl_FragColor = gl_Color * outColor;
}
