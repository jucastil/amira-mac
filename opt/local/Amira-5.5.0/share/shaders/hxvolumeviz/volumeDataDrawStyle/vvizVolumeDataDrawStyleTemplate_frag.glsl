uniform sampler3D VVIZDATASET;
uniform int VVIZRENDERSTYLE;

int VVizGetMaskDATASETID(vec3 tcoord)
{
  //Use ternary operator to avoid triggering software fallback on apple non dx10 cards
  return VVizUseVolumeMask?int(texture3D(VVizDataMask, tcoord).w*255.):DATASETID;
}

vec4 VVizComputeVVizDataDrawStyleDATASETID()
{
  if ( VVIZRENDERSTYLE == VVIZ_DRAWSTYLE_NONE )
    discard;

  bool hasVR = mod(float(VVIZRENDERSTYLE), 2.) == 1.;
	
  vec3 tcoord0 = VVizComputeCoordinates(gl_TexCoord[0].xyz);
  vec3 tcoord1 = VVizComputeCoordinates(gl_TexCoord[1].xyz);

  VVIZ_DATATYPE sf = VVizGetData(VVIZDATASET, tcoord0);
#if VVIZ_DRAWSTYLE_USE_PREINT || VVIZ_DRAWSTYLE_ISOSURFACE
  VVIZ_DATATYPE sb = VVizGetData(VVIZDATASET, tcoord1);
#endif

#if VVIZ_DRAWSTYLE_USE_LIGHTING
  vec3 viewVec;
  vec3 grad;
  float gradLength = 1.0;
  vec3 normal=vec3(0.,0.,1.);
  if ( hasVR )
  {
    viewVec = VVizComputeViewVec();
    #if VVIZ_DRAWSTYLE_USE_PREINT
      grad = VVizComputePreintegratedGradient(VVIZDATASET, tcoord0, tcoord1);
    #else //VVIZ_DRAWSTYLE_USE_PREINT
      grad = VVizComputeGradient(VVIZDATASET, tcoord0);
    #endif //VVIZ_DRAWSTYLE_USE_PREINT
    gradLength = length(grad);
    normal = VVizComputeNormal(viewVec, grad);
  }
#endif //VVIZ_DRAWSTYLE_USE_LIGHTING

  vec4 fragColor = vec4(0.);
  int mask = VVizGetMaskDATASETID(tcoord0);

  if ( hasVR )
  {
    vec4 vrFrag = fragColor;
#if VVIZ_DRAWSTYLE_USE_PREINT
    vrFrag = VVizComputePreIntegrated(sf, sb, mask);
  #if VVIZ_DRAWSTYLE_USE_LIGHTING
    vrFrag = VVizComputePreintegratedLighting(vrFrag, normal, gradLength);
  #endif
#else //VVIZ_DRAWSTYLE_USE_PREINT
    vrFrag = VVizComputeVolumeRendering(sf, mask);
  #if VVIZ_DRAWSTYLE_USE_LIGHTING
    vrFrag = VVizComputeVolumeRenderingLighting(vrFrag, normal, gradLength);
  #endif
#endif //VVIZ_DRAWSTYLE_USE_PREINT
    fragColor = vrFrag;
  }

#if VVIZ_DRAWSTYLE_ISOSURFACE
  //Isorendering
  if ( VVIZRENDERSTYLE >= 4 )
  {
  #if VVIZ_DRAWSTYLE_SEGMENTED_INTERPOLATION
    vec4 isoFrag = VVizComputeGeobodies(VVIZDATASET, DATASETID, tcoord0, tcoord1);
  #else
    vec4 isoFrag = VVizComputeIsoMaterial(VVIZDATASET, sf, sb, DATASETID);
  #endif //VVIZ_DRAWSTYLE_SEGMENTED_INTERPOLATION
    fragColor = VVizOverOperator(fragColor, isoFrag);
  }
#endif

#if VVIZ_DRAWSTYLE_USE_LIGHTING
  if ( hasVR )
    fragColor = VVizApplyNpr(fragColor, viewVec, grad, gradLength, normal);
  else
    fragColor = VVizApplyNpr(fragColor, tcoord0);
#else
  fragColor = VVizApplyNpr(fragColor, tcoord0);
#endif
  fragColor = VVizApplyBoundary(fragColor, mask, tcoord0, tcoord1);

  return fragColor;
}

