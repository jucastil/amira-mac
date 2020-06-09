uniform sampler2D VVizJitterTex;
uniform float VVizNoiseTexSizeInv;

/**
 * Return a randomly displaced texture coord along the view vector
 * into the current voxel
 */
vec3 VVizJitter(vec3 tcoord)
{
  vec3 rayDir = gl_TexCoord[1].xyz-gl_TexCoord[0].xyz;
  vec2 noiseCoord = gl_FragCoord.xy*VVizNoiseTexSizeInv;
  float jitter = texture2D(VVizJitterTex, noiseCoord).x;

  return tcoord+rayDir*jitter;
}
