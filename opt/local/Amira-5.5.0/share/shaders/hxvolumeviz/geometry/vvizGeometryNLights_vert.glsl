uniform int VVizNumLights;

vec4 VVizLightingVert(int light, vec3 n, vec4 col, gl_LightProducts lightProduct,
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
  res += att*(lightProduct.ambient+max(nDotVp, 0.)*lightSource.diffuse*col);
  float fi = nDotVp != 0. ? 1.:0.;
  float e = pow(max(dot(n, lightSource.halfVector.xyz), 0.), mat.shininess);
  res += att*e*fi*lightProduct.specular;

  return res;
}

vec4 VVizComputeBackColor(vec3 n, vec4 col)
{
  vec4 res = gl_BackLightModelProduct.sceneColor;

#if 1
  // unroll the loop with ternary operator to avoid issue on vp40 profile (FX3500)
  res += ((1<VVizNumLights)?1.:0.)*VVizLightingVert(0, n, col, gl_BackLightProduct[0], gl_LightSource[0], gl_BackMaterial);
  res += ((2<VVizNumLights)?1.:0.)*VVizLightingVert(1, n, col, gl_BackLightProduct[1], gl_LightSource[1], gl_BackMaterial);
  res += ((3<VVizNumLights)?1.:0.)*VVizLightingVert(2, n, col, gl_BackLightProduct[2], gl_LightSource[2], gl_BackMaterial);
  res += ((4<VVizNumLights)?1.:0.)*VVizLightingVert(3, n, col, gl_BackLightProduct[3], gl_LightSource[3], gl_BackMaterial);
  res += ((5<VVizNumLights)?1.:0.)*VVizLightingVert(4, n, col, gl_BackLightProduct[4], gl_LightSource[4], gl_BackMaterial);
  res += ((6<VVizNumLights)?1.:0.)*VVizLightingVert(5, n, col, gl_BackLightProduct[5], gl_LightSource[5], gl_BackMaterial);
  res += ((7<VVizNumLights)?1.:0.)*VVizLightingVert(6, n, col, gl_BackLightProduct[6], gl_LightSource[6], gl_BackMaterial);
  res += ((8<VVizNumLights)?1.:0.)*VVizLightingVert(7, n, col, gl_BackLightProduct[7], gl_LightSource[7], gl_BackMaterial);
#else
  for(int i = 0; i < VVizNumLights; ++i)
    res += VVizLightingVert(0, n, col, gl_BackLightProduct[i], gl_LightSource[i], gl_BackMaterial);
#endif
  res.w = col.w;
  return res;
}

vec4 VVizComputeFrontColor(vec3 n, vec4 col)
{
  vec4 res = gl_FrontLightModelProduct.sceneColor;

#if 1
  // unroll the loop with ternary operator to avoid issue on vp40 profile (FX3500)
  res += ((1<VVizNumLights)?1.:0.)*VVizLightingVert(0, -n, col, gl_FrontLightProduct[0], gl_LightSource[0], gl_FrontMaterial);
  res += ((2<VVizNumLights)?1.:0.)*VVizLightingVert(1, -n, col, gl_FrontLightProduct[1], gl_LightSource[1], gl_FrontMaterial);
  res += ((3<VVizNumLights)?1.:0.)*VVizLightingVert(2, -n, col, gl_FrontLightProduct[2], gl_LightSource[2], gl_FrontMaterial);
  res += ((4<VVizNumLights)?1.:0.)*VVizLightingVert(3, -n, col, gl_FrontLightProduct[3], gl_LightSource[3], gl_FrontMaterial);
  res += ((5<VVizNumLights)?1.:0.)*VVizLightingVert(4, -n, col, gl_FrontLightProduct[4], gl_LightSource[4], gl_FrontMaterial);
  res += ((6<VVizNumLights)?1.:0.)*VVizLightingVert(5, -n, col, gl_FrontLightProduct[4], gl_LightSource[5], gl_FrontMaterial);
  res += ((7<VVizNumLights)?1.:0.)*VVizLightingVert(6, -n, col, gl_FrontLightProduct[6], gl_LightSource[6], gl_FrontMaterial);
  res += ((8<VVizNumLights)?1.:0.)*VVizLightingVert(7, -n, col, gl_FrontLightProduct[7], gl_LightSource[7], gl_FrontMaterial);
#else
  for(int i = 0; i < VVizNumLights; i++)
    res += VVizLightingVert(i, -n, col, gl_FrontLightProduct[i], gl_LightSource[i], gl_FrontMaterial);
#endif
  res.w = col.w;
  return res;
}
