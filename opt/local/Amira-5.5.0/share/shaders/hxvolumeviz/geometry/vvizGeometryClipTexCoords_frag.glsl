uniform vec3 VVizMinUvw;
uniform vec3 VVizMaxUvw;


void
VVizClipGeometry()
{
  vec3 epsilon = vec3(1e-5);

  // driver bug: the original code was:
  //
  // if ( any(lessThan(gl_TexCoord[0].xyz, VVizMinUvw-epsilon)) ||
  //      any(greaterThan(gl_TexCoord[0].xyz, VVizMaxUvw+epsilon)) )
  //  discard;
  //
  // but due to driver issues, we have to do this trick, else it does not compil
  // in macOS

  bool mustDiscard = (any(lessThan(gl_TexCoord[0].xyz, VVizMinUvw-epsilon)) 
              || any(greaterThan(gl_TexCoord[0].xyz, VVizMaxUvw+epsilon)));

  if ( !mustDiscard ) 
    return;

  discard;
}
