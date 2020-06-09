#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect fbDepthTexture;

//uniform vec2 viewportSize;
          
void main() {
  //vec3 coords = vec3( gl_FragCoord.x / viewportSize.x, gl_FragCoord.y / viewportSize.y, gl_FragCoord.z );
  gl_FragDepth = texture2DRect( fbDepthTexture, gl_FragCoord.xy ).w;
}
