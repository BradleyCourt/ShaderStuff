#include "Application3D.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Camera.h"
#include <gl_core_4_4.h>
#include <Shader.h>
#include <MyTestShader.h>
#include "Model.h"
#define STB_IMAGE_IMPLEMENTATION 
#include <Texture.h>
#include "imgui_glfw3.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;
Camera camera;
Model sphere;
//Shader shader = Shader();

struct Vertex
{
	glm::vec4 position;
	glm::vec4 colour;
};

unsigned int m_VAO;
unsigned int m_VBO;
unsigned int m_IBO;

int rows = 80, cols = 80;
//unsigned int m_programID;//////////////
//unsigned int m_texture;
float heightScale = 1.0f;

Application3D::Application3D() {

}

Application3D::~Application3D() {

}

void Application3D::generateGrid()
{
	Vertex* aoVertices = new Vertex[rows * cols];
	for (unsigned int r = 0; r < rows; ++r)
	{
		for (unsigned int c = 0; c < cols; ++c)
		{
			aoVertices[r * cols + c].position = glm::vec4((float)c * 0.1 , 0, (float)r * 0.1, 1);

			glm::vec3 colour = glm::vec3(sinf((c / (float)(cols - 1)) * (r / (float)(rows - 1)))); aoVertices[r * cols + c].colour = glm::vec4(colour, 1);

		}
	}

	// defining index count based off quad count (2 triangles per quad)
	unsigned int* auiIndices = new unsigned int[(rows - 1) * (cols - 1) * 6];
	unsigned int index = 0;
	for (unsigned int r = 0; r < (rows - 1); ++r)
	{
		for (unsigned int c = 0; c < (cols - 1); ++c)
		{
			//triangle 1
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);

			//triangle 2
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);
			auiIndices[index++] = r * cols + (c + 1);
		}
	}

	
	//Add the following line to generate a VertexArrayObject
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (rows * cols) * sizeof(Vertex), aoVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (rows - 1) * (cols - 1) * 6 * sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);


	// ....Code Segment here to bind and fill VBO + IBO from previous pages
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete[] aoVertices;
	
}

//void Application3D::createOpenGLBuffers(tinyobj::attrib_t& attribs, std::vector<tinyobj::shape_t>& shapes)
//	{
//	m_glInfo.resize(shapes.size());
//	// grab each shape
//	int shapeIndex = 0;
//	for (auto& shape : shapes)
//	{
//		// setup OpenGL data
//		glGenVertexArrays(1, &m_glInfo[shapeIndex].m_VAO);
//		glGenBuffers(1, &m_glInfo[shapeIndex].m_VBO);
//		glBindVertexArray(m_glInfo[shapeIndex].m_VAO);
//		m_glInfo[shapeIndex].m_faceCount = shape.mesh.num_face_vertices.size();
//
//		// collect triangle vertices
//		std::vector<OBJVertex> vertices;
//		int index = 0;
//		for (auto face : shape.mesh.num_face_vertices)
//		{
//			for (int i = 0; i < 3; ++i)
//			{
//				tinyobj::index_t idx = shape.mesh.indices[index + i];
//				OBJVertex v = { 0 };
//				// positions
//				v.x = attribs.vertices[3 * idx.vertex_index + 0];
//				v.y = attribs.vertices[3 * idx.vertex_index + 1];
//				v.z = attribs.vertices[3 * idx.vertex_index + 2];
//				// normals
//				if (attribs.normals.size() > 0)
//				{
//					v.nx = attribs.normals[3 * idx.normal_index + 0];
//					v.ny = attribs.normals[3 * idx.normal_index + 1];
//					v.nz = attribs.normals[3 * idx.normal_index + 2];
//				}
//				// texture coordinates
//				if (attribs.texcoords.size() > 0)
//				{
//					v.u = attribs.texcoords[2 * idx.texcoord_index + 0];
//					v.v = attribs.texcoords[2 * idx.texcoord_index + 1];
//				}
//				vertices.push_back(v);
//			}
//			index += face;
//		}
//		// bind vertex data
//		glBindBuffer(GL_ARRAY_BUFFER, m_glInfo[shapeIndex].m_VBO);
//		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(OBJVertex), vertices.data(), GL_STATIC_DRAW);
//
//		glEnableVertexAttribArray(0); //position
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OBJVertex), 0);
//
//		glEnableVertexAttribArray(1); //normal data
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(OBJVertex), (void*)12);
//
//		glEnableVertexAttribArray(2); //texture data
//		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(OBJVertex), (void*)24);
//
//		glBindVertexArray(0);
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		shapeIndex++;
//	}
//	
//}

unsigned int Application3D::LoadTexture(char* path)
{
	aie::Texture* tex = new aie::Texture();
	tex->load(path);
	return tex->getHandle();
}

