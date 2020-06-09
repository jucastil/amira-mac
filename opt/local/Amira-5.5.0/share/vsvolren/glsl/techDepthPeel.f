uniform sampler2D   u0s_DepthTexture;
uniform sampler2D   u0s_ColorTexture;
uniform vec4        u0v_TextureSize;
uniform vec4        u0v_DepthMultiply;
uniform vec4        u0v_ColorMultiply;
uniform vec4        u0v_ViewDir;

varying vec4        v_Normal;
varying vec4        v_ShadowCoord;

void main()
{
    vec4 coord = gl_FragCoord;

    // TODO: I believe that this mapping is wrong.
    //       Window coordinates in gl_FragCoord are always in the
    //       pixel centers (i.e, 0.5 1.5 2.5 ...) which means that
    //       a division by u0v_TextureSize should give the correct
    //       pixel to texel mapping. However, the uppermost and
    //       rightmost pixels look wrong.
    //       Thus, time should be spent to figure out the CORRECT
    //       vertex to viewport mapping. For the time beeing
    //       we use some workarounds.
    coord.x = (coord.x) / (u0v_TextureSize.x); // -1);
    coord.y = (coord.y) / (u0v_TextureSize.y); // -1);
    coord.w = 1.0;
 
    float depth = texture2D( u0s_DepthTexture, coord.xy).x;

    depth *= u0v_DepthMultiply.x;

    // This is an ordinary GL_LESS test - DON'T use gl_FragDepth
    // for reading, otherwise the depth value written by the shader
    // will be undefined.
    if (gl_FragCoord.z < depth + 0.00005) // 0.03) // 001)
      	discard;

    gl_FragColor = gl_Color;

    // Edge enhancement
    vec3 normal = normalize(v_Normal.xyz);
#if 1
    float u     = (1.0 - abs(dot(normal, u0v_ViewDir.xyz)));
    // u = max(0.8, u) - 0.8;
    u = u * u;
    u = u * u * u;
    // u = u * u;
    // float beta = (1+gl_Color.a)/2.0; // min(4*gl_Color.a, 1);
    // float beta = min(4*gl_Color.a, 1);
    float beta = 1.0;
    gl_FragColor.a += u*(beta - gl_Color.a);
#endif

#if 0
    // The amira style - does not really work here
    float cosfi = max(abs(dot(normal, u0v_ViewDir)), 0.001);
    float t     = 1.0 - gl_Color.a;
    gl_FragColor.a = 1.0 - pow(t, 1.0/cosfi);
#endif

    // gl_FragColor.r = 100 * gl_FragCoord.w; 
    // gl_FragColor.r = gl_FragCoord.w;
    // gl_FragColor.g = -gl_FragCoord.w;
    // gl_FragColor.r = coord.x;

//gl_FragColor = depth;
//gl_FragColor.x = u0v_TextureSize.x / 500;
//gl_FragColor.y = 0.5;
//gl_FragColor.a = 1.0;
}
