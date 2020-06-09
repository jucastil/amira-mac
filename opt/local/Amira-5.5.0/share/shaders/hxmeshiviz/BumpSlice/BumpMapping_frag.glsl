uniform sampler2D texture;

varying vec3 eNormal;       // Normal in eye space
varying vec3 viewDir;
varying vec3 lightDir;       // Vertex to light vector in eye space

uniform float depth;
uniform int dimTexture;
uniform mat4 transMat;
uniform vec4 color;

// average luminance computation weight
const vec3 luminance = vec3(0.33, 0.33, 0.33);

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

float getData(sampler2D tex, vec2 tcoord, bool disc)
{
  vec2 texSize = vec2(dimTexture, dimTexture);
  vec2 oneOvertexSize = vec2(1./dimTexture, 1./dimTexture);
  vec2 texUV = tcoord.xy*texSize-0.5;
  vec2 w = fract(texUV);
  vec2 p = floor(texUV)+0.5;

  vec4 a0 = texture2D(tex, p*oneOvertexSize);
  vec4 a1 = texture2D(tex, (p+vec2(1, 0))*oneOvertexSize);
  vec4 a2 = texture2D(tex, (p+vec2(0, 1))*oneOvertexSize);
  vec4 a3 = texture2D(tex, (p+vec2(1, 1))*oneOvertexSize);

  if( a0.a < 0.5 && a1.a < 0.5 && a2.a < 0.5 && a3.a < 0.5 )
   if( disc)
    discard;
   else
    return -1;

  vec4 b0 = vec4(0.);
  if ( a0.a > 0.5 || a1.a > 0.5 )
  {
   if ( a0.a > 0.5 && a1.a > 0.5 )
     b0 = mix(a0, a1, w.x);
   else if ( a0.a > 0.5 )
	  b0 = a0;
	else if ( a1.a > 0.5 )
	  b0 = a1;
  }

  vec4 b1 = vec4(0.);
  if ( a2.a > 0.5 || a3.a > 0.5 )
  {
    if ( a2.a > 0.5 && a3.a > 0.5 )
	  b1 = mix(a2, a3, w.x);
    else if ( a2.a > 0.5 )
	  b1 = a2;
	else if ( a3.a > 0.5 )
	  b1 = a3;
  }

  // use fragment luminance for normal perturbation
  if ( b0.w > 0.5 && b1.w > 0.5)
    return dot(mix(b0, b1, w.y).xyz, luminance);
  
  if ( b0.w > 0.5 )
    return dot(b0.xyz, luminance);

  if ( b1.w > 0.5 )
    return dot(b1.xyz, luminance);
}

void main()
{
	vec2 newTexCoord = gl_TexCoord[0].st;
	
	mat3 TBN = computeTBN();
	vec3 tLightDir = normalize(TBN*lightDir);
	vec3 tView   = normalize(TBN*viewDir);
	
	float Hg, Ha, Hr;
	float decalOnePixel = 1.0/dimTexture;
	
	Hg = getData(texture, newTexCoord, true);
	Ha = getData(texture, newTexCoord + vec2(0.0, decalOnePixel), false);
	if ( Ha == -1 )
	  Ha = Hg;
	Hr = getData(texture, newTexCoord + vec2(decalOnePixel, 0.0), false);
	if ( Hr == -1 )
	  Hr = Hg;

	vec3 tNormal; // normal in texture space
	tNormal = vec3(depth*(Hg-Hr), depth*(Hg-Ha), 1.0);
	tNormal = normalize(tNormal);
	
	float diffuseCoeff  = abs(dot(tNormal, tLightDir));
	vec3 H = -reflect(tView, tNormal);
	float specularCoeff = max(dot(tLightDir, normalize(H)), 0.);
	specularCoeff = pow(specularCoeff, gl_FrontMaterial.shininess);

	vec4 indColor;
	if ( color.rgb == vec3( -1., -1., -1. ) )
		indColor = gl_Color;
	else
		indColor = color;
	
	gl_FragColor = gl_FrontLightModelProduct.sceneColor+
			 gl_FrontLightProduct[0].ambient+
			 indColor*diffuseCoeff+
			 gl_FrontLightProduct[0].specular*max(0.0, specularCoeff);
	gl_FragColor.w = indColor.w*gl_FrontMaterial.diffuse.w;
}
