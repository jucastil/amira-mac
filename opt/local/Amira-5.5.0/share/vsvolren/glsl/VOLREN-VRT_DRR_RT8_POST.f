uniform sampler2D   u0s_Result;
uniform vec4        u0v_Gamma;

void main()
{
    vec4 data    = texture2D( u0s_Result, gl_TexCoord[0].xy );
    
    float u      = data.r;
    float v      = 1.0 - pow( 1.0-u, 1.0/4.0 );
    
    gl_FragColor = vec4(v,v,v,1.0);
}
