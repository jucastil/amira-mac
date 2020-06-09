uniform sampler3D data;

void main()
{
  gl_FragColor = texture3D(data, gl_TexCoord[0].xyz);
}
