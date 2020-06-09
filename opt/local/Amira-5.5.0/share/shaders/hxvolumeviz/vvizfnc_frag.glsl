/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Benjamin GRANGE (Aug 2005)
**=======================================================================*/
/*=======================================================================
* Description : Shader library for volume rendering
*========================================================================*/
uniform sampler3D VVizIsoLut;
uniform vec3 VVizInvIsoLutSize;
uniform float VVizSliceSpacing;

#ifndef VVIZ_DATA2D
uniform sampler3D VVizData;
#endif

#ifndef VVIZ_DATARGBA
#define VVIZ_DATATYPE float
#else
#define VVIZ_DATATYPE vec4
#endif


uniform sampler3D VVizMatPal;
uniform sampler2D VVizTransfer;

uniform vec3 VVizDu;
uniform vec3 VVizDv;
uniform vec3 VVizDw;
//On drivers 91.47 VVizDw is not correct without this dummy uniform
uniform float VVizNvidiaWorkAround;

uniform float VViz256OverNumIsos;

uniform float VVizGradientThreshold;

uniform float VVizSurfaceScalarExponent;
uniform bool VVizSurfaceScalar;

uniform float VVizOneOverSliceDensity;

uniform vec3 VVizUvwMin;
uniform vec3 VVizUvwMax;

uniform vec3 VVizVolumeDimensions;
uniform vec3 VVizTileDimensions;
uniform vec3 VVizTileMinIJK;
uniform vec3 VVizTileMaxIJK;

varying vec3 VVizLightingVec;
varying vec3 VVizViewVec;
varying vec4 VVizHalfVec;

uniform bool VVizUnnormalizedGradient;
uniform float VVizUnnormalizedGradientExponent;

uniform int VVizDefaultTfId;

vec4 VVizTransferFunction(VVIZ_DATATYPE vox, int num);
vec4 VVizTransferFunction(VVIZ_DATATYPE sf, VVIZ_DATATYPE sb, int num);

vec3 VVizJitter(vec3 tcoord);
vec4 VVizComputeVolumeRenderingLighting(vec4 col, vec3 normal, float gradLength);
vec4 VVizComputePreintegratedLighting(vec4 col, vec3 normal, float gradLength);
vec3 VVizComputeCoordinates(const vec3);
vec3 VVizComputeGradient(vec3 tcoord);
vec3 VVizComputeGradient(sampler3D tex, vec3 tcoord);
vec4 VVizLighting(vec4 col, vec4 diffColor, vec4 specularColor,
                  vec4 emissionColor, vec4 ambientColor,
                  vec2 diffSpecCoeffs);
vec3 VVizComputeCoordinatesGradient(vec3 v);
vec2 VVizIsosurfaceLookupIndex(float sf, float sb);
vec4 VVizComputeMinMaxTexCoord(vec2 tcoord);

/**
 * Return in x the diffuse coeff and in y the specular coeff.
 * (Workaround: last 3 parameters are uniforms and not needed but starting with 185 drivers,
 * C9999 error if uniforms directly used in the function.)
 */
vec2 VVizComputeDiffuseAndSpecularCoeffs(vec3 normal, float gradLength, float threshold, vec3 lightVec, vec3 halfVec, float shininess);

/** Blend 2 colors using the over operator, result color is not alpha premutiplied */
vec4 VVizOverOperator(vec4 underCol, vec4 overCol)
{
  vec4 res;
  res.xyz = underCol.w*underCol.xyz+overCol.xyz*overCol.w*(1.-underCol.w);
  res.w = overCol.w*(1.-underCol.w)+underCol.w;

  //res is a alpha premutiplied color, so go back to non premutiplied
  //for next blending operations
  if ( res.w != 0. )
    res.xyz /= res.w;
  else
    res = vec4(0.);
  return res;
}

float VVizGetLuminance(VVIZ_DATATYPE data)
{
#ifndef VVIZ_DATARGBA
  return data;
#else
  return dot(vec3(0.299,0.587,0.114),data.xyz);
#endif
}

/**
 * Compute the gradient at the center of the two slices.
 */
vec3 VVizComputePreintegratedGradient(vec3 tcoord0, vec3 tcoord1)
{
   vec3 interTexCoord = mix(tcoord1, tcoord0, 0.5);
   return VVizComputeGradient(interTexCoord);
}

vec3 VVizComputePreintegratedGradient(sampler3D tex, vec3 tcoord0, vec3 tcoord1)
{
   vec3 interTexCoord = mix(tcoord1, tcoord0, 0.5);
   return VVizComputeGradient(tex, interTexCoord);
}

