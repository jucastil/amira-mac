uniform vec3 VVizDu;
uniform vec3 VVizDv;
uniform vec3 VVizDw;

VVIZ_DATATYPE VVizCombineData(vec3 tcoord);
VVIZ_DATATYPE VVizGetData(sampler3D tex, vec3 tcoord);
float VVizGetLuminance(VVIZ_DATATYPE rgba);

vec3 VVizComputeGradient(vec3 tcoord)
{
  vec3 G;
  float a00 = VVizGetLuminance(VVizCombineData(tcoord));
  G.x = a00-VVizGetLuminance(VVizCombineData(tcoord+VVizDu));
  G.y = a00-VVizGetLuminance(VVizCombineData(tcoord+VVizDv));
  G.z = a00-VVizGetLuminance(VVizCombineData(tcoord+VVizDw));

  G *= 1./sqrt(3.);

  return G;
}

vec3 VVizComputeGradient(sampler3D tex, vec3 tcoord)
{
  vec3 G;
  float a00 = VVizGetLuminance(VVizGetData(tex, tcoord));
  G.x = a00-VVizGetLuminance(VVizGetData(tex, tcoord+VVizDu));
  G.y = a00-VVizGetLuminance(VVizGetData(tex, tcoord+VVizDv));
  G.z = a00-VVizGetLuminance(VVizGetData(tex, tcoord+VVizDw));

  G *= 1./sqrt(3.);

  return G;
}
