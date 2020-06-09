#ifndef VVIZ_DATA2D
uniform sampler3D VVizData;
#endif

uniform vec3 VVizDu;
uniform vec3 VVizDv;
uniform vec3 VVizDw;

uniform vec3 VVizInvIsoLutSize;
uniform sampler3D VVizMatPal;
uniform sampler3D VVizIsoLut;
uniform float VViz256OverNumIsos;
uniform float VVizGradientThreshold;
uniform vec3 VVizTileDimensions;
uniform vec3 VVizInvTileDimensions;

#if VVIZ_NUM_ISOVALUES > 0
//Isovalues normalized between 0-1
uniform float VVizIsoValues[VVIZ_NUM_ISOVALUES];
#endif

uniform float VVizIsoThreshold;

/**
 * 8 neightboors:
 * left[0] is (0,0,0)
 * left[1] is (0, 1, 0)
 * left[2] is (0, 0, 1)
 * left[3] is (1, 0, 1)
 * same for right.
 */
struct VVizNeightboors
{
  vec4 left;
  vec4 right;
  //Coeffs used for linear interpolation (ie: fractionnal part of texcoords)
  vec3 coeffs;
};

varying vec3 VVizViewVec;
varying vec3 VVizLightingVec;
varying vec4 VVizHalfVec;

vec2 VVizComputeDiffuseAndSpecularCoeffs(vec3 normal, float gradLength, float threshold, vec3 lightVec, vec3 halfVec, float shininess);
vec2 VVizIsosurfaceLookupIndex(float sf, float sb);
vec3 VVizComputeCoordinatesGradient(vec3 v);
vec3 VVizComputeGradient(sampler3D tex, vec3 tcoord);
vec3 VVizComputeNormal(vec3 view, vec3 grad, float gradNorm);
vec4 VVizLighting(vec4 col, vec4 diffColor, vec4 specularColor,
                  vec4 emissionColor, vec4 ambientColor,
                  vec2 diffSpecCoeffs);
float VVizGetLuminance(VVIZ_DATATYPE data);
VVIZ_DATATYPE VVizGetData(sampler3D tex, vec3 tcoord);

void VVizGetNeighboors(sampler3D tex, in vec3 tcoord, out VVizNeightboors info)
{
  vec3 texUV = tcoord*VVizTileDimensions-0.5;
  info.coeffs = fract(texUV);
  vec3 texUVInt = (floor(texUV)+0.5)*VVizInvTileDimensions;

  vec3 tmp = texUVInt;
  info.left[0] = VVizGetLuminance(VVizGetData(tex, tmp));
  info.right[0] = VVizGetLuminance(VVizGetData(tex, tmp+VVizDu));

  tmp += VVizDv;
  info.left[1] = VVizGetLuminance(VVizGetData(tex, tmp));
  info.right[1] = VVizGetLuminance(VVizGetData(tex, tmp+VVizDu));

  tmp = texUVInt+VVizDw;
  info.left[2] = VVizGetLuminance(VVizGetData(tex, tmp));
  info.right[2] = VVizGetLuminance(VVizGetData(tex, tmp+VVizDu));

  tmp += VVizDv;
  info.left[3] = VVizGetLuminance(VVizGetData(tex, tmp));
  info.right[3] = VVizGetLuminance(VVizGetData(tex, tmp+VVizDu));
}

/** Binary interpolate neighborhood info at pos tcoord.
 * All texels != value are set to 0, otherwise 1.
 */
float VVizInterpolateBinaryValue(vec3 tcoord, float value,  VVizNeightboors info)
{
  for(int i = 0; i < 4; i++)
  {
    info.left[i]=(info.left[i]==value)?1.:0.;
    info.right[i]=(info.right[i]==value)?1.:0.;
  }

  vec4 topBottom = mix(info.left, info.right, info.coeffs.xxxx);
  vec2 frontBack = mix(topBottom.xz, topBottom.yw, info.coeffs.yy);

  return mix(frontBack.x, frontBack.y, info.coeffs.z);
}

