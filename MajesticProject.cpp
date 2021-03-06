// MajesticProject.cpp: definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include "window.h"
#define LOG(x) std::cout<<x;

struct ShaderProgramSource {

	std::string vertexShader;
	std::string fragmentShader;

};


unsigned int CompileShader(const std::string& source, unsigned int type) {

	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {

		int lenght;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
		char* message = (char*)alloca(lenght * sizeof(char));
		glGetShaderInfoLog(id, lenght, &lenght, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "shader") << "shader" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;

	}


	return id;

}

unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {

	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;

}
ShaderProgramSource ParseShader(const std::string& filePath) {

	std::fstream stream(filePath);

	enum class ShaderType {

		NONE = -1, VERTEX = 0, FRAGMENT = 1

	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)) {

		if (line.find("#shader") != std::string::npos) {

			if (line.find("vertex") != std::string::npos) {

				type = ShaderType::VERTEX;

			}
			else if (line.find("fragment") != std::string::npos) {


				type = ShaderType::FRAGMENT;
			}


		}
		else {

			ss[(int)type] << line << '\n';

		}

		return { ss[0].str(), ss[1].str() };


	}
}

int main()
{
	window Window("Majestic", 1280, 780);
	glClearColor(0.0f, 0.5f, 1.0f, 0.8f);


	if (glewInit() != GLEW_OK) {
		LOG("GLEW failed!");
	}

	float positions[6] = { -0.5f, -0.5f, 0.0f,0.5f, 0.5f, -0.5f };

	//Triangle buffer
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	//Shader
	/*ShaderProgramSource source = ParseShader("Basic.shader");
	std::cout << source.vertexShader << std::endl;
	std::cout << source.fragmentShader << std::endl;*/

	while (!Window.Closed())
	{
		Window.Clear();
		/*glBegin(GL_POLYGON);
		glVertex2f(0,0.2f);
		glVertex2f(0.1, 0);
		glVertex2f(-0.1f,0);
		glVertex2f(0, -0.2f);
		glEnd();*/
		glDrawArrays(GL_TRIANGLES, 0, 3);
		Window.update();

	}


	return 0;
}