vec3 VVizComputeNormal(vec3 view, vec3 grad)
{
  vec3 n = grad;
  n = normalize(n);

  return -faceforward(n, view, n);
}

vec3 VVizComputeNormal(vec3 view, vec3 grad, float gradNorm)
{
  vec3 n = grad;
  n /= gradNorm;
  return -faceforward(n, view, n);
}

vec4 VVizComputeIsoMaterial(sampler3D tex, VVIZ_DATATYPE sf, VVIZ_DATATYPE sb, int maskId)
{
  float isoLut = float(maskId+0.5)*VVizInvIsoLutSize.z;
  vec4 res = texture3D(VVizIsoLut, vec3(VVizIsosurfaceLookupIndex(VVizGetLuminance(sf), VVizGetLuminance(sb)), isoLut));

  //0=>no visible isosurface
  if(res.w != 0.) {
    //Fetch material
    //|diff|spec|shininess|isoval
    float idx = res.w*VViz256OverNumIsos; //lut*256/NUMISO
    vec4 diff = texture3D(VVizMatPal, vec3(0.5/4., idx, isoLut));
    vec4 spec = texture3D(VVizMatPal, vec3(1.5/4., idx, isoLut));
    vec4 coeffs = texture3D(VVizMatPal, vec3(2.5/4., idx, isoLut));
    float shininess = spec.w*128.;

    //Find where is the isovalue in the texture & compute the gradient
    //at this position (coeffs.x=isovalue)
    float w = (coeffs.x-VVizGetLuminance(sb))/(VVizGetLuminance(sf)-VVizGetLuminance(sb));
    w = clamp(w, 0., 1.); // Added for ATI compatibility

    vec3 interTexCoord = mix(gl_TexCoord[1].xyz, gl_TexCoord[0].xyz, w);
    interTexCoord = VVizComputeCoordinatesGradient(interTexCoord);

    vec3 N;
    N = VVizComputeGradient(tex, interTexCoord);
    float gradLength = length(N);

    //No lighting if gradient is noise
    N = VVizComputeNormal(normalize(VVizViewVec), N, gradLength);
    vec2 coeffsLight = VVizComputeDiffuseAndSpecularCoeffs(N, gradLength, VVizGradientThreshold, VVizLightingVec, VVizHalfVec.xyz, shininess);
    res = VVizLighting(diff, vec4(1., 1., 1., 1.), spec,
                       vec4(-1., -1., -1., 0.),  vec4(0., 0., 0., 0.), coeffsLight);

    //Remove transparency artefacts
    if(coeffs.x == sf && diff.w != 1.0)
      res.w = 0.;
  }
  return res;
}

vec4 VVizComputeIsoMaterial(VVIZ_DATATYPE sf, VVIZ_DATATYPE sb, int maskId)
{
#ifndef VVIZ_DATA2D
  return VVizComputeIsoMaterial(VVizData, sf, sb, maskId);
#else
  return vec4(0.);
#endif
}

vec4 VVizComputeIsoMaterial(VVIZ_DATATYPE sf, VVIZ_DATATYPE sb)
{
  return VVizComputeIsoMaterial(sf, sb, 0);
}

vec4 VVizComputePreIntegrated(VVIZ_DATATYPE sf, VVIZ_DATATYPE sb, int mask)
{
  vec4 res = VVizTransferFunction(sf, sb, mask);
  res.w = 1.-pow(max(1.-res.w*gl_Color.w,0), VVizOneOverSliceDensity);

  return res;
}

vec4 VVizComputePreIntegrated(VVIZ_DATATYPE sf, VVIZ_DATATYPE sb)
{
  return VVizComputePreIntegrated(sf, sb, VVizDefaultTfId);
}

vec4 VVizComputeVolumeRendering(VVIZ_DATATYPE sf, int tfId)
{
#ifndef VVIZ_NODATA
  vec4 res = VVizTransferFunction(sf, tfId);
  res.w = 1.-pow(max(1.-res.w *gl_Color.w,0), VVizOneOverSliceDensity);

  return res;
#else
  return gl_Color;
#endif
}

vec4 VVizComputeVolumeRendering(VVIZ_DATATYPE sf)
{
  return VVizComputeVolumeRendering(sf, VVizDefaultTfId);
}

vec4 VVizComputePreintegratedLighting(vec4 col)
{
  vec4 res = col;
  if(res.w != 0.) {
    vec3 tcoord0 = VVizComputeCoordinatesGradient(gl_TexCoord[0].xyz);
    vec3 tcoord1 = VVizComputeCoordinatesGradient(gl_TexCoord[1].xyz);

    //Compute normal to use with preintegration
    vec3 N;
    N = VVizComputePreintegratedGradient(tcoord0, tcoord1);
    float gradLength = length(N);
    vec3 view = normalize(VVizViewVec);
    N = VVizComputeNormal(view, N, gradLength);

    res = VVizComputePreintegratedLighting(res, N, gradLength);
  }
  return res;
}

