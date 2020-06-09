uniform sampler2D u0s_Channel0;
uniform sampler2D u0s_Channel1;
uniform sampler2D u0s_Channel2;
uniform sampler2D u0s_Channel3;
uniform sampler2D u0s_Channel4;

void main()
{
    vec2 coord  = vec2( gl_TexCoord[0].x, gl_TexCoord[0].y );
    vec3 color1 = texture2D( u0s_Channel0, coord ).rgb;
    vec3 color2 = texture2D( u0s_Channel1, coord ).rgb;
    vec3 color3 = texture2D( u0s_Channel2, coord ).rgb;
    vec3 color4 = texture2D( u0s_Channel3, coord ).rgb;
    vec3 color5 = texture2D( u0s_Channel4, coord ).rgb;
//               "    color5 = vec4( 1.0, 0.0, 0.0, 1.0 );
    float xx = mod(gl_FragCoord.x, 5.0);
    float yy = mod(gl_FragCoord.y, 5.0);
    float pre1 = floor(xx*0.5);
    float pre2 = 3.0*mod(xx,2.0);
    float pre3 = mod(pre1 + pre2 + yy, 5.0);
    int rest = int(pre3);
    if (rest == 3)
    {
        color1.yz  = vec2(0, 0);
        color2.xz  = vec2(0, 0);
        color3.xy  = vec2(0, 0);
        color4.xyz = vec3(0, 0, 0);
        color5.xyz = vec3(0, 0, 0);
    }
    if (rest == 0)
    {
        color1.xyz = vec3(0, 0, 0);
        color2.xyz = vec3(0, 0, 0);
        color3.yz  = vec2(0, 0);
        color4.xz  = vec2(0, 0);
        color5.xy  = vec2(0, 0);
    }
    if (rest == 2)
    {
        color1.xz  = vec2(0, 0);
        color2.xy  = vec2(0, 0);
        color3.xyz = vec3(0, 0, 0);
        color4.xyz = vec3(0, 0, 0);
        color5.yz  = vec2(0, 0);
    }
    if (rest == 4)
    {
        color1.xyz = vec3(0, 0, 0);
        color2.yz  = vec2(0, 0);
        color3.xz  = vec2(0, 0);
        color4.xy  = vec2(0, 0);
        color5.xyz = vec3(0, 0, 0);
    }
    if (rest == 1) 
    {
        color1.xy  = vec2(0, 0);
        color2.xyz = vec3(0, 0, 0);
        color3.xyz = vec3(0, 0, 0);
        color4.yz  = vec2(0, 0);
        color5.xz  = vec2(0, 0);
    } 
    gl_FragColor.xyz = color1 + color2 + color3 + color4 + color5;
    gl_FragColor.a = 1.0;
}
