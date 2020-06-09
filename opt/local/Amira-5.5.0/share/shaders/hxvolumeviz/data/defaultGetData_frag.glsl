#ifndef VVIZ_DATA2D
uniform sampler3D VVizData;
#else
uniform sampler2D VVizData2D;
#endif

#ifndef VVIZ_DATARGBA
#define VVizDefaultData VVIZ_DATATYPE(0.0)
#else
#define VVizDefaultData VVIZ_DATATYPE(0,0,0,1)
#endif

vec2 VVizComputeCoordinates(const vec2 tCoord);

VVIZ_DATATYPE VVizGetData(sampler2D tex, vec2 tcoord)
{
#ifndef VVIZ_DATARGBA
  return texture2D(tex, VVizComputeCoordinates(tcoord)).w;
#else
  return texture2D(tex, VVizComputeCoordinates(tcoord));
#endif
}

VVIZ_DATATYPE VVizGetData(sampler3D tex, vec3 tcoord)
{
#ifndef VVIZ_DATARGBA
  return texture3D(tex, tcoord).w;
#else
  return texture3D(tex, tcoord);
#endif
}

VVIZ_DATATYPE VVizGetData(vec2 tcoord)
{
#ifdef VVIZ_DATA2D
  return VVizGetData(VVizData2D, tcoord);
#else
  return VVizDefaultData;
#endif
}

VVIZ_DATATYPE VVizGetData(vec3 tcoord)
{
#ifndef VVIZ_DATA2D
  return VVizGetData(VVizData, tcoord);
#else
  return VVizDefaultData;
#endif
}
