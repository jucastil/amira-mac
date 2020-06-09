//Reference: www2.ati.com/misc/samples/dx9/FixedFuncShader.pdf

#define NUM_LIGHTS               8

#define LIGHT_TYPE_NONE          0
#define LIGHT_TYPE_POINT         1
#define LIGHT_TYPE_SPOT          2
#define LIGHT_TYPE_DIRECTIONAL   3
#define LIGHT_NUM_TYPES          4

#define FOG_MODE_NONE            0
#define FOG_MODE_EXP             1
#define FOG_MODE_EXP2            2
#define FOG_MODE_LINEAR          3

#define TEXGEN_TYPE_NONE             0
#define TEXGEN_TYPE_OBJECT_PLANE     1
#define TEXGEN_TYPE_REFLECTION_MAP   2
#define TEXGEN_TYPE_SPHERE_MAP       3
#define TEXGEN_TYPE_NORMAL_MAP       4
#define TEXGEN_TYPE_EYE_PLANE        5

#define PI 3.14159265358979312

void OivSetupShadowVertex();

uniform bool OivLighting = true;
uniform bool OivFogFragmentDepth = false;
uniform bool OivTwoSidedLighting = false;

//fog
uniform int OivFogMode = FOG_MODE_NONE;

uniform int OivTexGenType = TEXGEN_TYPE_NONE;

uniform int OivLights[NUM_LIGHTS];

uniform bool OivColorMaterial = false;

/** Return the curent material according to given color material mode*/
/* Inventor supports diffuse color material only */
vec4
OivGetDiffuse()
{
  if ( OivColorMaterial || !OivLighting )
  {
    return gl_Color;
  }
  else
  {
    return gl_FrontMaterial.diffuse;
  }
}

void
OivComputeLighting(in vec4 viewSpaceVertex, in vec3 viewVector, in vec3 viewSpaceNormal,
                   out vec4 cFront, out vec4 cBack)
{
  cFront = vec4(0.);
  cBack = vec4(0.);

  vec4 Dcm = OivGetDiffuse();

  if ( !OivLighting )
  {
    cFront = Dcm;
    cBack = cFront;
  }
  else
  {
    for ( int i = 0; i < NUM_LIGHTS; i++ )
    {
      if ( OivLights[i] == LIGHT_TYPE_NONE )
        continue;

      vec3 lightVector = normalize(gl_LightSource[i].position.xyz-viewSpaceVertex.xyz*gl_LightSource[i].position.w);

      float NdotL = dot(viewSpaceNormal, lightVector.xyz);
      vec3 diffuseFront = gl_FrontLightProduct[i].ambient.xyz;
      vec3 diffuseBack = diffuseFront;
      vec3 specularFront = vec3(0.);
      vec3 specularBack = vec3(0.);
      vec3 H = normalize(lightVector+vec3(0, 0, 1));
      float HdotV = dot(H, viewSpaceNormal);
      float specCoeff = pow(abs(HdotV), gl_FrontMaterial.shininess);
      vec3 specularCol = specCoeff*gl_FrontLightProduct[i].specular.xyz;
      vec3 diffuseCol = NdotL*Dcm.xyz*gl_LightSource[i].diffuse.xyz;
      if ( NdotL > 0. )
      {
        diffuseFront += diffuseCol;
        if ( HdotV > 0 )
          specularFront = specularCol;
      }
      else if ( OivTwoSidedLighting )
      {
        diffuseBack = -diffuseCol;
        if ( HdotV < 0 )
          specularBack = specularCol;
      }

      if ( OivLights[i] == LIGHT_TYPE_SPOT )
      {
        //spot cone computation
        float spot = 1.;
        vec3 Sdli = normalize((vec4(gl_LightSource[i].spotDirection, 0.)).xyz);
        float rho = max(dot(-lightVector, Sdli), 0.);
        if ( gl_LightSource[i].spotCutoff != 180. )
        {
          if ( rho >= gl_LightSource[i].spotCosCutoff )
            spot = pow(rho, gl_LightSource[i].spotExponent);
          else
            spot = 0.;
          specularFront *= spot;
          diffuseFront *= spot;
          specularBack *= spot;
          diffuseBack *= spot;
        }
      }

      cFront.xyz += diffuseFront+specularFront;
      cBack.xyz += diffuseBack+specularBack;
    }
    cFront.xyz += gl_FrontLightModelProduct.sceneColor.xyz;
    cFront.w = Dcm.w;

    cBack.xyz += gl_FrontLightModelProduct.sceneColor.xyz;
    cBack.w = Dcm.w;
  }
}

