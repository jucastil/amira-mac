uniform int VVizNumLights;

vec4 VVizLightingInternal(int light, vec3 n, vec4 col, gl_LightProducts lightProduct,
                          gl_LightSourceParameters lightSource,
                          gl_MaterialParameters mat)
{
  vec4 res = vec4(0., 0., 0., 0.);

  vec4 vp = lightSource.position;

  float vpLength = length(vp);
  vp /= vpLength;
  float nDotVp = dot(n, vp.xyz);

  float att = 1.0/(lightSource.constantAttenuation+
                   lightSource.linearAttenuation*vpLength+
                   lightSource.quadraticAttenuation*vpLength*vpLength);
  res += att*(lightProduct.ambient+max(nDotVp, 0.)*lightProduct.diffuse*col);
  float fi = nDotVp != 0. ? 1.:0.;
  float e = pow(max(dot(n, lightSource.halfVector.xyz), 0.), mat.shininess);
  res += att*e*fi*lightProduct.specular;

  return res;
}

vec4 VVizComputeBackColor(vec3 n, vec4 col)
{
  vec4 res = gl_BackLightModelProduct.sceneColor;

  for(int i = 0; i < VVizNumLights; i++)
    res += VVizLightingInternal(i, n, col, gl_BackLightProduct[i], gl_LightSource[i], gl_BackMaterial);
  res.w = col.w;

  return res;
}

vec4 VVizComputeFrontColor(vec3 n, vec4 col)
{
  vec4 res = gl_FrontLightModelProduct.sceneColor;

  for(int i = 0; i < VVizNumLights; i++)
    res += VVizLightingInternal(i, n, col, gl_FrontLightProduct[i], gl_LightSource[i], gl_FrontMaterial);
  res.w = col.w;

  return res;
}

