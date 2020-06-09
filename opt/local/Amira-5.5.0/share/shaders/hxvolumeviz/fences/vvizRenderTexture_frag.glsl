uniform sampler3D data;

void main()
{
  float vox = texture3D(data, gl_TexCoord[0].xyz).w;
  gl_FragColor = vec4(vox, vox, vox, 1.);
}
