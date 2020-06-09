uniform sampler2D VVizTransfer;
uniform sampler3D VVizPreIntLut;
uniform float VVizInvTFTexSize;

float VVizGetLuminance(VVIZ_DATATYPE data);

/** 1D transfer function */
vec4 VVizTransferFunction(VVIZ_DATATYPE vox, int num)
{
#ifndef VVIZ_DATARGBA
  float tf = (float(num)+0.5)*VVizInvTFTexSize;
  return texture2D(VVizTransfer, vec2(vox, tf));
#else
  // TODO: we do not support RGBA Transfer function yet
  return vox;
#endif
}

/** Preintegrated transfer function */
vec4 VVizTransferFunction(VVIZ_DATATYPE sf, VVIZ_DATATYPE sb, int num)
{
#ifndef VVIZ_DATARGBA
  float tf = (float(num)+0.5)*VVizInvTFTexSize;
  return texture3D(VVizPreIntLut, vec3(sf, sb, tf));
#else
  // TODO: we do not support RGBA Transfer function yet
  return sf;
#endif  
}
