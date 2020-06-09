uniform vec3 VVizDu;
uniform vec3 VVizDv;
uniform vec3 VVizDw;

VVIZ_DATATYPE VVizCombineData(vec3 tcoord);
VVIZ_DATATYPE VVizGetData(sampler3D tex, vec3 tcoord);
float VVizGetLuminance(VVIZ_DATATYPE rgba);

vec3 VVizComputeGradient(vec3 tcoord)
{
  vec3 G;
  G.x = VVizGetLuminance(VVizCombineData(tcoord+VVizDu))-VVizGetLuminance(VVizCombineData(tcoord-VVizDu));
  G.y = VVizGetLuminance(VVizCombineData(tcoord+VVizDv))-VVizGetLuminance(VVizCombineData(tcoord-VVizDv));
  G.z = VVizGetLuminance(VVizCombineData(tcoord+VVizDw))-VVizGetLuminance(VVizCombineData(tcoord-VVizDw));

  G *= 1./sqrt(3.);
  
  return G;
}

vec3 VVizComputeGradient(sampler3D tex, vec3 tcoord)
{
  vec3 G;
  G.x = VVizGetLuminance(VVizGetData(tex,tcoord+VVizDu))-VVizGetLuminance(VVizGetData(tex,tcoord-VVizDu));
  G.y = VVizGetLuminance(VVizGetData(tex,tcoord+VVizDv))-VVizGetLuminance(VVizGetData(tex,tcoord-VVizDv));
  G.z = VVizGetLuminance(VVizGetData(tex,tcoord+VVizDw))-VVizGetLuminance(VVizGetData(tex,tcoord-VVizDw));

  G *= 1./sqrt(3.);

  return G;
}
