#include "Shader.hpp"

std::atomic<GLuint> Shader::occupantShaderID(0);

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	assert(vertexPath!=NULL);
	assert(fragmentPath!=NULL);

	// Resource type
	type = Resource::Type::Shader;

	// Read sources from files
	std::string vertexSource;
	utls::readFile(vertexPath, vertexSource);
	std::string fragmentSource;
	utls::readFile(fragmentPath, fragmentSource);

	// Compile shaders
	GLuint vertexShader;
	if(!(vertexShader = buildShader(vertexSource, Type::Vertex)))
		std::cerr << "ERROR: (Shader::Shader) Vertex shader " << vertexPath << " compilation failed\n";
	GLuint fragmentShader;
	if(!(fragmentShader = buildShader(fragmentSource, Type::Fragment)))
		std::cerr << "ERROR: (Shader::Shader) Fragment shader " << fragmentPath << " compilation failed\n";
	assert(((vertexShader!=0) && (fragmentShader!=0)));

	// Create shader program object and link shaders
	if(!(ID = glCreateProgram()))
		std::cerr << "ERROR: (Shader::Shader) Failed to create shader object\n";
	assert(ID!=0);
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	int success;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cerr << "ERROR: (Shader::Shader) Shader program linking failed\n" << infoLog << '\n';
	}

	// Clean created shaders and leave only the shader program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLint Shader::activate() const {
	// If any other thread is using OpenGL glProgram, wait till it's done
	GLuint expectedProgram = 0;
	GLuint counter = 0;
	while(
		!occupantShaderID.compare_exchange_weak(expectedProgram, ID) &&
		counter<=300
	)
	{
		++counter;
		expectedProgram = 0;
	}
	if(expectedProgram!=0) {
		std::cerr << "ERROR: (Shader::Activate) Couldn't activate Shader ID: " << ID
							<< " Currently used Shader ID is: " << expectedProgram << "\n";
		return expectedProgram;
	}

	glUseProgram(ID);
	return 0;
}

void Shader::deactivate() const {
	// Just to be safe, make sure that the deactivating itself shader is acutally occupying OpenGL
	if(occupantShaderID.load()!=ID)
		std::cerr << "Shader ID: " << ID << " is not active to be deactivated\n";
	glUseProgram(0);
	occupantShaderID.store(0);
}

GLint Shader::currentlyActivated() {
	GLint progID;
	glGetIntegerv(GL_CURRENT_PROGRAM, &progID);
	return progID;
}

void Shader::setFloat(const char *uniformName, float value) const {
	activate();
	glUniform1f(glGetUniformLocation(ID, uniformName), value);
	deactivate();
	}

void Shader::setInt(const char *uniformName, int value) const {
	activate();
	glUniform1i(glGetUniformLocation(ID, uniformName), value);
	deactivate();
}

void Shader::setBool(const char *uniformName, bool value) const {
	activate();
	glUniform1i(glGetUniformLocation(ID, uniformName), (int)value);
	deactivate();
}

GLuint Shader::buildShader(std::string source, Type type) {
	// Create vertex shader object
	GLuint shader;
	switch(type) {
	case Vertex:
		if(!(shader = glCreateShader(GL_VERTEX_SHADER))) {
			std::cerr << "ERROR: (Shader::buildShader) Failed to create vertex shader object\n";
			return 0;
		}
		break;
	case Fragment:
		if(!(shader = glCreateShader(GL_FRAGMENT_SHADER))) {
			std::cerr << "ERROR: (Shader::buildShader) Failed to create fragment shader object\n";
			return 0;
		}
		break;
	default:
		return 0;
	}

	// Compile shader
	const char * cSource = source.c_str();
	glShaderSource(shader, 1, &cSource, NULL);
	glCompileShader(shader);
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "ERROR: (Shader::buildShader) Shader compilation failed\n" << infoLog << '\n';
		return 0;
	}

	return shader;
}

void Shader::print(std::ostream & os) const {
	os << "[type:Shader"
		 << "|resID:"<< resID
		 << "|OpenGL_ID:" << ID
		 << "|name:" << friendlyName
		 << "]";
}

