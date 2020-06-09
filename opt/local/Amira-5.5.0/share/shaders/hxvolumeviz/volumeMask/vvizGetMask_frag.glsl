//#version 130

#ifndef VVIZ_DATA2D

uniform sampler3D VVizDataMask;

uniform vec3 VVizTileDimensions;

uniform vec3 VVizDu;
uniform vec3 VVizDv;
uniform vec3 VVizDw;
#endif

//When there is no volume mask, GetMask return VVizDefaultTfId
//which is the first transfer function
uniform int VVizDefaultTfId;

int VVizGetMask(vec3 tcoord)
{
#ifndef VVIZ_DATA2D
  #ifndef VVIZ_USE_VOLUME_MASK
  return VVizDefaultTfId;
  #else
  return int(texture3D(VVizDataMask, tcoord).w*255.);
  #endif // VVIZ_USE_VOLUME_MASK
#else
  return VVizDefaultTfId;
#endif //VVIZ_DATA2D
}


