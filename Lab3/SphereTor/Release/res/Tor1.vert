

// TODO: rename n to normal
varying vec3 n;
// TODO: rename v to vertex
varying vec3 v;
// TODO: rename to MORPH_LEVEL
uniform float TWIST;
const float PI =  3.14159265359 * 1.25;



void main()
{
	v = vec3(gl_ModelViewMatrix * gl_Vertex);
	n = normalize(gl_NormalMatrix * gl_Normal);

	float u = gl_Vertex.y / 1.0 * (PI) + PI * gl_Vertex.y;
	float t = gl_Vertex.z / 1.0 * PI ;
	   // u += PI * gl_Vertex.y;


	t = (t + PI);

	float R = TWIST * 2.0;
	float r = TWIST * 1.0;

	vec4 torCoor = vec4(
	    (gl_Vertex.x * (1 - abs(TWIST) / 2)) +(R + r * cos(u)) * cos(t),
	    (gl_Vertex.y * (1 - abs(TWIST) / 2)) +(R + r * cos(u)) * sin(t),
	    (gl_Vertex.z * (1 - abs(TWIST) / 2)) + r * sin(u),
        gl_Vertex.w
	);
	vec4 position = gl_ModelViewProjectionMatrix * torCoor ;
    // Transform twisted coordinate
    gl_Position = position;
    gl_FrontColor = (position + vec4(1.0)) * 0.5;
}