vec4 VVizComputeGeobodies(sampler3D tex, int maskId, int isoIdx, VVizNeightboors infoSf, VVizNeightboors infoSb)
{
#if !defined(VVIZ_DATA2D) && VVIZ_NUM_ISOVALUES > 0
  float iso = VVizIsoValues[isoIdx];
  float sf = VVizInterpolateBinaryValue(gl_TexCoord[0].xyz, iso, infoSf);
  float sb = VVizInterpolateBinaryValue(gl_TexCoord[1].xyz, iso, infoSb);
  float isoLut = float(maskId+0.5)*VVizInvIsoLutSize.z;
  bool intersect = (sf<=VVizIsoThreshold && sb>=VVizIsoThreshold)||(sb<=VVizIsoThreshold && sf>=VVizIsoThreshold);

  vec4 res = vec4(0.);
  if(intersect)
  {
    //Fetch material
    //|diff|spec|shininess|isoval
    float idx = float(isoIdx+1.)/255.*VViz256OverNumIsos; //lut*256/NUMISO
    vec4 diff = texture3D(VVizMatPal, vec3(0.5/4., idx, isoLut));
    vec4 spec = texture3D(VVizMatPal, vec3(1.5/4., idx, isoLut));
    float shininess = spec.w*128.;

    //Find where is the isovalue in the texture & compute the gradient
    //at this position (coeffs.x=isovalue)
    float w = (VVizIsoThreshold-sb)/(sf-sb);
    w = clamp(w, 0., 1.); // Added for ATI compatibility

    vec3 interTexCoord = mix(gl_TexCoord[1].xyz, gl_TexCoord[0].xyz, w);
    interTexCoord = VVizComputeCoordinatesGradient(interTexCoord);

    vec3 N;
    N = VVizComputeGradient(tex, interTexCoord);
    float gradLength = length(N);
    if ( gradLength < VVizGradientThreshold )
    {
      w = (0.5-sb)/(sf-sb);
      w = clamp(w, 0., 1.); // Added for ATI compatibility

      interTexCoord = mix(gl_TexCoord[1].xyz, gl_TexCoord[0].xyz, w);
      interTexCoord = VVizComputeCoordinatesGradient(interTexCoord);

      N = VVizComputeGradient(tex, interTexCoord);
      gradLength = length(N);
    }

    //No lighting if gradient is noise
    N = VVizComputeNormal(normalize(VVizViewVec), N, gradLength);
    vec2 coeffsLight = VVizComputeDiffuseAndSpecularCoeffs(N, gradLength, VVizGradientThreshold, VVizLightingVec, VVizHalfVec.xyz, shininess);
    res = VVizLighting(diff, vec4(1., 1., 1., 1.), spec,
                       vec4(-1., -1., -1., 0.),  vec4(0., 0., 0., 0.), coeffsLight);

    //Remove transparency artefacts
    if(VVizIsoThreshold == sf && diff.w != 1.0)
      res.w = 0.;
  }

  return res;
#else
  return vec4(0.);
#endif
}

vec4 VVizComputeGeobodies(sampler3D tex, int maskId, vec3 tCoordFront, vec3 tCoordBack)
{
#if !defined(VVIZ_DATA2D) && VVIZ_NUM_ISOVALUES > 0
  VVizNeightboors info[2];
  VVizGetNeighboors(tex, tCoordFront, info[0]);
  VVizGetNeighboors(tex, tCoordBack, info[1]);

  vec4 res = vec4(0.);
  for ( int i = 0; i < VVIZ_NUM_ISOVALUES; i++ )
    res += VVizComputeGeobodies(tex, maskId, i, info[0], info[1]);

  return res;
#else
  return vec4(0.);
#endif
}

vec4 VVizComputeGeobodies(vec3 tCoordFront, vec3 tCoordBack)
{
#ifndef VVIZ_DATA2D
  return VVizComputeGeobodies(VVizData, 0, tCoordFront, tCoordBack);
#else
  return vec4(0.);
#endif
}
