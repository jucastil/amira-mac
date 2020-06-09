#ifdef OIV_HAS_SHADER_MODEL4
#extension GL_EXT_gpu_shader4 : enable
#endif

#define VVIZ_VOLUME_RENDER_MASK_STYLE 1
#define VVIZ_BOUNDARY_MASK_STYLE 2
#define VVIZ_ISOSURFACE_MASK_STYLE 4
#define VVIZ_MIXED_MASK_STYLE 3

#define BOUNDARY_PALETTE_TEXTURE 0
#define BOUNDARY_TEST_TEXTURE 1

vec4 VVizOverOperator(vec4 underCol, vec4 overCol);
int VVizGetMask(vec3 tcoord);
bool VVizIsOutsideOrOnVolumeBorder(vec3 tcoord);
bool VVizIsOutsideVolume(vec3 tcoord);
vec3 VVizComputeGradient(vec3 tcoord);
vec4 VVizComputeIsoMaterial(VVIZ_DATATYPE sf, VVIZ_DATATYPE sb, int maskId);
VVIZ_DATATYPE VVizCombineData(vec3 tcoord);

vec2 VVizComputeDiffuseAndSpecularCoeffs(vec3 normal, float gradLength, float threshold, vec3 lightVec, vec3 halfVec, float shininess);
vec4 VVizLighting(vec4 col, vec4 diffColor, vec4 specularColor,
                  vec4 emissionColor, vec4 ambientColor,
                  vec2 diffSpecCoeffs);

uniform vec3 VVizDu;
uniform vec3 VVizDv;
uniform vec3 VVizDw;

//depth 0 : Render mode and boundary material
//depth 1 : Boundary test texture
uniform sampler3D VVizVolumeMaskTex;

uniform float VVizInvRenderModeTexSize;

uniform float VVizGradientThreshold;
varying vec3 VVizLightingVec;
varying vec3 VVizViewVec;
varying vec4 VVizHalfVec;

int VVizGetRenderMode(int mask)
{
  float p = (float(mask)+0.5)*VVizInvRenderModeTexSize;
  return int(texture3D(VVizVolumeMaskTex, vec3(0, p, BOUNDARY_PALETTE_TEXTURE)).x*255.);
}

vec4 VVizGetBoundaryColor(int mask)
{
  float p = (float(mask)+0.5)*VVizInvRenderModeTexSize;
  return texture3D(VVizVolumeMaskTex, vec3(VVizInvRenderModeTexSize, p, BOUNDARY_PALETTE_TEXTURE));
}

vec3 VVizComputeBoundaryGradient(vec3 tcoord, int mask)
{
  vec3 G;
  int a001 = VVizGetMask(tcoord-VVizDu);
  int a201 = VVizGetMask(tcoord+VVizDu);

  int a101 = VVizGetMask(tcoord-VVizDv);
  int a121 = VVizGetMask(tcoord+VVizDv);

  int a100 = VVizGetMask(tcoord-VVizDw);
  int a102 = VVizGetMask(tcoord+VVizDw);

  bool outa001 = VVizIsOutsideVolume(tcoord-VVizDu);
  bool outa201 = VVizIsOutsideVolume(tcoord+VVizDu);

  bool outa101 = VVizIsOutsideVolume(tcoord-VVizDv);
  bool outa121 = VVizIsOutsideVolume(tcoord+VVizDv);

  bool outa100 = VVizIsOutsideVolume(tcoord-VVizDw);
  bool outa102 = VVizIsOutsideVolume(tcoord+VVizDw);


  a001 = (a001 != mask || outa001)? 0:1;
  a201 = (a201 != mask || outa201)? 0:1;
  a101 = (a101 != mask || outa101)? 0:1;
  a121 = (a121 != mask || outa121)? 0:1;
  a100 = (a100 != mask || outa100)? 0:1;
  a102 = (a102 != mask || outa102)? 0:1;
  G.x = float(a001-a201);
  G.y = float(a101-a121);
  G.z = float(a100-a102);

  return G;
}

