vec4 VVizLighting(vec3 n, vec4 col)
{
  vec4 res = gl_FrontLightModelProduct.sceneColor;

  vec4 lDir;
  lDir = normalize(gl_LightSource[0].position);
  float nDotL = dot(n, lDir.xyz);

  res += (gl_FrontLightProduct[0].ambient+max(nDotL, 0.)*gl_LightSource[0].diffuse*col);
  float fi = nDotL != 0. ? 1.:0.;
  float e = pow(max(dot(n, gl_LightSource[0].halfVector.xyz), 0.), gl_FrontMaterial.shininess);
  res += e*fi*gl_FrontLightProduct[0].specular;

  return res;
}

