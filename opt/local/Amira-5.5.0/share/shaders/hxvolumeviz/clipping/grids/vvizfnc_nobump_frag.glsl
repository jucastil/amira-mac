/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Benjamin GRANGE (Aug 2005)
**=======================================================================*/
/*=======================================================================
* Description : Shader library for volume rendering when using uniform grid
*               clipping (allow to spare 2 varyings)
*========================================================================*/
uniform sampler2D VVizIsoLut;
uniform sampler2D VVizMatPal;
uniform sampler2D VVizPreIntLut;
uniform sampler2D VVizTransfer;

uniform vec3 VVizDu;
uniform vec3 VVizDv;
uniform vec3 VVizDw;
uniform float VVizNvidiaWorkAround;

uniform float VViz256OverNumIsos;

varying vec3 VVizLightingVec;
varying vec3 VVizViewVec;
varying vec4 VVizHalfVec;

VVIZ_DATATYPE VVizCombineData(vec3 tcoord);
VVIZ_DATATYPE VVizCombineData(vec2 tcoord);
float VVizGetLuminance(VVIZ_DATATYPE data);

vec4 VVizComputeIsoMaterial(VVIZ_DATATYPE sf, VVIZ_DATATYPE sb)
{
  vec4 res = texture2D(VVizIsoLut, vec2(VVizGetLuminance(sf), VVizGetLuminance(sb)));

  //0=>no visible isosurface
  if(res.w != 0.) {
    //Fetch material
    //|diff|spec|shininess|isoval
    float idx = res.w*VViz256OverNumIsos; //lut*256/NUMISO
    vec4 coeffs = texture2D(VVizMatPal, vec2(2./4., idx));
    vec4 spec = texture2D(VVizMatPal, vec2(1./4., idx));
    vec4 diff = texture2D(VVizMatPal, vec2(0., idx));

    //Find where is the isovalue in the texture & compute the gradient
    //at this position (coeffs.x=isovalue)
    float w = (coeffs.x-sb)/(sf-sb);
    w = clamp(w, 0., 1.); // Added for ATI compatibility
    if(coeffs.x == sf && diff.w != 1.0) //Remove transparency artefacts
      discard;
    vec3 interTexCoord = mix(gl_TexCoord[1].xyz, gl_TexCoord[0].xyz, w);
    vec3 N;
    N.x = VVizLuminance(VVizCombineData(interTexCoord+VVizDu))-VVizLuminance(VVizCombineData(interTexCoord-VVizDu));
    N.y = VVizLuminance(VVizCombineData(interTexCoord+VVizDv))-VVizLuminance(VVizCombineData(interTexCoord-VVizDv));
    N.z = VVizLuminance(VVizCombineData(interTexCoord+VVizDw))-VVizLuminance(VVizCombineData(interTexCoord-VVizDw));
    N = normalize(N);
    N = -faceforward(N, normalize(VVizViewVec), N);

    //Compute diffuse and specular
    float d = dot(N, normalize(VVizLightingVec));
    vec3 H = normalize(VVizHalfVec.xyz);
    float s = pow(max(dot(N, H), 0.), spec.w*256.);

    res.w = diff.w;
    res.xyz = d*diff.xyz+s*spec.xyz;
  }
  return res;
}

vec4 VVizComputePreIntegrated(VVIZ_DATATYPE sf, VVIZ_DATATYPE sb)
{
  vec4 res = texture2D(VVizPreIntLut, vec2(VVizLuminance(sf), VVizLuminance(sb)));
  res.w = res.w*gl_Color.w; //Multiply by the current material transaparency

  return res;
}

vec4 VVizComputeVolumeRendering(VVIZ_DATATYPE sf)
{
  vec4 res = texture2D(VVizTransfer, vec2(VVizLuminance(sf), 0.));
  res.w = res.w*gl_Color.w;

  return res;
}

vec4 VVizComputePreintegratedLighting(vec4 col)
{
  vec4 res = col;
  if(res.w != 0.) {
    //Normalize
    vec3 view = normalize(VVizViewVec);
    vec3 light = normalize(VVizLightingVec);

    vec3 interTexCoord = mix(gl_TexCoord[1].xyz, gl_TexCoord[0].xyz, 0.5);
    vec3 N;
    N.x = VVizLuminance(VVizCombineData(interTexCoord+VVizDu))-VVizLuminance(VVizCombineData(interTexCoord-VVizDu));
    N.y = VVizLuminance(VVizCombineData(interTexCoord+VVizDv))-VVizLuminance(VVizCombineData(interTexCoord-VVizDv));
    N.z = VVizLuminance(VVizCombineData(interTexCoord+VVizDw))-VVizLuminance(VVizCombineData(interTexCoord-VVizDw))+VVizNvidiaWorkAround;
    N = normalize(N);
    N = -faceforward(N, view, N);

    //Compute diffuse and specular
    float d = dot(N, light);
    vec3 H = normalize(VVizHalfVec.xyz);
    float s = pow(max(dot(N, H), 0.), gl_FrontMaterial.shininess);

    vec3 diffuse = d*col.xyz*gl_FrontMaterial.diffuse.xyz;
    vec3 specular = s*gl_FrontMaterial.specular.xyz;
    vec3 ambient = gl_FrontMaterial.ambient.xyz;
    vec3 emission = gl_FrontMaterial.emission.xyz+vec3(2., 2., 2.);

    //Increase brightness with the material emission term
    res.xyz = (ambient+diffuse+specular)*emission;
    res.w = col.w;
  }
  return res;
}

vec4 VVizComputeVolumeRenderingLighting(vec4 col)
{
  vec4 res = col;
  if(res.w != 0.) {
    //work around for nvidia's compiler bug:
    //without it VVizLightingVec is not correct
    vec4 workAround = gl_TexCoord[1];

    //Normalize
    vec3 light = normalize(VVizLightingVec);
    vec3 view = normalize(VVizViewVec);

    vec3 N;
    N.x = VVizLuminance(VVizCombineData(gl_TexCoord[0].xyz+VVizDu))-VVizLuminance(VVizCombineData(gl_TexCoord[0].xyz-VVizDu));
    N.y = VVizLuminance(VVizCombineData(gl_TexCoord[0].xyz+VVizDv))-VVizLuminance(VVizCombineData(gl_TexCoord[0].xyz-VVizDv));
    N.z = VVizLuminance(VVizCombineData(gl_TexCoord[0].xyz+VVizDw))-VVizLuminance(VVizCombineData(gl_TexCoord[0].xyz-VVizDw))+VVizNvidiaWorkAround;
    N = normalize(N);
    N = -faceforward(N, view, N);

    //Compute diffuse and specular
    float d = dot(N, light);
    vec3 H = normalize(VVizHalfVec.xyz);
    float s = pow(max(dot(N, H), 0.), gl_FrontMaterial.shininess);

    vec3 diffuse = d*col.xyz*gl_FrontMaterial.diffuse.xyz;
    vec3 specular = s*gl_FrontMaterial.specular.xyz;
    vec3 ambient = gl_FrontMaterial.ambient.xyz;
    vec3 emission = gl_FrontMaterial.emission.xyz+vec3(2., 2., 2.);

    //Increase brightness with the material emission term
    res.xyz = (ambient+diffuse+specular)*emission;
    res.w = col.w;
  }
  return res;
}

vec4 VVizBumpSlice(vec4 col, float bumpScale)
{
  return vec4(1., 1., 1., 1.);
}
