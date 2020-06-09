//Recycle unusued varying
#define eNormal VVizLightingVec
#define view VVizViewVec
#define mvLightv VVizHalfVec

uniform sampler2D VVizTransfer;

varying vec3 eNormal;       // Normal in eye space
varying vec3 view;
varying vec4 mvLightv;       // Vertex to light vector in eye space

uniform float VVizScale;
uniform vec4 VVizDuDv;

VVIZ_DATATYPE VVizCombineData(vec2 tcoord);
float VVizGetLuminance(VVIZ_DATATYPE data);
vec4 VVizComputeVolumeRendering(VVIZ_DATATYPE sf);
void VVizOutputColor(vec4 color);
void VVizClipVoxel();

void main()
{
  VVizClipVoxel();

  vec3 feNormal       = normalize(eNormal);

  vec2 newTexCoord = gl_TexCoord[0].st;

  float diffuseCoeff;
  float specularCoeff;

  VVIZ_DATATYPE vox = VVizCombineData(newTexCoord);

  vec3 tNormal;
  tNormal.x = (VVizGetLuminance(VVizCombineData(gl_TexCoord[0].xy-VVizDuDv.xy))-VVizGetLuminance(VVizCombineData(gl_TexCoord[0].xy+VVizDuDv.xy)))*VVizScale;
  tNormal.y = (VVizGetLuminance(VVizCombineData(gl_TexCoord[0].xy-VVizDuDv.zw))-VVizGetLuminance(VVizCombineData(gl_TexCoord[0].xy+VVizDuDv.zw)))*VVizScale;
  tNormal.z = VVizGetLuminance(vox);
  float lenN = length(tNormal);
  tNormal = tNormal/lenN;

  vec4 indColor = VVizComputeVolumeRendering(vox);

  // the following code are far-fetched computations to get an estimation of the direction of
  // the s direction (evolution of the s texture coordinate) in eye space, to get a consistent tangent system
  vec2 deTangent    = vec2(dFdx(newTexCoord.s),  dFdy(newTexCoord.s));
  vec2 deZ          = vec2(dFdx(gl_FragCoord.z), dFdy(gl_FragCoord.z));
  vec3 tempeTangent = vec3(deTangent, deTangent.x * -deZ.x + deTangent.y * -deZ.y);
  vec3 temp         = cross(tempeTangent, feNormal);
  vec3 eTangent     = cross(feNormal, temp);

  eTangent  = normalize(eTangent);
  vec3 eBinormal = cross(feNormal, eTangent);

  mat3 TBN = mat3(eTangent, eBinormal, feNormal);

  vec3 tLightv =  normalize(mvLightv.xyz);
  vec3 tView = normalize(view);

  tNormal = TBN*tNormal;

  vec3 H = normalize(tLightv+tView);

  //double face lighting
  tNormal = -faceforward(tNormal, tView, feNormal);

  float d = dot(tNormal, tLightv);
  float s = d<=0.?0.:pow(max(dot(tNormal, normalize(H)), 0.), gl_FrontMaterial.shininess);

  if ( lenN < 0.0001 )
    d = s = 0.;

  vec3 diffuse = d*indColor.xyz*gl_FrontMaterial.diffuse.xyz;
  vec3 specular = s*gl_FrontMaterial.specular.xyz;
  vec3 ambient = gl_FrontMaterial.ambient.xyz*indColor.xyz;
  vec3 emission = gl_FrontMaterial.emission.xyz+vec3(1., 1., 1.);

  specularCoeff = max(dot(tLightv, normalize(H)), 0.);

  vec4 res;
  res.xyz  =  (ambient+diffuse+specular)*emission;
  res.w = indColor.w*gl_FrontMaterial.diffuse.w;

  VVizOutputColor(res);
}
