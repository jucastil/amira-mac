uniform sampler2D   u0s_DepthTexture;
uniform sampler2D   u0s_ColorTexture;
uniform vec4        u0v_TextureSize;
uniform vec4        u0v_DepthMultiply;
uniform vec4        u0v_ColorMultiply;


void main()
{
    vec4 coord = gl_FragCoord;

    // TODO: I believe that this mapping is wrong.
    //       Window coordinates in gl_FragCoord are always in the
    //       pixel centers (i.e, 0.5 1.5 2.5 ...) which means that
    //       a division by u0v_TextureSize should give the correct
    //       pixel to texel mapping. However, the uppermost and 
    //       rightmost pixels look wrong.
    //       Thus, time should be spent to figure out the CORRECT 
    //       vertex to viewport mapping. For the time beeing
    //       we use some workarounds.
    coord.x = (coord.x) / (u0v_TextureSize.x); // - 1);
    coord.y = (coord.y) / (u0v_TextureSize.y); // - 1);
    coord.w = 1.0;
 
    gl_FragDepth = u0v_DepthMultiply.x * texture2D( u0s_DepthTexture, coord.xy).x;
    gl_FragColor = u0v_ColorMultiply * texture2D( u0s_ColorTexture, coord.xy);

    // gl_FragColor.rgb = texture2D( u0s_DepthTexture, coord.xy).xxx;
    // gl_FragColor.a = 1.0;
}
