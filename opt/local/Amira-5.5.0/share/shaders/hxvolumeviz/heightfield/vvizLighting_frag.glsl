uniform bool OivTwoSidedLighting;
uniform bool OivCCW;
uniform bool OivModelMatrixRightHanded;

vec4 VVizComputeFrontColor(vec3 n, vec4 col);
vec4 VVizComputeBackColor(vec3 n, vec4 col);

vec4 VVizComputeLighting(vec3 normal, vec4 col)
{
  bool frontFacing = !(gl_FrontFacing^^OivModelMatrixRightHanded);
  if ( OivTwoSidedLighting )
  {
    if ( !(frontFacing^^OivCCW) )
      return VVizComputeFrontColor(normal, col);
     else
      return VVizComputeBackColor(-normal, col);
  } else if ( frontFacing )
    return VVizComputeFrontColor(normal, col);

  return vec4(0., 0., 0., col.w);
}
