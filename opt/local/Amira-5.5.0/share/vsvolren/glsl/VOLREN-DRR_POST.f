uniform sampler2D   u0s_Result;
uniform vec4        u0v_Gamma;

void main()
{
    vec4 data    = texture2D( u0s_Result, gl_TexCoord[0].xy ) * vec4(1.0,3.3333,0.3333,1.0);
    float u      = (data.r > data.g) ? data.r : data.g;
    u            = (u > data.b) ? u : data.b;
    float v      = 1.0 - exp( -u * u0v_Gamma.g );

    gl_FragColor = vec4(v,v,v,1.0);
}
