uniform sampler2D   u0s_Result;

uniform vec4        u0v_LightO;
uniform vec4        u0v_HalfwayO;
uniform vec4        u0v_Specular;
uniform vec4        u0v_IsoColor;
uniform vec4        u0v_Ambient;


void main()
{
    vec4 data    = texture2D( u0s_Result, gl_TexCoord[0].xy );
    gl_FragColor = vec4( data.a,data.a,data.a,data.a  );

    if ( data.a==0.0 )
        discard;

    vec3 norm = data.xyz - 0.5;

       
    float Idiff =  abs( dot( norm, u0v_LightO.rgb   ) );
    float Ispec =       dot( norm, u0v_HalfwayO.rgb )  ;

    Ispec *= Ispec * Ispec * Ispec;

    gl_FragColor.rgb = (u0v_Ambient.x + Idiff) * u0v_IsoColor.rgb + Ispec * u0v_Specular.rgb;
    gl_FragColor.a = 1.0;
}
