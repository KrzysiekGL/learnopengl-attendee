#include "Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	// Read sources from files
	std::string vertexSource;
	readFile(vertexPath, vertexSource);
	std::string fragmentSource;
	readFile(fragmentPath, fragmentSource);

	// Complie shaders
	GLuint vertexShader;
	if(!(vertexShader = buildShader(vertexSource, Type::Vertex)))
		std::cerr << "ERROR: Vertex shader " << vertexPath << " compilation failed\n";
	GLuint fragmentShader;
	if(!(fragmentShader = buildShader(fragmentSource, Type::Fragment)))
		std::cerr << "ERROR: Fragment shader " << fragmentPath << " compilation failed\n";
	assert(((vertexShader!=0) && (fragmentShader!=0)));

	// Create shader program object and link shaders
	if(!(ID = glCreateProgram()))
		std::cerr << "ERROR: Failed to create shader object\n";
	assert(ID!=0);
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	int success;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cerr << "ERROR: Shader program linking failed\n" << infoLog << '\n';
	}

	// Clean created shaders and leave only the shader program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::activate() const {
	glUseProgram(ID);
}

void Shader::deactivate() const {
	glUseProgram(0);
}

bool Shader::isActive() const {
	return active;
}

void Shader::readFile(std::string path, std::string & readBuf) {
	std::ifstream f(path, std::ios::ate);
	if(f.is_open()) {
		auto size = f.tellg();
		f.seekg(0);
		std::string str(size, '\0');
		try {
			f.read(&str[0], size);
		}
		catch(std::ifstream::failure e) {
			std::cerr << "ERROR: Error reading file " << path << '\n';
		}
		f.close();
		readBuf = str.c_str();
	}
	else
		std::cerr << "ERROR: Error opening file: " << path << '\n';
}

GLuint Shader::buildShader(std::string source, Type type) {
	// Create vertex shader object
	GLuint shader;
	switch(type) {
	case Vertex:
		if(!(shader = glCreateShader(GL_VERTEX_SHADER))) {
			std::cerr << "ERROR: Failed to create vertex shader object\n";
			return 0;
		}
		break;
	case Fragment:
		if(!(shader = glCreateShader(GL_FRAGMENT_SHADER))) {
			std::cerr << "ERROR: Failed to create fragment shader object\n";
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
		std::cerr << "ERROR: Shader compilation failed\n" << infoLog << '\n';
		return 0;
	}

	return shader;
}

