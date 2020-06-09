//Recycle unusued varying
#define eNormal VVizLightingVec
#define view VVizViewVec
#define mvLightv VVizHalfVec

void VVizComputeBackSliceTexCoord();
void VVizComputeFrontSliceTexCoord();
void VVizComputeLightingVectors();
void VVizComputeTangentSpaceLightingVectors();
void VVizCalcDistToUniformGrid(vec4 vertex);
vec4 VVizGenerateVertex();

varying vec3 eNormal;
varying vec3 view;
varying vec4 mvLightv;

void main()
{
  vec4 vertex = VVizGenerateVertex();
  VVizComputeBackSliceTexCoord();
  VVizComputeFrontSliceTexCoord();
  VVizComputeLightingVectors();
  VVizComputeTangentSpaceLightingVectors();
  VVizCalcDistToUniformGrid(gl_ModelViewMatrix*vertex);

  // Output vertex position
  gl_Position = gl_ModelViewProjectionMatrix * vertex;

  vec4 ePosition      = gl_ModelViewMatrix * vertex;
  vec4 eLightPosition = gl_LightSource[0].position;
  eNormal        = gl_NormalMatrix * gl_Normal;

  view = -ePosition.xyz;
  mvLightv.xyz = normalize(gl_LightSource[0].position.xyz);

  gl_TexCoord[0] = gl_MultiTexCoord0;
  gl_FrontColor = gl_Color;
#ifndef OIV_USE_ATI
  gl_ClipVertex = gl_ModelViewMatrix*vertex;
#endif
}
