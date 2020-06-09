vec4 VVizLightingInternal(vec3 n, vec4 col, gl_LightProducts lightProduct,
                          gl_LightSourceParameters lightSource,
                          gl_MaterialParameters mat)
{
  vec4 res = vec4(0., 0., 0., 0.);

  vec4 vp;
  //Check for point or directional light
  if ( lightSource.position.w == 0.)
    vp = lightSource.position;
  else
    vp = lightSource.position-gl_ModelViewMatrix*gl_Vertex;

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

  res += VVizLightingInternal(n, col, gl_BackLightProduct[0], gl_LightSource[0], gl_BackMaterial);
  res.w = col.w;

  return res;
}

vec4 VVizComputeFrontColor(vec3 n, vec4 col)
{
  vec4 res = gl_FrontLightModelProduct.sceneColor;

  res += VVizLightingInternal(n, col, gl_FrontLightProduct[0], gl_LightSource[0], gl_FrontMaterial);
  res.w = col.w;

  return res;
}

