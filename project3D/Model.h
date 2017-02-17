#pragma once
#include <Texture.h>
#include <gl_core_4_4.h>
#include <tiny_obj_loader.h>
#include <glm/glm.hpp>
#include <glm\ext.hpp>



struct OBJVertex
{
	float x, y, z;
	float nx, ny, nz;
	float u, v;
};

struct OpenGLInfo
{
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_faceCount;
}; 
class Model
{
private:

	aie::Texture m_tex;
	tinyobj::attrib_t m_attribs;
	std::vector<tinyobj::shape_t> m_shapes;
	std::vector<tinyobj::material_t> m_materials;
	std::vector<OpenGLInfo>glInfo; 
	unsigned int m_texure;

public:

	//void createBuffers(std::vector<OpenGLInfo>& glInfo);

	void createBufferOBJ();

	//void cleanupOpenGLBuffers();
	/*FBXFile* m_fbx; 
	unsigned int m_program;*/

	void Model::Draw(glm::mat4 transform, glm::mat4 cameraMatrix, unsigned int programID);

	Model();
	~Model();
	bool loadModel(const char * filename, const char * textureFile);
};

