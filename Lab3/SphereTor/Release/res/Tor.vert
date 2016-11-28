

varying vec3 n;
varying vec3 v;

uniform float TWIST;
const float PI =  3.14159265359;
const vec2 IDENTITY_VEC_X = vec2(1, 0);


float GetDistance(vec2 A, vec2 B)
{
	float x = A.x - B.x;
	float y = A.y - B.y;
	return sqrt(x * x + y * y);
}

void main()
{

	v = vec3(gl_ModelViewMatrix * gl_Vertex);
	n = normalize(gl_NormalMatrix * gl_Normal);


	float x = gl_Vertex.x;
	float y = gl_Vertex.y;
	float z = gl_Vertex.z;

	float a = GetDistance(vec2(x, y), IDENTITY_VEC_X);
	float b = 1;
	float c = GetDistance(vec2(x, y), vec2(0,0));
	 
	float Xangle = acos((b * b + c * c - a * a) / (2 * b * c)) * 2;
	
	if(y < 0)
	{
		Xangle = -Xangle;
	}
	Xangle *= 1.1;
	a = GetDistance(vec2(x, z), IDENTITY_VEC_X);
	b = 1;
	c = GetDistance(vec2(x, z), vec2(0,0));
	 
	float Yangle = acos((b * b + c * c - a * a) / (2 * b * c));
	if(z < 0)
	{
		Yangle = -Yangle;
	}

	float R = 1 * TWIST;
	float r = 0.5 * TWIST;

	vec4 torCoor = vec4(
	    (gl_Vertex.x * (1 - abs(TWIST) / 2)) + (R + r * cos(Yangle)) * cos(Xangle),
	    (gl_Vertex.y * (1 - abs(TWIST) / 2)) + (R + r * cos(Yangle)) * sin(Xangle),
	    (gl_Vertex.z * (1 - abs(TWIST) / 2)) + r * sin(Yangle),
        gl_Vertex.w
	);
      vec4 position = gl_ModelViewProjectionMatrix * torCoor ;
    // Transform twisted coordinate
    gl_Position = position;
    gl_FrontColor = (position + vec4(1.0)) * 0.5;
}
