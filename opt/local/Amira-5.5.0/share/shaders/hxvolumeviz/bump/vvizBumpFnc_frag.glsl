varying vec3 VVizTanSpaceLightingVec;
varying vec3 VVizTanSpaceViewVec;

uniform vec3 VVizDu;
uniform vec3 VVizDv;

VVIZ_DATATYPE VVizCombineData(vec2 tcoord);
float VVizGetLuminance(VVIZ_DATATYPE rgba);

vec4 VVizBumpSlice(vec4 col, float bumpScale)
{
  vec4 res;
  //Normalize
  vec3 light = normalize(VVizTanSpaceLightingVec);
  vec3 view = normalize(VVizTanSpaceViewVec);

  vec3 N;
  N.x = (VVizGetLuminance(VVizCombineData(gl_TexCoord[0].xy+VVizDu.xy))-VVizGetLuminance(VVizCombineData(gl_TexCoord[0].xy-VVizDu.xy)))*bumpScale;
  N.y = (VVizGetLuminance(VVizCombineData(gl_TexCoord[0].xy+VVizDv.xy))-VVizGetLuminance(VVizCombineData(gl_TexCoord[0].xy-VVizDv.xy)))*bumpScale;
  N.z = VVizGetLuminance(VVizCombineData(gl_TexCoord[0].xy));  
  float lenN = length(N);
  N = N/lenN;

  if ( lenN < 0.0001 )
    N = vec3(0, 0, 1);

  //Flip normal if it doesn't face the viewer
  if(N.z*view.z<0.)
    N = -N;

  //Compute diffuse and specular
  float d = dot(N, light);
  vec3 H = normalize(light+view);
  float s = d<0.?0.:pow(max(dot(N, H), 0.), gl_FrontMaterial.shininess);
  vec3 diffuse = col.xyz*gl_FrontMaterial.diffuse.xyz;
  vec3 ambient = gl_FrontMaterial.ambient.xyz;
  vec3 emission = gl_FrontMaterial.emission.xyz+vec3(1., 1., 1.);
  vec3 specular = gl_FrontMaterial.specular.xyz;

  res.xyz = (ambient*col.xyz+d*diffuse+s*specular)*emission;
  res.w = col.w;

  return res;
}


