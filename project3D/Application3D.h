#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include "tiny_obj_loader.h"
#include "Model.h"

//struct OpenGLInfo
//{
//	unsigned int m_VAO;
//	unsigned int m_VBO;
//	unsigned int m_faceCount;
//};
//
//struct OBJVertex
//{
//	float x, y, z;
//	float nx, ny, nz;
//	float u, v;
//};

class Application3D : public aie::Application {
public:

	Application3D();
	virtual ~Application3D();

	void generateGrid();

	//Model* model;

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();


	//void Application3D::createOpenGLBuffers(tinyobj::attrib_t& attribs, std::vector<tinyobj::shape_t>& shapes);

	unsigned int LoadTexture(char * path);

protected:

	unsigned int m_texture;
	unsigned int m_programID;
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;
	std::vector<OpenGLInfo> m_glInfo;
	
};