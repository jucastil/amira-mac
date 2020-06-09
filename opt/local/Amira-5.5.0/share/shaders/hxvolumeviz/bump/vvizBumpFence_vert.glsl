varying vec3 VVizEyeNormal;
varying vec3 VVizEyeViewVec;

void VVizComputeTangentSpaceLightingVectors()
{
  vec4 ePosition = gl_ModelViewMatrix*gl_Vertex;
  vec4 eLightPosition = gl_LightSource[0].position;

  VVizEyeNormal = gl_NormalMatrix*gl_Normal;
  VVizEyeViewVec = normalize(-ePosition.xyz);
}
