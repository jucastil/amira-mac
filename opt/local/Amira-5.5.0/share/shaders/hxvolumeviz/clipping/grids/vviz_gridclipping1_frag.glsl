/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Benjamin GRANGE (Aug 2005)
** Modified    : David Beilloin (Mar 2011)
**=======================================================================*/
/*=======================================================================
* Description : Volume Grid clipping
* File generated with /Common/bin/shader/genExternalGridFragShader.sh
*========================================================================*/

// forward declaration
bool VVizIsInNormalizedRange(in vec2 coord);
float VVizCheckClippingElevation(in vec3 PlanDist, in float ZScale, in sampler2D ClipMap, in int RevertMode);
void VVizClipGrid(in float Distance, in float ZScale, in int ClipAbove, in int ClipBelow, in float ClipThickness);

// Grid0 parameters
uniform sampler2D VVizClipMap0;
uniform float VVizZScale0;
uniform float VVizClipThickness0;
uniform int VVizClipBelowMode0;
uniform int VVizClipAboveMode0;
uniform int VVizClipRevertMode0;
varying vec3 VVizPlanDist0;

void VVizClipVolumeGrid()
{
  // Check if projected coord are in the bounds of the plane
  if (VVizIsInNormalizedRange(VVizPlanDist0.xy))
  {
    // NOTHING
  }
  else
  {
    discard;
  }

  // Check and get z distance to plan
  float elevation0 = VVizCheckClippingElevation(VVizPlanDist0, VVizZScale0, VVizClipMap0, VVizClipRevertMode0);

  // clip below or above taking in account thickness
  VVizClipGrid(elevation0, VVizZScale0, VVizClipAboveMode0, VVizClipBelowMode0, VVizClipThickness0);
}

