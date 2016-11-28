uniform float TWIST;

void main()
{
	
	float angle = gl_Vertex.x;
	float Radius = 
	(1.f  + sin(angle)) * 
	(1.f + 0.9f * cos(8.f * angle)) * 
	(1.f + 0.1f * cos(24.f * angle)) * 
	(0.5f + 0.05f * cos(140.f * angle));
	
	vec4 kanabolaCoord = vec4(
	   gl_Vertex.x + (cos(angle) * Radius)  * TWIST ,
        gl_Vertex.y + (sin(angle) * Radius)  *TWIST ,
        gl_Vertex.z,
        gl_Vertex.w
);
      vec4 position = gl_ModelViewProjectionMatrix * kanabolaCoord ;
    // Transform twisted coordinate
    gl_Position = position;
    gl_FrontColor = (position + vec4(1.0)) * 0.5;
}