bool Application3D::startup() {
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms

	/*tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;*/

	//m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	//m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
	//									  getWindowWidth() / (float)getWindowHeight(),
	//								  0.1f, 1000.f);

	//Model* m = new Model();
	/*glm::mat4 cameraMatrix = m_projectionMatrix * m_viewMatrix;
	mat4 modelMatrix = glm::translate(vec3(0));*/
	sphere.loadModel("data/stanford/Handgun_obj.obj", "data/Textures/handgun_C.jpg");
	//sphere.loadModel("../project3D/Models/earth.obj");
	//sphere.Draw(modelMatrix, cameraMatrix, m_programID);
	//	m->createOpenGLBuffers(m_glInfo);

	//aie::Texture texLocation;
	//texLocation.load("data/textures/earth_lights.jpg");
	

	m_programID = MyTestShader::CompileShaders("../Project3D/Shaders/vertexWithTexture.txt", "../Project3D/Shaders/fragmentWithTexture.txt");
	//m_programID = MyTestShader::CompileShaders("../Project3D/Shaders/Vertex.txt", "../Project3D/Shaders/DiffuseFragment.txt");
	//m_programID = shader.Gradient();
	//MyTestShader* shader = new MyTestShader();
	//char* vs = "../bootstrap/Shaders/Vertex.txt";
	//char* fs = "../bootstrap/Shaders/Fragment.txt";
	//shader->CompileShaders(vs, fs);

	return true;
}

void Application3D::shutdown()
{
}

void Application3D::update(float deltaTime) {
	camera.Update();
	// query time since application started
	float time = getTime();

	// rotate camera
	m_viewMatrix = glm::lookAt(vec3(glm::sin(time) * 10, 10, glm::cos(time) * 10),
							   vec3(0), vec3(0, 1, 0));

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
						vec3(-10 + i, 0, -10),
						i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
						vec3(-10, 0, -10 + i),
						i == 10 ? white : black);
	}
	

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	// demonstrate a few shapes
	//Gizmos::addAABBFilled(vec3(0), vec3(1), vec4(0, 0.5f, 1, 0.25f));
	//Gizmos::addSphere(vec3(5, 0, 5), 1, 8, 8, vec4(1, 0, 0, 0.5f));
	//Gizmos::addRing(vec3(5, 0, -5), 1, 1.5f, 8, vec4(0, 1, 0, 1));
	//Gizmos::addDisk(vec3(-5, 0, 5), 1, 16, vec4(1, 1, 0, 1));
	//Gizmos::addArc(vec3(-5, 0, -5), 0, 2, 1, 8, vec4(1, 0, 1, 1));

	mat4 t = glm::rotate(time, glm::normalize(vec3(1, 1, 1)));
	t[3] = vec4(-2, 0, 0, 1);
	Gizmos::addCylinderFilled(vec3(0), 0.5f, 1, 5, vec4(0, 1, 1, 1), &t);

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application3D::draw() {

	// wipe the screen to the background colour
	clearScreen();
	// update perspective in case window resized
	m_projectionMatrix = camera.GetProjectionMatrix(getWindowWidth(), getWindowHeight());
	m_viewMatrix = camera.GetViewMatrix();


	static float angle = 0;
	//angle += 0.01f;
	mat4 modelMatrix = glm::rotate(angle, vec3(0, 1, 0));
	//glm::mat4 mvp = m_projectionMatrix * m_viewMatrix * modelMatrix;


	
	//unsigned int modelUniform = glGetUniformLocation(m_programID, "M");
	//glUniformMatrix4fv(modelUniform, 1, GL_FALSE, (float*)&modelMatrix);

	glUseProgram(m_programID);

	//unsigned int projectionViewUniform = glGetUniformLocation(m_programID, "MVP");
	//glUniformMatrix4fv(projectionViewUniform, 1, false, glm::value_ptr(mvp));

	//unsigned int timeUniform = glGetUniformLocation(m_programID, "time");
	//glUniform1f(timeUniform, getTime());

	//unsigned int heightUniform = glGetUniformLocation(m_programID, "heightScale");
	//glUniform1f(heightUniform, heightScale);

	////ambient lighting
	//float ambientLight = 0.3f;
	//unsigned int ambientAmount = glGetUniformLocation(m_programID, "ambientAmount");
	//glUniform1f(ambientAmount, ambientLight);

	//unsigned int cameraPosition = glGetUniformLocation(m_programID, "cameraPos");
	//glUniform4f(cameraPosition, camera.getPos().x, camera.getPos().y, camera.getPos().z, 0);

	//glBindVertexArray(m_VAO);
	//unsigned int indexCount = (rows - 1) * (cols - 1) * 6;

	//mat4 model = glm::translate(vec3(0));

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, m_texture);
	//unsigned int loc = glGetUniformLocation(m_programID, "diffuse");
	//glUniform1i(loc, 0);

	sphere.Draw(modelMatrix, m_projectionMatrix * m_viewMatrix, m_programID);

	//glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	/*for (auto& gl : m_glInfo)
	{
		glBindVertexArray(gl.m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, gl.m_faceCount * 3);
	}*/
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	Gizmos::draw(m_projectionMatrix * m_viewMatrix * modelMatrix);

	

}