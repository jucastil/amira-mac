//xy: uv width/height, z: 0|1 enable/disable atlas
uniform vec3 VVizAtlasOffset;

/** Clamp tcoord between min max of the subtexture atlas */
vec4 VVizComputeMinMaxTexCoord(vec2 tcoord)
{
  return vec4(gl_TexCoord[0].zw*VVizAtlasOffset.z,
              gl_TexCoord[0].zw*VVizAtlasOffset.z+VVizAtlasOffset.xy);
}
