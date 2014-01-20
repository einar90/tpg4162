// ******************************************************************
// * TGP4162 Project 2: Visualization using OpenGL shader language *
// * Stein Dale/Thorvald Natvig, IPT, NTNU							*
// ******************************************************************

// Required uniform variables to solve Project.
// Remember texture values are within the domain [0.0, 1.0]
uniform float splitter;		// splitter value, domain [0.0, 1.0]
uniform sampler2D tex;		// sampler for helping to access texture value

// The framework vertex shader conveys the following varying attributes which can be used if you want. 
varying vec3 normal;		// interpolated surface normal
varying vec3 lightDir;		// interpolated vector pointing towards light source

void main()
{
	vec4 color;
	
	vec4 tx = texture2D(tex, gl_TexCoord[0].st);
	float v = tx[0];

	if (v > splitter)
	{
		color[0] = 1.0;
		color[1] = (1.0-v)/(1.0-splitter);
		color[2] = color[1];
	}
	else
	{
		color[0] = v/splitter;
		color[1] = color[0];
		color[2] = 1.0;
	}
	color[3] = 1.0;

	gl_FragColor = color;

}
