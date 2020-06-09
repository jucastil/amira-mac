vec4 VVizLighting(vec4 col, vec4 diffuseColor, vec4 specularColor, 
                  vec4 emissionColor, vec4 ambientColor,
                  vec2 diffSpecCoeffs)
{
  vec4 res;

  vec3 diffuse = diffSpecCoeffs.x*col.xyz*diffuseColor.xyz;
  vec3 specular = diffSpecCoeffs.y*specularColor.xyz;
  vec3 emission = emissionColor.xyz+vec3(2., 2., 2.);

  //Increase brightness with the material emission term
  res.xyz = (ambientColor.xyz+diffuse+specular)*emission;
  res.w = col.w;

  return res;
}
