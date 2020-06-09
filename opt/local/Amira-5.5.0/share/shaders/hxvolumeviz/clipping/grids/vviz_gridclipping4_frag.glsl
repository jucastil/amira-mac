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

// Grid1 parameters
uniform sampler2D VVizClipMap1;
uniform float VVizZScale1;
uniform float VVizClipThickness1;
uniform int VVizClipBelowMode1;
uniform int VVizClipAboveMode1;
uniform int VVizClipRevertMode1;
varying vec3 VVizPlanDist1;

// Grid2 parameters
uniform sampler2D VVizClipMap2;
uniform float VVizZScale2;
uniform float VVizClipThickness2;
uniform int VVizClipBelowMode2;
uniform int VVizClipAboveMode2;
uniform int VVizClipRevertMode2;
varying vec3 VVizPlanDist2;

// Grid3 parameters
uniform sampler2D VVizClipMap3;
uniform float VVizZScale3;
uniform float VVizClipThickness3;
uniform int VVizClipBelowMode3;
uniform int VVizClipAboveMode3;
uniform int VVizClipRevertMode3;
varying vec3 VVizPlanDist3;

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
  if (VVizIsInNormalizedRange(VVizPlanDist1.xy))
  {
    // NOTHING
  }
  else
  {
    discard;
  }
  if (VVizIsInNormalizedRange(VVizPlanDist2.xy))
  {
    // NOTHING
  }
  else
  {
    discard;
  }
  if (VVizIsInNormalizedRange(VVizPlanDist3.xy))
  {
    // NOTHING
  }
  else
  {
    discard;
  }

  // Check and get z distance to plan
  float elevation0 = VVizCheckClippingElevation(VVizPlanDist0, VVizZScale0, VVizClipMap0, VVizClipRevertMode0);
  float elevation1 = VVizCheckClippingElevation(VVizPlanDist1, VVizZScale1, VVizClipMap1, VVizClipRevertMode1);
  float elevation2 = VVizCheckClippingElevation(VVizPlanDist2, VVizZScale2, VVizClipMap2, VVizClipRevertMode2);
  float elevation3 = VVizCheckClippingElevation(VVizPlanDist3, VVizZScale3, VVizClipMap3, VVizClipRevertMode3);

  // clip below or above taking in account thickness
  VVizClipGrid(elevation0, VVizZScale0, VVizClipAboveMode0, VVizClipBelowMode0, VVizClipThickness0);
  VVizClipGrid(elevation1, VVizZScale1, VVizClipAboveMode1, VVizClipBelowMode1, VVizClipThickness1);
  VVizClipGrid(elevation2, VVizZScale2, VVizClipAboveMode2, VVizClipBelowMode2, VVizClipThickness2);
  VVizClipGrid(elevation3, VVizZScale3, VVizClipAboveMode3, VVizClipBelowMode3, VVizClipThickness3);
}

