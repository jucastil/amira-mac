uniform sampler3D depthTexture;
uniform float depthInputLayer;
uniform vec2 texRectTo2D;
uniform int enableFragmentTest;
              
void main() 
{
  if (enableFragmentTest != 0)
  {
    vec2 coords = gl_FragCoord.xy * texRectTo2D;
    float tmp = texture3D( depthTexture, vec3(coords, depthInputLayer) ).x;
    if (tmp >= gl_FragCoord.z)
      discard;
  }
  gl_FragColor = vec4(gl_FragCoord.z, gl_FragCoord.z, gl_FragCoord.z, 1.0);
}
