varying vec3 VVizTanSpaceLightingVec;
varying vec3 VVizTanSpaceViewVec;

uniform vec3 VVizTangent;
uniform vec3 VVizBinormal;

varying vec3 VVizLightingVec;
varying vec3 VVizViewVec;

void VVizComputeLightingVectors();

void VVizComputeTangentSpaceLightingVectors()
{
  mat3 TBN = mat3(VVizTangent, VVizBinormal, gl_Normal);
  VVizTanSpaceLightingVec = VVizLightingVec*TBN;
  VVizTanSpaceViewVec = VVizViewVec*TBN;
}
