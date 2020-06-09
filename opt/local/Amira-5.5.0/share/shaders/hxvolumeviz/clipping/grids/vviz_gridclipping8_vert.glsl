/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Benjamin GRANGE (Aug 2005)
**=======================================================================*/
/*=======================================================================
* Description : Volume Grid clipping
*========================================================================*/
uniform vec3 VVizUPlan0;
uniform vec3 VVizVPlan0;
uniform vec3 VVizOPlan0;

uniform vec3 VVizUPlan1;
uniform vec3 VVizVPlan1;
uniform vec3 VVizOPlan1;

uniform vec3 VVizUPlan2;
uniform vec3 VVizVPlan2;
uniform vec3 VVizOPlan2;

uniform vec3 VVizUPlan3;
uniform vec3 VVizVPlan3;
uniform vec3 VVizOPlan3;

uniform vec3 VVizUPlan4;
uniform vec3 VVizVPlan4;
uniform vec3 VVizOPlan4;

uniform vec3 VVizUPlan5;
uniform vec3 VVizVPlan5;
uniform vec3 VVizOPlan5;

uniform vec3 VVizUPlan6;
uniform vec3 VVizVPlan6;
uniform vec3 VVizOPlan6;

uniform vec3 VVizUPlan7;
uniform vec3 VVizVPlan7;
uniform vec3 VVizOPlan7;

varying vec3 VVizPlanDist0;
varying vec3 VVizPlanDist1;
varying vec3 VVizPlanDist2;
varying vec3 VVizPlanDist3;
varying vec3 VVizPlanDist4;
varying vec3 VVizPlanDist5;
varying vec3 VVizPlanDist6;
varying vec3 VVizPlanDist7;

// ret.xy = parametric coordinate of the projection of vertex
// on the plane
// ret.z = distance between vertex and the plane
vec3 VVizCalcDistToPlan(vec4 vertex, vec3 uAxis, vec3 vAxis, vec3 origin)
{
  vec3 ret;
  vec3 N = normalize(cross(uAxis, vAxis));

  vec3 toProj = vertex.xyz-origin;
  ret.x = dot(toProj, uAxis)/dot(uAxis, uAxis);
  ret.y = dot(toProj, vAxis)/dot(vAxis, vAxis);
  float d = -dot(N, origin);

  ret.z = dot(vertex, vec4(N,d));

  return ret;
}

void VVizCalcDistToUniformGrid(vec4 vertex)
{
  VVizPlanDist0 = VVizCalcDistToPlan(vertex, VVizUPlan0, VVizVPlan0, VVizOPlan0);
  VVizPlanDist1 = VVizCalcDistToPlan(vertex, VVizUPlan1, VVizVPlan1, VVizOPlan1);
  VVizPlanDist2 = VVizCalcDistToPlan(vertex, VVizUPlan2, VVizVPlan2, VVizOPlan2);
  VVizPlanDist3 = VVizCalcDistToPlan(vertex, VVizUPlan3, VVizVPlan3, VVizOPlan3);
  VVizPlanDist4 = VVizCalcDistToPlan(vertex, VVizUPlan4, VVizVPlan4, VVizOPlan4);
  VVizPlanDist5 = VVizCalcDistToPlan(vertex, VVizUPlan5, VVizVPlan5, VVizOPlan5);
  VVizPlanDist6 = VVizCalcDistToPlan(vertex, VVizUPlan6, VVizVPlan6, VVizOPlan6);
  VVizPlanDist7 = VVizCalcDistToPlan(vertex, VVizUPlan7, VVizVPlan7, VVizOPlan7);
}

