/**
    Raycasting of a cylinder.
    ========================

    This shader raycasts a cylinder for orthographic projection
    and cuts it with a slice.

    input: cylinder start point = gl_Vertex.xyz
           cylinder end point   = gl_MultiTexCoord0.xyz
           color                = gl_Color;
           radius               = uniform float "radius"
           slice                = uniform vec4 "slice"
           slice height         = uniform float "sliceHeight"


    Vertex Shader:

    Applies the modelview matrix to the end points of the
    cylinder. 

    
    Geometry Shader:

    Computes a thight square for the cylinder and the
    ray start and direction for raycasting.


    Fragment Shader:

    Computes the intersection points of the ray and the
    cylinder. Compares the points with the slice and 
    computes the intersection with the slice if necessary.

    author: Norbert Lindow
*/






varying vec4 cylinder;
varying vec3 color;
varying vec3 rayStart;
varying vec4 rayDirection;
varying vec4 rotation;

uniform vec4  slice;
uniform float sliceHeight;



/*
    Quaternion multiplikation.
*/
vec4 qMul(vec4 q1, vec4 q2)
{
    return vec4((q1.w * q2.xyz) + (q2.w * q1.xyz) + cross(q1.xyz, q2.xyz), q1.w * q2.w - dot(q1.xyz, q2.xyz));
}




/*
    Point rotation with quaternion. Axe must have unit length.
*/
vec3 rotatePoint (vec3 point, vec3 axis, float angle)
{
    vec4 q  = vec4(sin(angle * 0.5) * axis, cos(angle * 0.5));

    vec4 qC = vec4(-1.0 * q.xyz, q.w);
    vec4 x  = vec4(point, 0.0);
    vec4 res = qMul(qMul(q, x), qC);

    return res.xyz;
}




/*
    Helper function for isecCylinder.
*/
float dotC(vec3 v1, vec3 v2)
{
    return v1.x * v2.x + v1.z * v2.z;
}




/* 
  Returns the intersection points of a ray and a cylinder.
  The ray starts at rs and has direction rd. The cylinder
  has midpoint in zero position and radius r. The cylinder
  axis is equal to the y-axis.
*/
void isecCylinder(vec3 rs, vec3 rd, float r, out vec3 isec_first, out vec3 isec_second)
{
    float w = 1.0 / dotC(rd, rd);
    float p = 2.0 * dotC(rs, rd) * w;
    float q = (dotC(rs, rs) - r * r) * w;

    w = p * p * 0.25 - q;

    if (w < 0.0) discard;

    w = sqrt(w);
    p = -0.5 * p;
    
    isec_first  = rs + (p + w) * rd;
    isec_second = rs + (p - w) * rd;
}




/*
   Returns gradient of a cylinder in zero position and y-axis direction.
*/
vec3 gradCylinder(vec3 p)
{
    return normalize(vec3(-2.0 * p.x, 0.0, -2.0 * p.z));
}



/*
    Returns the angle between two 3d vectors.
*/
float angle(vec3 x, vec3 y)
{
    return acos(dot(x,y) / (length(x) * length(y)));
}




/*
    Returns the intersection point of a ray and a plane.
*/
vec3 isecPlane(vec3 pPosition, vec3 pNormal, vec3 rStart, vec3 rDirection)
{
    vec3  rS = rStart - pPosition;
    vec3  n  = pNormal;
    vec3  rD = rDirection;
    float t  = -dot(rS, n) / dot(rD, n);

    return rS + t * rD + pPosition;
}




/*
    Returns true if y-Value of p is between -h and h and if 
    p lies beween the plane with position c_P and normal
    c_N and the same plane moved backward by s_H.
*/
bool isValid(vec3 p, float h, vec3 c_P, vec3 c_N, float s_H)
{
    return (dot(p - c_P, c_N) <= 0.0  && dot(p - c_P, c_N) >= -s_H*2.0 && abs(p.y) <= h);
}




void main (void)
{
    vec3  rd    = normalize(rayDirection.xyz);
    vec3  rs    = rayStart;
    vec3  m     = cylinder.xyz;
    float r     = cylinder.w;
    float h     = rayDirection.w;

    // cut transformation
    vec3 c_p = vec3(gl_ModelViewMatrix * vec4(slice.xyz * slice.w, 1.0)) - m;
    vec3 c_n = normalize(vec3(gl_ModelViewMatrix * vec4(slice.xyz, 0.0)));

    c_p = rotatePoint(c_p + abs(sliceHeight) * c_n, rotation.xyz, rotation.w);
    c_n = rotatePoint(c_n, rotation.xyz, rotation.w);

    vec3 p_first;
    vec3 p_second;

    isecCylinder(rs, rd, r, p_first, p_second);

    vec3 p  = p_first;
    vec3 n  = gradCylinder(p);

    /*
        if first point is not valid, 
        try intersection point with plane
        and afterwards try second point
    */
    if (!isValid(p, h, c_p, c_n, sliceHeight))
    {
        p  = isecPlane(c_p, c_n, rs, rd);
        n  = -c_n;

        if (p.x * p.x + p.z * p.z > r * r  || abs(p.y) > h)
        {
            p  = p_second;
            n  = gradCylinder(p);

            if (!isValid(p, h, c_p, c_n, sliceHeight)) discard;
        }
    }

    // back transformation, depth computation
    p = rotatePoint(p, rotation.xyz, -rotation.w);
    p = p + m;

    vec4 np = gl_ProjectionMatrix * vec4(p, 1.0);

    gl_FragDepth = ((np.z / np.w) + 1.0) * 0.5; 
    gl_FragColor = vec4(/*abs(dot(n, rd)) * */color, 1.0);

}