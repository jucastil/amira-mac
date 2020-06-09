varying vec3 VVizLightingVec;

vec4 VVizLighting(vec4 col, vec4 diffuseColor, vec4 specularColor, 
                  vec4 emissionColor, vec4 ambientColor,
                  vec2 diffSpecCoeffs)
{
  vec4 res;
  float lightLength = length(VVizLightingVec);
   
  float attInv = gl_LightSource[0].constantAttenuation +
                 gl_LightSource[0].linearAttenuation * lightLength +
                 gl_LightSource[0].quadraticAttenuation * lightLength * lightLength;
  
  // fix driver bug: constant, linear and quadratic attenuations should by default (1, 0, 0)
  // Some drivers set it to (0, 0, 0). In such a case, set attenuation to 1 (no attenuation)
  if ( attInv <= 0 )
    attInv = 1.0; 

  float att = 1.0/attInv;

  res = gl_FrontMaterial.emission+
        gl_FrontMaterial.ambient*col+
        att*(diffSpecCoeffs.x*diffuseColor*col+specularColor*diffSpecCoeffs.y);
  res.w = col.w;  
 
  return res;
}
