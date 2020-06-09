
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRectShadow opaqueTexture;
uniform sampler2DRectShadow depthTexture;
uniform sampler3D baseTexture;

uniform vec2 enableDiscardTest;
              
void main() {
  // For delayed sorted layer blend
  if (enableDiscardTest.x != 0.0)
  {
	float tmp = shadow2DRect( opaqueTexture, gl_FragCoord.xyz ).w;
	if (tmp == 0.0)
	  discard; 
  }
	
  if (enableDiscardTest.y > 0.5)
  {
    float tmp = shadow2DRect( depthTexture, gl_FragCoord.xyz ).w;
    if (tmp == 0.0)
      discard; 
  }
   
  gl_FragColor = texture3D(baseTexture, gl_TexCoord[0].xyz) * gl_Color;
}
