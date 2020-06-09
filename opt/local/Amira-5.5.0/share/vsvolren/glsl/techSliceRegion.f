uniform sampler2D   u0s_Label;
uniform sampler1D   u0s_LookupLabel;


void main()
{
    float matVal = texture2D( u0s_Label, gl_TexCoord[0].xy ).x;

    // Voxels with the most significant label bit set will just be
    // considered selected voxels, they will be rendered according
    // to the seven remaining bits.
    matVal -= (matVal > 127.5 / 255.0) ? 128.0 / 255.0 : 0.0;

    gl_FragColor = gl_Color * texture1D( u0s_LookupLabel, matVal + 0.5/255.0);
}
