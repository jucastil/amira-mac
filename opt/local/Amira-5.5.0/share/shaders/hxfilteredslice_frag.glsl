uniform sampler2D texUnit;
uniform float brightness;
uniform float contrast;

void main()
{ 
  vec3 color = texture2D(texUnit,gl_TexCoord[0].xy).xyz;
  float transparency = texture2D(texUnit,gl_TexCoord[0].xy).w;
  
  //
  // Apply brightness
  //
  vec3 britghVec = vec3(brightness, brightness, brightness);
  color += britghVec;
  
  //
  // Apply contrast
  //
  vec3 average = vec3(0.5, 0.5, 0.5) + britghVec;
  color = average + ((color-average) * contrast);
  
  gl_FragColor.xyz = color;
  gl_FragColor.w = transparency;
}
