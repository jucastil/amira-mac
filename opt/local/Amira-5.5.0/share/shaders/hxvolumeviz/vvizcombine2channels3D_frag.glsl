uniform sampler2D TransferTex;
uniform sampler3D Data1;
uniform sampler3D Data2;

void main()
{ 
  // Texture coord are only sent in tex unit 0
  vec3 texCoord = vec3(gl_TexCoord[0]);
  
  // Texture unit 1 -> Data 1
  vec4 index1 = texture3D(Data1, texCoord);
  vec4 color1 = texture2D(TransferTex, vec2(index1.w, 0.1));
  
  // Texture unit 2 -> Data 2
  vec4 index2 = texture3D(Data2, texCoord);
  vec4 color2 = texture2D(TransferTex, vec2(index2.w, 0.8));
   
  gl_FragColor.rgb = (color1.rgb * color1.a + color2.rgb * color2.a) / (color1.a + color2.a) ;
  gl_FragColor.a = max(color1.a, color2.a) * gl_Color.a ;
}