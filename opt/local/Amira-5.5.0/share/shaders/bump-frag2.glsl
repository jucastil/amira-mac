uniform sampler2D colormap;
uniform sampler2D indexedTex;
uniform sampler2D data1;
uniform sampler2D data2;

varying vec3 eNormal;       // Normal in eye space
varying vec3 viewDir;
varying vec3 lightDir;       // Vertex to light vector in eye space

uniform float depth;
uniform float dimTextureU;
uniform float dimTextureV;

const float epsilon0 = 2./255.;
const float epsilon1 = 1.-2./255.;

mat3 computeTBN()
{
  // the following code are far-fetched computations to get an estimation of the direction of
  // the s direction (evolution of the s texture coordinate) in eye space, to get a consistent tangent system
  vec3 feNormal       = eNormal;
  feNormal = normalize(feNormal);

  vec2 deTangent    = vec2(dFdx(gl_TexCoord[0].s),  dFdy(gl_TexCoord[0].s));
  vec2 deZ          = vec2(dFdx(gl_FragCoord.z), dFdy(gl_FragCoord.z));
  vec3 tempeTangent = vec3(deTangent, deTangent.x * -deZ.x + deTangent.y * -deZ.y);
  vec3 temp         = cross(tempeTangent, feNormal);
  vec3 eTangent     = normalize(cross(feNormal, temp));
  vec3 eBinormal = cross(feNormal, eTangent);

  return mat3(eTangent.x, eBinormal.x, feNormal.x,
              eTangent.y, eBinormal.y, feNormal.y,
              eTangent.z, eBinormal.z, feNormal.z);
}

float getData(sampler2D tex, vec2 tcoord)
{
  vec2 texSize = vec2(dimTextureU, dimTextureV);
  vec2 oneOvertexSize = vec2(1./dimTextureU, 1./dimTextureV);
  vec2 texUV = tcoord.xy*texSize-0.5;
  vec2 w = fract(texUV);
  vec2 p = floor(texUV)+0.5;

  float d00 = texture2D(tex, p*oneOvertexSize).r;
  float d10 = texture2D(tex, (p+vec2(1, 0))*oneOvertexSize).r;
  float d01 = texture2D(tex, (p+vec2(0, 1))*oneOvertexSize).r;
  float d11 = texture2D(tex, (p+vec2(1, 1))*oneOvertexSize).r;

  if( (d00 <= epsilon0 || d10 <= epsilon0 || d11 <= epsilon0 || d01 <=epsilon0)
      ||(d00 >= epsilon1 || d10 >= epsilon1 || d11 >= epsilon1 || d01 >=epsilon1))
    return d00;
  else
     return texture2D(tex, tcoord).r;
}

vec3 computeNormal()
{
  vec2 u00, u10, u01 ;

  vec2 newTexCoord = gl_TexCoord[0].st;
  //  vec2 newTexCoord = gl_TexCoord[1].st; // if separate texture coords
  
  u00.x = getData(data1, newTexCoord);
  u00.y = getData(data2, newTexCoord);
  if(u00.x > epsilon0 && u00.y > epsilon0 && u00.x < epsilon1 && u00.y < epsilon1) {
    // height of the texel directly above the given texel:
    u01.x = getData(data1, newTexCoord + vec2(0.0, 1./dimTextureV)); 
    u01.y = getData(data2, newTexCoord + vec2(0.0, 1./dimTextureV));
    if(u01.x > epsilon0 && u01.y > epsilon0 && u01.x < epsilon1 && u01.y < epsilon1) {
      // height of the texel directly to the right of the given texel:
      u10.x = getData(data1, newTexCoord + vec2(1./dimTextureU, 0.0));	
      u10.y = getData(data2, newTexCoord + vec2(1./dimTextureU, 0.0));
      if(u10.x > epsilon0 && u10.y > epsilon0 && u10.x < epsilon1 && u10.y < epsilon1) {
	  float Ha, Hg, Hr;
	  Hg = length(u00);
	  Ha = length(u01);
	  Hr = length(u10);                            // height of the given texel
	  vec3 tNormal;
	  tNormal = vec3(depth*(Hg-Hr), depth*(Hg-Ha), 1.0);
	  return normalize(tNormal);
	}
    }
  }
  return( vec3(0, 0, 1.0)); 
}

vec4 getColor(sampler2D tex, vec2 tcoord)
{
  vec4 res;
  float d00 = getData(tex, tcoord);

  if( d00 <= epsilon0 ) {
      res = texture2D(colormap, vec2(0, 0));
  }
  else if ( d00 >= epsilon1 ) {
    res = texture2D(colormap, vec2(1, 0));
  }
  else  {
    res = texture2D(colormap, vec2(d00, 0));
  }

  return res;
}

void main()
{
  float specularCoeff;
  vec4 indColor = getColor(indexedTex, gl_TexCoord[0].st); 
  if(indColor.w == 0.0)  
  {
	discard;
	return;
  }
  //Lighting vectors in texture space
  mat3 TBN = computeTBN();
  vec3 tLightDir = normalize(TBN*lightDir);
  vec3 tView   = normalize(TBN*viewDir);
  vec3 tNormal = computeNormal();

  //Diff & spec coeffs
  //  orig: tNormal = -faceforward(tNormal, tView, tNormal);
  float diffuseCoeff  = dot(tNormal, tLightDir);
  vec3 H = -reflect(tView, tNormal);
  specularCoeff = max(dot(tLightDir, normalize(H)), 0.);
  diffuseCoeff = abs(diffuseCoeff);
  specularCoeff = pow(specularCoeff, gl_FrontMaterial.shininess);

  // Computation of final colors
  vec4 diffuseColor = indColor * gl_FrontLightProduct[0].diffuse;

  gl_FragColor = gl_FrontLightModelProduct.sceneColor+
                 gl_FrontLightProduct[0].ambient+
                 indColor*diffuseCoeff+
                 gl_FrontLightProduct[0].specular*specularCoeff;
  gl_FragColor.w = indColor.w*gl_FrontMaterial.diffuse.w;
}