vec4 VVizComputePreintegratedLighting(vec4 col, vec3 normal, float gradLength)
{
  return VVizComputeVolumeRenderingLighting(col, normal, gradLength);
}

vec4 VVizComputeVolumeRenderingLighting(vec4 col)
{
  vec4 res = col;
  if(res.w != 0.)
  {
    //work around for nvidia's compiler bug:
    //without it VVizLightingVec is not correct
    vec4 workAround = gl_TexCoord[1];

    //Normalize
    vec3 view = normalize(VVizViewVec);

    vec3 N;
    N = VVizComputeGradient(VVizComputeCoordinatesGradient(gl_TexCoord[0].xyz));
    float gradLength = length(N);
    N = VVizComputeNormal(view, N, gradLength);
    res = VVizComputeVolumeRenderingLighting(col, N, gradLength);
  }
  return res;
}

vec2 VVizComputeDiffuseAndSpecularCoeffs(vec3 normal, float gradLength, float threshold, vec3 lightVec, vec3 halfVec, float shininess)
{
  vec2 res;
  if ( VVizUnnormalizedGradient && gradLength < threshold )
  {
    res = vec2(1., 0.);
  }
  else
  {
    vec3 light = normalize(lightVec);

    //Compute diffuse and specular
    vec3 H = normalize(halfVec);
    float n = max(shininess, 0.0001);
    res = vec2(max(dot(normal, light), 0.),
               pow(max(dot(normalize(normal), H), 0.), n));

   //Weigth lighting coeefs by gradient length
   if ( !VVizUnnormalizedGradient )
     res.xy *= (1-pow(1-gradLength, VVizUnnormalizedGradientExponent));
   }
   return res;
}

vec3 VVizApplySurfaceScalarInternal(vec3 baseColor, vec3 lightedColor, float gradLength)
{
  float t = 1.-pow((1.-gradLength), VVizSurfaceScalarExponent);
  return mix(baseColor, lightedColor, t);
}

vec3 VVizApplySurfaceScalar(vec3 baseColor, vec3 lightedColor, float gradLength)
{
  return VVizSurfaceScalar?VVizApplySurfaceScalarInternal(baseColor, lightedColor, gradLength):lightedColor;
}

vec4 VVizComputeVolumeRenderingLighting(vec4 col, vec3 normal, float gradLength)
{
  vec4 res = col;
  if(res.w != 0.)
  {
    //work around for nvidia's compiler bug:
    //without it VVizLightingVec is not correct
    vec4 workAround = gl_TexCoord[1];

    vec2 diffSpecCoeffs = VVizComputeDiffuseAndSpecularCoeffs(normal, gradLength, VVizGradientThreshold, VVizLightingVec, VVizHalfVec.xyz, gl_FrontMaterial.shininess);
    res = VVizLighting(res, gl_FrontMaterial.diffuse, gl_FrontMaterial.specular,
                       gl_FrontMaterial.emission, gl_FrontMaterial.ambient,
                       diffSpecCoeffs);
    res.xyz = VVizApplySurfaceScalar(col.xyz, res.xyz, gradLength);
  }
  return res;
}

vec3 VVizComputeViewVec()
{
  return normalize(VVizViewVec);
}

vec2 VVizComputeCoordinates(const vec2 tCoord)
{
  vec4 minMax = VVizComputeMinMaxTexCoord(tCoord);
  return clamp(tCoord, minMax.xy, minMax.zw);
}

bool VVizIsOutsideTexture(vec3 tcoord)
{
  return any(lessThan(tcoord, VVizUvwMin)) || any(greaterThan(tcoord, VVizUvwMax));
}

bool VVizIsOutsideVolume(vec3 tcoord)
{
  vec3 ijk = VVizTileMinIJK+tcoord*(VVizTileMaxIJK-VVizTileMinIJK+vec3(1.));
  return any(lessThan(ijk, vec3(0.))) || any(greaterThan(ijk, VVizVolumeDimensions));
}

/**True if tcoord is on the volume's boundary voxel or out of the volume*/
bool VVizIsOutsideOrOnVolumeBorder(vec3 tcoord)
{
  vec3 ijk = VVizTileMinIJK+tcoord*(VVizTileMaxIJK-VVizTileMinIJK+vec3(1.));
  return any(lessThan(ijk, vec3(1.))) || any(greaterThan(ijk, VVizVolumeDimensions-vec3(1.)));
}
