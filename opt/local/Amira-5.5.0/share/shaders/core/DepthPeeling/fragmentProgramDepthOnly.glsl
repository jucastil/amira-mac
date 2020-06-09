
uniform sampler2DShadow depthTexture;

uniform vec2 texRectTo2D;
              
void main() {
  vec3 coords = gl_FragCoord.xyz * vec3(texRectTo2D, 1.0);
  float tmp = shadow2D( depthTexture, coords ).w;
  if (tmp < 0.5)
    discard;
  gl_FragDepth = gl_FragCoord.z;
  //gl_FragColor = gl_Color;
}
