#include "Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	if(vertexPath==NULL)
		throw std::ios_base::failure("vertexPath is NULL\n");
	if(fragmentPath==NULL)
		throw std::ios_base::failure("fragmentPath is NULL\n");

	this->vertexPath = vertexPath;
	this->fragmentPath = fragmentPath;

	// Resource type
	type = Resource::Type::Shader;

	// Read sources from files
	std::string vertexSource;
	try {
		utls::readFile(vertexPath, vertexSource);
	}
	catch(const std::ios_base::failure & e) {
		std::cout << "Caught an std::ios_base::failure\n"
							<< "Explanatory string: " << e.what() << '\n'
							<< "Error code: " << e.code() << '\n';
		throw;
	}

	std::string fragmentSource;
	try {
		utls::readFile(fragmentPath, fragmentSource);
	}
	catch(const std::ios_base::failure & e) {
		std::cout << "Caught an std::ios_base::failure\n"
							<< "Explanatory string: " << e.what() << '\n'
							<< "Error code: " << e.code() << '\n';
		throw;
	}

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

void Shader::setFloat(const char *uniformName, float value) const {
	activate();
	glUniform1f(glGetUniformLocation(ID, uniformName), value);
	}

void Shader::setInt(const char *uniformName, int value) const {
	activate();
	glUniform1i(glGetUniformLocation(ID, uniformName), value);
}

void Shader::setBool(const char *uniformName, bool value) const {
	activate();
	glUniform1i(glGetUniformLocation(ID, uniformName), (int)value);
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
		 << "|name:" << friendlyName
		 << "|OpenGL_ID:" << ID
		 << "|vert path:" << vertexPath
		 << "|frag path:" << fragmentPath
		 << "]";
}

