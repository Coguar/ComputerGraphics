uniform sampler2D colormap;
uniform sampler2D replaceColormap;

uniform float timer;
uniform vec2 CENTRE;

const float pi = 3.141592f;
const float tau = 4.0f;

const float WAVE_SPEED = 0.5;
const float WAVE_HEIGHT_FACTOR = 0.5;
const float WAVE_FRONT_LENGTH = 0.4;

float LineWaveFunc(float dist)
{
	return cos(2 * timer - 4 * dist - pi/2) * exp(-timer / tau) * 0.5;
}

float GetDistanceFromCentre(vec2 pos)
{
	// return sqrt(pow(pos.x - CENTRE.x, 2) + pow(pos.y - CENTRE.y, 2));
	return distance(pos, CENTRE);
}

float GetBlendingFactor(float radius, float dist)
{
	float delta = abs(radius - dist);
	if (delta <= WAVE_FRONT_LENGTH)
	{
		return 1 - (delta / WAVE_FRONT_LENGTH);
	}
	return 0;
}

vec2 GetOffsetVec(float length)
{
	vec2 pos = gl_TexCoord[0].xy;
	return normalize(pos - vec2(CENTRE.x, CENTRE.y)) * length * WAVE_HEIGHT_FACTOR;
}

void main()
{
	vec2 pos = gl_TexCoord[0].xy;

	float a = 1;
	float k = 0;
	float distance = WAVE_SPEED * timer;
	float dist = GetDistanceFromCentre(pos);

	if (dist <= distance)
	{
		a = GetBlendingFactor(dist, distance);
		k = 1;
	}

	float waveFactor = LineWaveFunc(dist);
	vec2 offset = GetOffsetVec(waveFactor) * k;
	vec4 mixedColor = mix(texture2D(colormap, pos + offset), texture2D(replaceColormap,  pos + offset), a);
	gl_FragColor = mixedColor * (1 - (waveFactor * k));
}
