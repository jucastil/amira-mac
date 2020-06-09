uniform vec4 VVizGridScaleTranslate;
uniform vec4 VVizGridUvScaleTranslate;

uniform sampler2D VVizGeomTexture;
uniform float VVizUndefinedValue;

/**
 * Generate slice on GPU
 */
vec4 VVizGenerateVertexInternal()
{
  vec3 vertex;
  vec2 uv = VVizGridUvScaleTranslate.xy*gl_Vertex.xy+VVizGridUvScaleTranslate.zw;

  vertex.xy = VVizGridScaleTranslate.xy*gl_Vertex.xy+VVizGridScaleTranslate.zw;
  float height = texture2DLod(VVizGeomTexture, uv, 0.0).x;
 // height = 0.;
  vertex.z = height;

  //Put texture value in z coordinate in order to avoid reading texture in geometry shader
  gl_TexCoord[0].z = height;

  return vec4(vertex.xyz, 1.);
}
