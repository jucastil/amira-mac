 uniform sampler2D colorTex;
 uniform vec2 VVizOneOverVp;

void main()
{
    vec2 tcoord = gl_FragCoord.xy*VVizOneOverVp;
    vec4 col = texture2D(colorTex, tcoord);
   if ( col.w < 0.95 )
     discard;
}
