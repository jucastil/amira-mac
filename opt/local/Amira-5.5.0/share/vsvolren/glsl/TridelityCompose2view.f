uniform sampler2D u0s_Mask;
uniform sampler2D u0s_Channel0;
uniform sampler2D u0s_Channel1;

void main()
{
    vec2 maskCoord  = vec2(gl_TexCoord[0].x, gl_TexCoord[0].y);
    vec3 tex = texture2D(u0s_Mask, maskCoord).rgb;
    vec3 itex = abs(tex - vec3(1.0, 1.0, 1.0)); // inverse texture

    vec2 coord  = vec2(gl_TexCoord[1].x, gl_TexCoord[1].y);
    vec3 color1 = texture2D(u0s_Channel0, coord).rgb;
    vec3 color2 = texture2D(u0s_Channel1, coord).rgb;

    gl_FragColor.xyz = tex * color1 + itex * color2;
    gl_FragColor.a = 1.0;
}
