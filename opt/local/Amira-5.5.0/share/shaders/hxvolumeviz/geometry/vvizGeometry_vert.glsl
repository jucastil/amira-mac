vec4 VVizGenerateVertex();
vec3 VVizComputeTextureCoordinates(vec4 vertex, vec3 normal);
vec4 VVizComputeBackColor(vec3 normal, vec4 color);
vec4 VVizComputeFrontColor(vec3 normal, vec4 color);
void VVizClipVertex(vec4 vertex);

void main()
{
  vec3 n = normalize(gl_NormalMatrix*gl_Normal);
  vec4 vertex = VVizGenerateVertex();
  gl_TexCoord[0].xyz = VVizComputeTextureCoordinates(vertex, n);
  gl_Position = gl_ModelViewProjectionMatrix*vertex;
  gl_FrontColor = VVizComputeFrontColor(n, gl_Color);
  gl_BackColor = VVizComputeBackColor(n, gl_Color);
  VVizClipVertex(vertex);
}
