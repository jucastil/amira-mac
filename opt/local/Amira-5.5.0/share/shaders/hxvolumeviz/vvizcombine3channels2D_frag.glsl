uniform sampler2D TransferTex;
uniform sampler2D Data1;
uniform sampler2D Data2;
uniform sampler2D Data3;

void main()
{ 
  // Texture coord are only sent in tex unit 0
  vec2 texCoord = vec2(gl_TexCoord[0]);
  
  // Texture unit 1 -> Data 1
  vec4 index1 = texture2D(Data1, texCoord);
  vec4 color1 = texture2D(TransferTex, vec2(index1.w, 0.1));
  
  // Texture unit 2 -> Data 2
  vec4 index2 = texture2D(Data2, texCoord);
  vec4 color2 = texture2D(TransferTex, vec2(index2.w, 0.5));
  
  // Texture unit 3 -> Data 3
  vec4 index3 = texture2D(Data3, texCoord);
  vec4 color3 = texture2D(TransferTex, vec2(index3.w, 0.9));
   
  gl_FragColor.rgb = (color1.rgb * color1.a + color2.rgb * color2.a + color3.rgb * color3.a) / 
                     (color1.a + color2.a + color3.a) ;
                     
  gl_FragColor.a = max(max(color1.a, color2.a), color3.a) * gl_Color.a ;
}