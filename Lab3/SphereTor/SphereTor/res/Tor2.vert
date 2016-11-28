

// TODO: rename n to normal
varying vec3 normal;
// TODO: rename v to vertex
varying vec3 vertex;
// TODO: rename to MORPH_LEVEL
uniform float MORPH_LEVEL;
const float PI =  3.14159265359;



void main()
{
	vertex = vec3(gl_ModelViewMatrix * gl_Vertex);

//vec3 norm =
	//normal = normalize(gl_NormalMatrix * );

	float u = gl_Vertex.x;
	float v = gl_Vertex.z;


	v = (v + PI);

	float R = MORPH_LEVEL * 2.0;
	float r = MORPH_LEVEL * 1.0;

	const float radius = 1.f;

	const float latitude = float(PI) * (1.f - v); // 𝝅∙(𝟎.𝟓-𝒗)
	const float longitude = float(2.0 * PI) * u; // 𝟐𝝅∙𝒖
	const float latitudeRadius = radius * sin(latitude);


	vec4 torCoor = vec4(
	    (cos(longitude) * latitudeRadius * (1 - abs(MORPH_LEVEL) / 2)) +(R + r * cos(u)) * cos(v),
	    (cos(latitude) * radius * (1 - abs(MORPH_LEVEL) / 2)) +(R + r * cos(u)) * sin(v),
	    (sin(longitude) * latitudeRadius * (1 - abs(MORPH_LEVEL) / 2)) + r * sin(u),
        gl_Vertex.w
	);

	u = gl_Vertex.x + PI / 80;
	vec4 torCoor1 = vec4(
	    (cos(longitude) * latitudeRadius * (1 - abs(MORPH_LEVEL) / 2)) +(R + r * cos(u )) * cos(v),
	    (cos(latitude) * radius * (1 - abs(MORPH_LEVEL) / 2)) +(R + r * cos(u)) * sin(v),
	    (sin(longitude) * latitudeRadius * (1 - abs(MORPH_LEVEL) / 2)) + r * sin(u),
	    gl_Vertex.w
	);

	u = gl_Vertex.x;
	v = gl_Vertex.z + PI / 80;

	vec4 torCoor2 = vec4(
	    (cos(longitude) * latitudeRadius * (1 - abs(MORPH_LEVEL) / 2)) +(R + r * cos(u)) * cos(v),
	    (cos(latitude) * radius * (1 - abs(MORPH_LEVEL) / 2)) +(R + r * cos(u)) * sin(v),
	    (sin(longitude) * latitudeRadius * (1 - abs(MORPH_LEVEL) / 2)) + r * sin(u),
	    gl_Vertex.w
	);


	vec3 v1  = vec3(torCoor1.x, torCoor1.y, torCoor1.z) - vec3(torCoor.x, torCoor.y, torCoor.z);
	vec3 v2 = vec3(torCoor2.x, torCoor2.y, torCoor2.z) - vec3(torCoor.x, torCoor.y, torCoor.z);

	float a = abs(MORPH_LEVEL) / 2;

	vec3 norm = normalize(cross(v1, v2));
	if(abs(a) < 0.05)
	{
		norm = vec3(torCoor.x, torCoor.y, torCoor.z);
	}

	normal = normalize(gl_NormalMatrix * norm);

	vec4 position = gl_ModelViewProjectionMatrix * torCoor ;
    // Transform twisted coordinate
    gl_Position = position;
    gl_FrontColor = (position + vec4(1.0)) * 0.5;
}
