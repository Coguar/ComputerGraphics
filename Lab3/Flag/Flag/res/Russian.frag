
const float PI =  3.14159265359;

bool PointIsOnTheLeft(vec2 p0, vec2 p1, vec2 p)
{
    vec2 p0p1 = p1 - p0;
    // find the orthogonal vector to p0p1
    vec2 n = vec2(-p0p1.y, p0p1.x);
    // Find the dot product between n and (p - p0)
    return dot(p - p0, n) > 0.0;
}

bool PointIsInsideTriangle(vec2 p0, vec2 p1, vec2 p2, vec2 p)
{
    return PointIsOnTheLeft(p0, p1, p) &&
           PointIsOnTheLeft(p1, p2, p) &&
           PointIsOnTheLeft(p2, p0, p);
}

vec2[5] CreateStarVertexes( vec2 center, float radius)
{
	vec2 starsVert[5];
	for(int i = 0; i < 5; ++i)
	{
		float angle = 2.0 * PI / 5.0 * i + (0.5 * PI);
		float x = center.x + (radius * cos(angle) / 2);
		float y = center.y + (radius * sin(angle));
		starsVert[i] = vec2(x, y);
	}
	return starsVert;
}

bool PointIsInsideStar(vec2 starsVert[5], vec2 p)
{
	bool isInT1 = PointIsInsideTriangle(starsVert[0], starsVert[2], starsVert[3], p);
	bool isInT2 = PointIsInsideTriangle(starsVert[1], starsVert[3], starsVert[4], p);
	bool isInT3 = PointIsInsideTriangle(starsVert[2], starsVert[4], starsVert[0], p);
	bool isInT4 = PointIsInsideTriangle(starsVert[3], starsVert[0], starsVert[1], p);

	int summ = 0;

if(isInT1)
	{
		summ =summ + 1;
	}
if(isInT2)
	{
		summ =summ + 1;
	}
if(isInT3)
	{
		summ =summ + 1;
	}
if(isInT4)
	{
		summ =summ + 1;
	}
if(summ >= 2)
{
	return true;
}
return false;
}

bool PointIsInsideQuadrangle(vec2 quardranglesVert[4], vec2 p)
{
	bool isInT1 = PointIsInsideTriangle(quardranglesVert[2], quardranglesVert[1], quardranglesVert[0], p);
	bool isInT2 = PointIsInsideTriangle(quardranglesVert[3], quardranglesVert[2], quardranglesVert[0], p);
	if (isInT1 || isInT2)
	{
		return true;
	}
	return false;
}

vec2[4] GetRotatedQuadrangle( float angle, vec2 quardranglesVert[4])
{
	vec2[4] rotatedQuardrangle;
	for(int i = 0; i < 4; ++i)
	{
		 rotatedQuardrangle[i].x = 0.5 * (quardranglesVert[i].x * cos(angle) - quardranglesVert[i].y * sin(angle));
         rotatedQuardrangle[i].y = quardranglesVert[i].x * sin(angle) + quardranglesVert[i].y * cos(angle);	
	}
	return rotatedQuardrangle;
}

vec2[4] GetPositionedQuadrangle(vec2 pos, vec2 quardranglesVert[4])
{
	vec2[4] positionedQuadrangle;
	for(int i = 0; i < 4; ++i)
	{
		positionedQuadrangle[i].x = quardranglesVert[i].x + pos.x;
		positionedQuadrangle[i].y = quardranglesVert[i].y + pos.y;
	}
	return positionedQuadrangle;
}

bool PointIsInsideTransformatedQuadrangle(vec2 quardranglesVert[4], vec2 p, float angle, vec2 pos)
{
	vec2[4] transformatedQuadrangle;
	transformatedQuadrangle = GetPositionedQuadrangle(pos, GetRotatedQuadrangle(angle, quardranglesVert));
	return PointIsInsideQuadrangle(transformatedQuadrangle, p);
}

