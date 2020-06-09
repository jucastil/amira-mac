varying vec3 VVizEyeNormal;
varying vec3 VVizEyeViewVec;

uniform vec3 VVizDu;
uniform vec3 VVizDv;

VVIZ_DATATYPE VVizCombineData(vec2 tcoord);
float VVizGetLuminance(VVIZ_DATATYPE data);
void VVizOutputColor(vec4 color);

varying vec3 VVizVertexV;
varying vec3 VVizEyePos;

vec4 VVizLightingFence(vec3 n, vec4 col, float gradLen)
{
  vec4 res = gl_FrontLightModelProduct.sceneColor;

  vec4 l = normalize(gl_LightSource[0].position);

  float nDotL = dot(n, l.xyz);
  float fi = ( nDotL != 0. ) ? 1.:0.;

  if ( gradLen < 0.0001 )
  {
    nDotL = 1.;
    fi = 0.;
  }

  res += (gl_FrontLightProduct[0].ambient+max(nDotL, 0.)*gl_LightSource[0].diffuse*col);
  float e = pow(max(dot(n, gl_LightSource[0].halfVector.xyz), 0.), gl_FrontMaterial.shininess);
  res += e*fi*gl_FrontLightProduct[0].specular;
  res.w = col.w;

  return res;
}

void VVizComputeNormalFence(in float bumpScale, out vec3 tNormal, out float gradLen)
{
  vec3 feNormal = normalize(VVizEyeNormal);

  float diffuseCoeff;
  float specularCoeff;

  VVIZ_DATATYPE vox = VVizCombineData(gl_TexCoord[0].st);

  tNormal.x = (VVizGetLuminance(VVizCombineData(gl_TexCoord[0].xy+VVizDu.xy))-VVizGetLuminance(VVizCombineData(gl_TexCoord[0].xy-VVizDu.xy)))*bumpScale;
  tNormal.y = (VVizGetLuminance(VVizCombineData(gl_TexCoord[0].xy+VVizDv.xy))-VVizGetLuminance(VVizCombineData(gl_TexCoord[0].xy-VVizDv.xy)))*bumpScale;
  tNormal.z = vox;
  if(tNormal == vec3(0., 0., 0.))
    tNormal = vec3(0., 0., 1.);

  gradLen = length(tNormal);
  tNormal /= gradLen;

  // the following code are far-fetched computations to get an estimation of the direction of
  // the s direction (evolution of the s texture coordinate) in eye space, to get a consistent tangent system
  vec2 deTangent    = vec2(dFdx(gl_TexCoord[0].s),  dFdy(gl_TexCoord[0].s));
  vec2 deZ          = vec2(dFdx(gl_FragCoord.z), dFdy(gl_FragCoord.z));
  vec3 tempeTangent = vec3(deTangent, deTangent.x * -deZ.x + deTangent.y * -deZ.y);
  vec3 temp         = cross(tempeTangent, feNormal);
  vec3 eTangent     = cross(feNormal, temp);

  eTangent  = normalize(eTangent);
  vec3 eBinormal = cross(feNormal, eTangent);

  mat3 TBN = mat3(eTangent, eBinormal, feNormal);

  vec3 tView = normalize(VVizEyeViewVec);

  tNormal = TBN*tNormal;

  //double face lighting
  tNormal = -faceforward(tNormal, tView, feNormal);
}

vec4 VVizBumpSlice(vec4 col, float bumpScale)
{
  vec3 n;
  float gradLen;
  VVizComputeNormalFence(bumpScale, n, gradLen);
  return VVizLightingFence(n, col, gradLen);
}
