#include "Shader.h"
#include <gl_core_4_4.h>


Shader::Shader()
{
}


Shader::~Shader()
{
}
// function to create a grid

int Shader::Gradient()
{
	int m_programID;
	//const char* vsSource = "#version 410\n \
	//						layout(location=0) in vec4 position; \
	//						layout(location=1) in vec4 colour; \
	//						out vec4 vColour; \
	//						uniform mat4 projectionViewWorldMatrix; \
	//						void main() { vColour = colour; gl_Position = projectionViewWorldMatrix * position; }";

	//const char* fsSource = "#version 410\n \
	//						in vec4 vColour; \
	//						out vec4 fragColor; \
	//						void main() { fragColor = vColour; }";

	const char* vsSource = "#version 410\n \
							layout(location=0) in vec4 position; \
							layout(location=1) in vec4 colour; \
							out vec4 vColour; \
							uniform mat4 projectionViewWorldMatrix; \
							uniform float time; \
							uniform float heightScale; \
							void main() { vColour = colour; vec4 P = position; P.y += sin( time + position.x ) * heightScale; gl_Position = projectionViewWorldMatrix * P;}";

	const char* fsSource = "#version 410\n \
							in vec4 vColour; \
							out vec4 fragColor; \
							void main() { fragColor = vColour; }";


	int success = GL_FALSE;
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(fragmentShader);

	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertexShader);
	glAttachShader(m_programID, fragmentShader);
	glLinkProgram(m_programID);

	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];

		glGetProgramInfoLog(m_programID, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}

	
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	return m_programID;
}