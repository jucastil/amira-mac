/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Benjamin GRANGE (Aug 2005)
** Modified    : David Beilloin (Mar 2011)
**=======================================================================*/
/*=======================================================================
* Description : Volume clipping
*========================================================================*/

void VVizClipGeometry();
void VVizClipVolumeGrid();

void VVizClipVoxel()
{
  VVizClipGeometry();
  VVizClipVolumeGrid();
}

// precision correction 
// Used by VVizClipVolumeGrid function
#define GRID_HEIGHT_EPSILON 0.0015

// Used by VVizClipVolumeGrid function
bool VVizIsInNormalizedRange(in vec2 coord)
{
  return all(greaterThanEqual(coord,vec2(0,0))) && all(lessThanEqual(coord,vec2(1,1)));
}

// Used by VVizClipVolumeGrid function
float VVizCheckClippingElevation(in vec3 PlanDist, in float ZScale, in sampler2D ClipMap, in int RevertMode)
{
  // Get elevation map values
  float elevationValue = texture2D(ClipMap, PlanDist.xy).x;

  if (RevertMode != 0)
    elevationValue = (1.0f-elevationValue);

  if ( RevertMode!= 0 && elevationValue <= 0)
    discard;

  // return the final distance to plan
  return PlanDist.z - elevationValue*ZScale;
}

// Used by VVizClipVolumeGrid function
void VVizClipGrid(in float Distance, in float ZScale, in int ClipAbove, in int ClipBelow, in float ClipThickness)
{
  float upperDist= ClipAbove*(Distance - ClipThickness + (GRID_HEIGHT_EPSILON*ZScale));
  if ( upperDist > 0 )
    discard;
  float lowerDist= ClipBelow*(Distance + ClipThickness -(GRID_HEIGHT_EPSILON*ZScale));
  if ( lowerDist < 0 )
    discard;
}