vec4 VVizGetMaskBoundaryColor(int maskFront, int maskBack, vec3 texCoordFront, vec3 texCoordBack)
{
  bool outFront = VVizIsOutsideOrOnVolumeBorder(texCoordFront);
  bool outBack = VVizIsOutsideOrOnVolumeBorder(texCoordBack);
  bool outside = ( outFront && !outBack )||
                 (!outFront && outBack);

  vec2 frontBack = vec2(maskFront, maskBack)*VVizInvRenderModeTexSize;
  //if outside just retrieve the colour used by iso maskBack
  if ( outside )
  {
    return VVizGetBoundaryColor(maskFront);
  }
  float matIdx = texture3D(VVizVolumeMaskTex, vec3(frontBack, BOUNDARY_TEST_TEXTURE)).x;
  return texture3D(VVizVolumeMaskTex, vec3(VVizInvRenderModeTexSize, matIdx, BOUNDARY_PALETTE_TEXTURE));
}

vec4 VVizComputeBoundaryLighting(vec4 fragColor, int maskFront, vec3 texCoordFront)
{
  vec3 g = VVizComputeBoundaryGradient(texCoordFront, maskFront);
  vec3 N = normalize(g);
  float gradlen = length(g);

  vec2 diffSpecCoeffs = VVizComputeDiffuseAndSpecularCoeffs(N, gradlen, VVizGradientThreshold, VVizLightingVec, VVizHalfVec.xyz, gl_FrontMaterial.shininess);
  return VVizLighting(fragColor, gl_FrontMaterial.diffuse, gl_FrontMaterial.specular,
                      gl_FrontMaterial.emission, gl_FrontMaterial.ambient,
                      diffSpecCoeffs);
}

#if defined(OIV_HAS_SHADER_MODEL4) && defined(VVIZ_USE_VOLUME_MASK)
vec4 VVizGetRoiFragment(int renderMode, int renderModeBack, vec4 fragColor, int maskFront, int maskBack, vec3 texCoordFront, vec3 texCoordBack)
{
  vec4 res = vec4(0, 0, 0, 0);

  if((renderMode & VVIZ_VOLUME_RENDER_MASK_STYLE) != 0)
  {
    vec4 v = fragColor;
    res = VVizOverOperator(res, fragColor);
  }

  if((renderMode & VVIZ_ISOSURFACE_MASK_STYLE) != 0)
  {
    VVIZ_DATATYPE sf = VVizCombineData(texCoordFront);
    VVIZ_DATATYPE sb = VVizCombineData(texCoordBack);
    vec4 v = VVizComputeIsoMaterial(sf, sb, maskFront);
    res = VVizOverOperator(res, v);
  }

  //Render mode of back slice must be tested for boundaries
  renderMode |= renderModeBack;
  if((renderMode & VVIZ_BOUNDARY_MASK_STYLE) != 0)
  {
    vec4 maskBoundColor = VVizGetMaskBoundaryColor(maskFront, maskBack, texCoordFront, texCoordBack);
    bool maskBound = maskBoundColor.w != 0.;
    if ( maskBound )
    {
      vec4 v = VVizComputeBoundaryLighting(maskBoundColor, maskFront, texCoordFront);
      res = VVizOverOperator(res, v);
    }

    if(renderMode == VVIZ_BOUNDARY_MASK_STYLE && !maskBound)
      discard;
  }

  return res;
}

vec4 VVizApplyBoundary(vec4 fragColor, int maskFront, int maskBack, vec3 texCoordFront, vec3 texCoordBack)
{
  vec4 res = vec4(0, 0, 0, 0);
  int renderMode = VVizGetRenderMode(maskFront);
  int renderModeBack = VVizGetRenderMode(maskBack);
  res = VVizGetRoiFragment(renderMode, renderModeBack, fragColor, maskFront, maskBack, texCoordFront, texCoordBack);

  return res;
}

vec4 VVizApplyBoundary(vec4 fragColor, int maskFront, vec3 texCoordFront, vec3 texCoordBack)
{
  int maskBack = VVizGetMask(texCoordBack);
  return VVizApplyBoundary(fragColor, maskFront, maskBack, texCoordFront, texCoordBack);
}

#else //!OIV_HAS_SHADER_MODEL4
vec4 VVizApplyBoundary(vec4 fragColor, int maskFront, vec3 texCoordFront, vec3 texCoordBack)
{
  return fragColor;
}

vec4 VVizApplyBoundary(vec4 fragColor, int maskFront, int maskBack, vec3 texCoordFront, vec3 texCoordBack)
{
  return fragColor;
}

#endif