bool PointInsideTransformatedEllipse(vec2 pos, vec2 size, vec2 p, float angle)
{
	float x1 = (p.x - pos.x);
	float y1 = (p.y - pos.y);
	float x = ((x1 * cos(angle))-(y1 * sin(angle)));
	float y = ((y1 * cos(angle))+(x1 * sin(angle)));

	float sizeX = size.x * (1 - 0.5 * cos(angle));
	float sizeY = size.y * (1 - 0.5 * sin(angle));


	float answer = ((x * x) / (sizeX * sizeX) ) + ((y * y) / (sizeY * sizeY));
	return (answer <= 1);
}

const float SCALE = 0.5;
const float Y_OFFSET = 0.6;
const vec2[4] HUMMER_HEAD = {vec2(0 * SCALE, 0* SCALE), vec2(0* SCALE, 0.3* SCALE), vec2(0.4* SCALE, 0.3* SCALE),vec2(0.55* SCALE, 0* SCALE)};
const float HUMMER_ANGLE = PI / 4.0;
const vec2 HUMMER_POS = vec2(0.35, 2.65 + Y_OFFSET);

const vec2[4] HUMMER_STICK = {vec2(0.15* SCALE, 0* SCALE), vec2(0.15* SCALE, -1.3* SCALE), vec2(0* SCALE, -1.3* SCALE),vec2(0* SCALE, 0* SCALE)};
const vec2 HUMMER_STICK_POS = vec2(0.35, 2.78+ Y_OFFSET);

const vec2 BIG_RADIUS = vec2(0.6* SCALE, 0.6* SCALE);
const vec2 SMALL_RADIUS = vec2(0.55* SCALE, 0.6* SCALE);
const vec2 BIG_POS = vec2(0.43, 2.7+ Y_OFFSET);
const vec2 SMALL_POS = vec2(0.38, 2.74+ Y_OFFSET);

const vec2[4] HANDLES_SQUARE = {vec2(0* SCALE, 0* SCALE), vec2(0* SCALE, 0.15* SCALE), vec2(0.15* SCALE, 0.15* SCALE),vec2(0.15* SCALE, 0* SCALE)};
const vec2 HANDLES_SQUARE_POS = vec2(0.325, 2.4+ Y_OFFSET);

const vec2[4] HANDLE = {vec2(0.1* SCALE, 0* SCALE), vec2(0.15* SCALE, -0.45* SCALE), vec2(-0.05* SCALE, -0.45* SCALE),vec2(0* SCALE, 0* SCALE)};
const vec2 HANDLE_POS = vec2(0.32, 2.45+ Y_OFFSET);


const vec4 YELLOW = vec4(1.0, 1.0, 0, 0);
const vec4 RED = vec4(1.0, 0, 0, 0);

void main()
{
    vec2 pos = gl_TexCoord[0].xy;
	vec2 star[5] = CreateStarVertexes(vec2(0.45, 3.75), 0.15);
	vec2 littleStar[5] = CreateStarVertexes(vec2(0.45, 3.75), 0.1);
if(PointIsInsideStar(star, pos) && !PointIsInsideStar(littleStar, pos) )
{
	gl_FragColor = YELLOW;
}
else if(PointIsInsideTransformatedQuadrangle(HUMMER_HEAD, pos, HUMMER_ANGLE, HUMMER_POS))
{
	gl_FragColor = YELLOW;
}
else if(PointIsInsideTransformatedQuadrangle(HUMMER_STICK, pos, HUMMER_ANGLE, HUMMER_STICK_POS))
{
	gl_FragColor = YELLOW;
}
else if(PointInsideTransformatedEllipse(BIG_POS, BIG_RADIUS, pos,  PI / 2) && 
							!PointInsideTransformatedEllipse(SMALL_POS, SMALL_RADIUS, pos, PI / 2))
{
	gl_FragColor = YELLOW;

}
else if(PointIsInsideTransformatedQuadrangle(HANDLES_SQUARE, pos, PI / 18, HANDLES_SQUARE_POS))
{
	gl_FragColor = YELLOW;
}
else if(PointIsInsideTransformatedQuadrangle(HANDLE, pos, -PI / 5, HANDLE_POS))
{
	gl_FragColor = YELLOW;
}
else
{
	gl_FragColor = RED;

}
}
