uniform sampler2D   u0s_Result;
uniform vec4        u0v_SelectionColor;

void main()
{
    vec4 data = texture2D( u0s_Result, gl_TexCoord[0].xy );

#ifdef M_INVERSE_MIP
    if ( data.g < 0.5 )
#else
    if ( data.g > 0.5 )
#endif
    {
        // selected
#ifdef M_INVERSE_MIP
        gl_FragColor.r = u0v_SelectionColor.r * (data.r + 0.5);
        gl_FragColor.g = u0v_SelectionColor.g * (data.r + 0.5) * 0.5;
        gl_FragColor.b = u0v_SelectionColor.b * (data.r + 0.5) * 0.5;
        gl_FragColor.a = u0v_SelectionColor.a * (data.r + 0.5);
#else
        gl_FragColor.r = u0v_SelectionColor.r * (data.r + 0.5);
        gl_FragColor.g = u0v_SelectionColor.g * (data.r + 0.5);
        gl_FragColor.b = u0v_SelectionColor.b * (data.r + 0.5);
        gl_FragColor.a = u0v_SelectionColor.a * (data.r + 0.5);
#endif
    }
    else
    {
        // not selected
        gl_FragColor = vec4( data.r, data.r, data.r, 1.0 );
    }
}
