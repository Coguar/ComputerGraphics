varying vec3 n;
varying vec3 v;
varying vec3 viewSpace;

void main(void)
{

    // Transform the vertex:
    // gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex
    gl_Position = ftransform();
    // Copy texture coordinates from gl_MultiTexCoord0 vertex attribute
    // to gl_TexCoord[0] varying variable
    gl_TexCoord[0] = gl_MultiTexCoord0;

    v = vec3(gl_ModelViewMatrix * gl_Vertex);
    n = normalize(gl_NormalMatrix * gl_Normal);
    gl_Position = ftransform();

	viewSpace = gl_ModelViewProjectionMatrix *  gl_ModelViewMatrix *  gl_Position;

}