/*****************************************************************************/
float computeFog(vec3 P)
{
  float d;
  float fog = 0.;

  if(!OivFogFragmentDepth)
    d = length(P);
  else
    d = P.z;

  if (OivFogMode == FOG_MODE_NONE)
    fog = 1.;
  else if(OivFogMode == FOG_MODE_EXP)
    fog = 1./exp(d * gl_Fog.density);
  else if(OivFogMode == FOG_MODE_EXP2)
    fog = 1./exp(pow(d * gl_Fog.density, 2.));
  else if ( OivFogMode == FOG_MODE_LINEAR)
    fog = clamp((gl_Fog.end - d)*gl_Fog.scale, 0., 1.);

  return fog;
}

/*****************************************************************************/
vec4 computeTexCoords(int i, vec4 V, vec3 N, vec4 P, vec4 inCoords)
{
  vec4 tcoords = vec4(0., 0., 0., 1.);
  if ( OivTexGenType == TEXGEN_TYPE_NONE )
    tcoords = inCoords;
  else
  {
    //Inventor only allows this kind of texgen
    tcoords.x = dot(gl_ObjectPlaneS[i], gl_Vertex);
    tcoords.y = dot(gl_ObjectPlaneT[i], gl_Vertex);
    tcoords.z = dot(gl_ObjectPlaneR[i], gl_Vertex);
    if ( gl_ObjectPlaneQ[i] != vec4(0.) )
      tcoords.w = dot(gl_ObjectPlaneQ[i], gl_Vertex);
  }

  return gl_TextureMatrix[0]*tcoords;
}

void OivOutputColor(in vec4 col)
{
  gl_FrontColor.xyz = min(vec3(1.), col.xyz);
  gl_FrontColor.w = col.w;
}

/*****************************************************************************/
void main ()
{
  OivSetupShadowVertex();
  vec4 P = gl_ModelViewMatrix*gl_Vertex;
  vec3 N = normalize(gl_NormalMatrix*gl_Normal);
  vec4 V = -normalize(P);

  vec4 cFront = vec4(0.);
  vec4 cBack = vec4(0.);
  OivComputeLighting(P, V.xyz, N, cFront, cBack);

  if ( !OivTwoSidedLighting || dot(N, V.xyz) >= 0. )
  {
    OivOutputColor(cFront);
  }
  else if ( OivTwoSidedLighting )
  {
    OivOutputColor(cBack);
  }

  gl_Position = gl_ModelViewProjectionMatrix*gl_Vertex;
#if !defined(OIV_USE_ATI)
  gl_ClipVertex = P;
#endif

  gl_TexCoord[0] = computeTexCoords(0, V, N, P, gl_MultiTexCoord0);
//   gl_TexCoord[1] = computeTexCoords(1, V, N, P, gl_MultiTexCoord1);
//   gl_TexCoord[2] = computeTexCoords(2, V, N, P, gl_MultiTexCoord2);
//   gl_TexCoord[3] = computeTexCoords(3, V, N, P, gl_MultiTexCoord3);

  if ( OivFogMode != FOG_MODE_NONE )
    gl_FogFragCoord = computeFog(P.xyz);
}
