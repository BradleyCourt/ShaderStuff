#pragma once
#include <string>

class MyTestShader
{
public:
	static unsigned int CompileShaders(const char* vsFile, const char* fsFile);
private:
	static bool LoadShaderFromFile(const char* filePath, std::string& code);
};