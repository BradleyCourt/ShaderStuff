#include "Model.h"

#include "Texture.h"

Model::Model()
{
}

Model::~Model()
{
}

bool Model::loadModel(const char * filename, const char* textureFile)
{
	std::string err;

	bool success = tinyobj::LoadObj(&m_attribs, &m_shapes, &m_materials, &err, filename);
	createBufferOBJ();


	

	m_texure = Texture::LoadTexture(textureFile);

	return success;
}


//void Model::createBuffers(std::vector<OpenGLInfo>& glInfo)
//{
//}

void Model::createBufferOBJ()
{
	glInfo.resize(m_shapes.size());
	// grab each shape
	int shapeIndex = 0;
	for (auto& shape : m_shapes)
	{
		// setup OpenGL data
		glGenVertexArrays(1, &glInfo[shapeIndex].m_VAO);
		glGenBuffers(1, &glInfo[shapeIndex].m_VBO);
		glBindVertexArray(glInfo[shapeIndex].m_VAO);
		glInfo[shapeIndex].m_faceCount = shape.mesh.num_face_vertices.size();

		// collect triangle vertices
		std::vector<OBJVertex> vertices;
		int index = 0;
		for (auto face : shape.mesh.num_face_vertices)
		{
			for (int i = 0; i < 3; ++i)
			{
				tinyobj::index_t idx = shape.mesh.indices[index + i];
				OBJVertex v = { 0 };
				// positions
				v.x = m_attribs.vertices[3 * idx.vertex_index + 0];
				v.y = m_attribs.vertices[3 * idx.vertex_index + 1];
				v.z = m_attribs.vertices[3 * idx.vertex_index + 2];
				// normals
				if (m_attribs.normals.size() > 0)
				{
					v.nx = m_attribs.normals[3 * idx.normal_index + 0];
					v.ny = m_attribs.normals[3 * idx.normal_index + 1];
					v.nz = m_attribs.normals[3 * idx.normal_index + 2];
				}
				// texture coordinates
				if (m_attribs.texcoords.size() > 0)
				{
					v.u = m_attribs.texcoords[2 * idx.texcoord_index + 0];
					v.v = m_attribs.texcoords[2 * idx.texcoord_index + 1];
				}
				vertices.push_back(v);
			}
			index += face;
		}
		// bind vertex data
		glBindBuffer(GL_ARRAY_BUFFER, glInfo[shapeIndex].m_VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(OBJVertex), vertices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0); //position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OBJVertex), 0);

		glEnableVertexAttribArray(1); //normal data
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(OBJVertex), (void*)12);

		glEnableVertexAttribArray(2); //texture data
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(OBJVertex), (void*)24);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		shapeIndex++;
	}

}
//void Model::Draw(glm::mat4 transform, glm::mat4 cameraMatrix, unsigned int programID)
//{
//	//get view matrix
//	glm::mat4 mvp = cameraMatrix * transform;
//
//	//pass in model uniform
//	unsigned int modelUniform = glGetUniformLocation(programID, "M");
//	glUniformMatrix4fv(modelUniform, 1, GL_FALSE, (float*)&transform);
//
//	// pass in projection view matrix
//	unsigned int projectionViewUniform = glGetUniformLocation(programID, "MVP");
//	glUniformMatrix4fv(projectionViewUniform, 1, false, glm::value_ptr(mvp));
//
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, m_texture);
//	unsigned int loc = glGetUniformLocation(m_programID, "diffuse");
//	glUniform1i(loc, 0);
//}

void LightingApp::createOpenGLBuffers(FBXFile* fbx)
{ 
	// create the GL VAO/VBO/IBO data for each mesh for (unsigned int i = 0; i < fbx->getMeshCount(); ++i) { FBXMeshNode* mesh = fbx->getMeshByIndex(i);
													  // storage for the opengl data in 3 unsigned int unsigned int* glData = new unsigned int[3];
													  // continued next page…
}

void Model::Draw(glm::mat4 transform, glm::mat4 cameraMatrix, unsigned int programID)
{
	glm::mat4 mvp = cameraMatrix * transform;

	unsigned int projectionViewUniform = glGetUniformLocation(programID, "MVP");
	glUniformMatrix4fv(projectionViewUniform, 1, GL_FALSE, glm::value_ptr(mvp));

	unsigned int modelUniform = glGetUniformLocation(programID, "M");
	glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(transform));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texure);
	unsigned int loc = glGetUniformLocation(programID, "diffuse");
	glUniform1i(loc, 0);

	for (auto& gl : glInfo)
	{
		glBindVertexArray(gl.m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, gl.m_faceCount * 3);
	}
	/*for (unsigned int i = 0; i < glInfo.size(); ++i)
	{
		glBindVertexArray(glInfo[i].m_VAO);
		glDrawElements(GL_TRIANGLES, glInfo[i].m_faceCount, GL_UNSIGNED_INT, 0);
	}*/
}
