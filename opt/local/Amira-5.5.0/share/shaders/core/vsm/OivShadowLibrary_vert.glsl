uniform mat4 OivLightViewProjectionMatrix;
uniform mat4 OivModelMatrix;
varying vec4 OivVertexLightSpace;

void OivSetupShadowVertex(vec4 vertex)
{
  OivVertexLightSpace = OivLightViewProjectionMatrix*OivModelMatrix*vertex;
}

void OivSetupShadowVertex()
{
  OivSetupShadowVertex(gl_Vertex);
}
