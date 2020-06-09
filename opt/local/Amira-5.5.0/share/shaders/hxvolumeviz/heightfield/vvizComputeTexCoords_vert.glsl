uniform vec4 VVizGridScaleTranslate;
uniform vec4 VVizGridUvScaleTranslate;

void VVizComputeTexCoord()
{ 
 vec2 uv = VVizGridUvScaleTranslate.xy*gl_Vertex.xy+VVizGridUvScaleTranslate.zw;
 gl_TexCoord[0].xy = uv;
}
