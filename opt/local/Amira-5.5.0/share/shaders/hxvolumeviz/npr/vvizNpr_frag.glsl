vec4 VVizEdgeColoring(vec4 fragColor, vec3 viewVec, vec3 normal, float gradNorm);
vec3 VVizComputeGradient(vec3 tcoord);
vec3 VVizComputeNormal(vec3 view, vec3 grad);
vec4 VVizBoundaryOpacity(vec4 fragColor, float gradNorm);
vec4 VVizEdgeImageSpace(vec4 fragColor, vec3 viewVec, vec3 normal, float gradNorm);

varying vec3 VVizViewVec;

vec4 VVizApplyNpr(vec4 fragColor, vec3 viewVec, vec3 grad,
                  float gradNorm, vec3 normal)
{
  fragColor = VVizEdgeColoring(fragColor, viewVec, normal, gradNorm);
  fragColor = VVizBoundaryOpacity(fragColor, gradNorm);
  fragColor = VVizEdgeImageSpace(fragColor, viewVec, grad, gradNorm);

  return fragColor;
}

vec4 VVizApplyNpr(vec4 fragColor, vec3 tcoord)
{
#ifdef VVIZ_NPR_USE_GRADIENT
  vec3 viewVec = normalize(VVizViewVec);
  vec3 grad = VVizComputeGradient(tcoord);
  float gradNorm = length(grad);
  vec3 normal = VVizComputeNormal(viewVec, grad);
#else
  vec3 viewVec = vec3(1.);
  vec3 grad = vec3(1.);
  float gradNorm = 0.;
  vec3 normal = vec3(1.);
#endif

  fragColor = VVizEdgeColoring(fragColor, viewVec, normal, gradNorm);
  fragColor = VVizBoundaryOpacity(fragColor, gradNorm);
  fragColor = VVizEdgeImageSpace(fragColor, viewVec, grad, gradNorm);

  return fragColor;
}
