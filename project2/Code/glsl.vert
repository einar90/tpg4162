varying vec3 normal, lightDir;		// varying variables are passed on to the fragment shader (interpolated)

void main()
{	
	lightDir = normalize(vec3(gl_LightSource[0].position));	// unit vector in the direction of GL_LIGHT0 (light zero)
	
	normal = normalize(gl_NormalMatrix * gl_Normal);		// transform vertex normal into eye coordinates

	// GL_TEXTURE0 texture coordinates passed in as a vertex attribute, and it is passed on 
	// by means of the built-in variable gl_TexCoord[] (varying variable; thus interpolated to fragment shader)
	gl_TexCoord[0] = gl_MultiTexCoord0;		
											
	gl_Position = ftransform();				// Compute vertex position in clip coordinates (positional invariance)
}
