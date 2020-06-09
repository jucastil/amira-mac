#ifndef VVIZ_DATARGBA
#define VVizDefaultData VVIZ_DATATYPE(0.0)
#else
#define VVizDefaultData VVIZ_DATATYPE(0,0,0,1)
#endif

uniform sampler2D VVizData2D;

uniform vec3 VVizDu;
uniform vec3 VVizDv;
uniform vec3 VVizDw;

vec4 VVizComputeMinMaxTexCoord(vec2 tcoord);

vec4 VVizMinMaxTcoord;

const float K = 1.5811388300842;//length(vec2(0.5, 1.5));

VVIZ_DATATYPE
VVizTextureData(sampler2D data, vec2 coord)
{
#ifndef VVIZ_DATARGBA
  return texture2D(data, coord).w;
#else
  return texture2D(data, coord);
#endif
}

VVIZ_DATATYPE fetchData(sampler2D tex, vec2 texUVInt, vec2 offset)
{
  vec2 tcoord = (texUVInt - (offset - 0.5)) * vec2(VVizDu.x, VVizDv.y);
  tcoord = clamp(tcoord, VVizMinMaxTcoord.xy, VVizMinMaxTcoord.zw);

  return VVizTextureData(tex, tcoord);
}

float computeWeight(vec2 texUVFrac, vec2 offset)
{
  float weight = max((K-length(offset - 0.5 + texUVFrac))/K, 0.);
  return weight*weight;
}

VVIZ_DATATYPE VVizGetData(sampler2D tex, vec2 tcoord)
{
  vec2 texUV = tcoord * vec2(1./VVizDu.x, 1./VVizDv.y);
  vec2 texUVFrac = fract(texUV);
  vec2 texUVInt = floor(texUV);

  VVizMinMaxTcoord = VVizComputeMinMaxTexCoord(tcoord);

  VVIZ_DATATYPE v0[4] = VVIZ_DATATYPE[4](fetchData(tex, texUVInt, vec2(-0.5, -1.5)),
                 fetchData(tex, texUVInt, vec2(0.5, -1.5)),
                 fetchData(tex, texUVInt, vec2(-1.5, -0.5)),
                 fetchData(tex, texUVInt, vec2(-0.5, -0.5)));

  VVIZ_DATATYPE v1[4] = VVIZ_DATATYPE[4](fetchData(tex, texUVInt, vec2(0.5, -0.5)),
                 fetchData(tex, texUVInt, vec2(1.5, -0.5)),
                 fetchData(tex, texUVInt, vec2(-1.5,  0.5)),
                 fetchData(tex, texUVInt, vec2(-0.5,  0.5)));

  VVIZ_DATATYPE v2[4] = VVIZ_DATATYPE[4](fetchData(tex, texUVInt, vec2(0.5,  0.5)),
                 fetchData(tex, texUVInt, vec2(1.5,  0.5)),
                 fetchData(tex, texUVInt, vec2(-0.5,  1.5)),
                 fetchData(tex, texUVInt, vec2(0.5,  1.5)));

  vec4 w0 = vec4(computeWeight(texUVFrac, vec2(-0.5, -1.5)),
                 computeWeight(texUVFrac, vec2(0.5, -1.5)),
                 computeWeight(texUVFrac, vec2(-1.5, -0.5)),
                 computeWeight(texUVFrac, vec2(-0.5, -0.5)));

  vec4 w1 = vec4(computeWeight(texUVFrac, vec2(0.5, -0.5)),
                 computeWeight(texUVFrac, vec2(1.5, -0.5)),
                 computeWeight(texUVFrac, vec2(-1.5,  0.5)),
                 computeWeight(texUVFrac, vec2(-0.5,  0.5)));

  vec4 w2 = vec4(computeWeight(texUVFrac, vec2(0.5,  0.5)),
                 computeWeight(texUVFrac, vec2(1.5,  0.5)),
                 computeWeight(texUVFrac, vec2(-0.5,  1.5)),
                 computeWeight(texUVFrac, vec2(0.5,  1.5)));

  float total_weight = dot(w0+w1+w2, vec4(1.));
  VVIZ_DATATYPE total_value = v0[0]*w0[0] + v0[1]*w0[1] + v0[2]*w0[2] + v0[3]*w0[3];
  total_value += v1[0]*w1[0] + v1[1]*w1[1] + v1[2]*w1[2] + v1[3]*w1[3];
  total_value += v2[0]*w2[0] + v2[1]*w2[1] + v2[2]*w2[2] + v2[3]*w2[3];

  return total_value/total_weight;
}

VVIZ_DATATYPE VVizGetData(vec2 tcoord)
{
  return VVizGetData(VVizData2D, tcoord);
}

VVIZ_DATATYPE VVizGetData(vec3 tcoord)
{
  return VVizDefaultData;
}
