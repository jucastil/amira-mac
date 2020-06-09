//uniforms for gpu slice generation
uniform vec3 VVizTileTranslation;

uniform float VVizDistStart;
uniform float VVizDistInc;

uniform float VVizGenVertices;

uniform int VVizVertPermutations[64];
uniform int VVizFrontVertIdx;
uniform vec2 VVizPathVertices[24];
uniform vec3 VVizTileVertices[8];

uniform vec3 VVizSliceNormal;

/**
 * Generate slice on GPU
 */
vec4 VVizGenerateVertexInternal()
{
  vec3 zAxis = normalize(VVizSliceNormal);
  float d = VVizDistStart+gl_Vertex.y*VVizDistInc;

  vec4 VVizVertex = vec4(0., 0., 0., 1.);
  if ( VVizGenVertices != 1.0 )
  {
    VVizVertex = gl_Vertex;
    return gl_Vertex;
  }

  for(int edge = 0; edge < 4; edge++)
  {
    vec2 pathEdge = VVizPathVertices[int(gl_Vertex.x*4.)+edge];
    int v1Idx = VVizVertPermutations[VVizFrontVertIdx*8+int(pathEdge.x)];
    int v2Idx = VVizVertPermutations[VVizFrontVertIdx*8+int(pathEdge.y)];

    vec3 v1 = VVizTileVertices[v1Idx];
    vec3 v2 = VVizTileVertices[v2Idx];

    vec3 vStart = v1+VVizTileTranslation;
    vec3 vDir = v2-v1;
    float denom = dot(vDir, zAxis);
    float lambda = -1.;
    if(denom != 0.)
      lambda = (d-dot(vStart, zAxis))/denom;

    if(lambda >= 0. && lambda <=1.)
    {
      VVizVertex = vec4(vStart+lambda*vDir, 1.);
      break;
    }
  }

  if ( VVizGenVertices != 1.0 )
    VVizVertex = gl_Vertex;

  return VVizVertex;
}

