vec4 VVizLightingVert(vec3 n, vec4 col)
{
  vec4 res = gl_FrontLightModelProduct.sceneColor;

  vec4 vp = normalize(gl_LightSource[0].position);

  float nDotVp = dot(n, vp.xyz);

  res += (gl_FrontLightProduct[0].ambient+max(nDotVp, 0.)*gl_LightSource[0].diffuse*col);
  float fi = nDotVp != 0. ? 1.:0.;
  float e = pow(max(dot(n, gl_LightSource[0].halfVector.xyz), 0.), gl_FrontMaterial.shininess);
  res += e*fi*gl_FrontLightProduct[0].specular;
  res.w = col.w;

  return res;
}

vec4 VVizComputeFrontColor(vec3 normal, vec4 color)
{
  return VVizLightingVert(normal, color);
}

vec4 VVizComputeBackColor(vec3 normal, vec4 color)
{
  return color;
}
