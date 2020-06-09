uniform sampler2D   u0s_Density;
uniform sampler2D   u0s_Label;
uniform vec4        u0v_SelectionColor; // selection color 
uniform vec4        u0v_HighlightColor; // highlight color
uniform vec4        u0v_HighlightDW;    // highlight data window


void main()
{
    vec4 color = vec4(0.0);
    
    float matVal   = texture2D( u0s_Label, gl_TexCoord[0].xy ).x;
    float densiVal = texture2D( u0s_Density, gl_TexCoord[0].xy ).x;
    
    // check if highlight is enabled
    if ( u0v_HighlightDW.b > 0.0)
    {
        if ( densiVal >= u0v_HighlightDW.r && densiVal <= u0v_HighlightDW.g )
            color = u0v_HighlightColor;
    }
    
    // Voxels with the most significant label bit set will be
    // considered selected voxels. They will be rendered with the color
    // of material 128, and transparent otherwise.
     
    // check if selection is enabled
    if ( u0v_HighlightDW.a > 0.0)
    {
        matVal = clamp(matVal, 0.0, 128.0/255.0); 
        if(matVal >= 127.5/255.0)
            color = u0v_SelectionColor;
    }
    gl_FragColor = color;
}
