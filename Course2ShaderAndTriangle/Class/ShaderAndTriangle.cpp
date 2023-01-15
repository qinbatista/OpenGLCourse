
#include "ShaderAndTriangle.h"
#include "../InternalLibs/Camera.h"
#include "../InternalLibs/DirectionLight.h"
#include "../InternalLibs/Material.h"
#include "../InternalLibs/Mesh.h"
#include "../InternalLibs/Shader.h"
#include "../InternalLibs/Texture.h"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/mat4x4.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
Texture brickTexture;
Texture dirtyTexture;

Material shinyMaterial;
Material dullMaterial;

GLuint uniformModel, uniformProjection, uniformView, uniformAmbientIntensity, uniformAmbientColor, uniformDiffuseIntensity, uniformDirection,
	uniformSpecularIntensity, uniformShininess, uniformEyePosition;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;
const float toRadians = 3.14159265f / 180.0f;
std::vector<Mesh *> meshList;
std::vector<Shader> shaderList;
float curAngle = 0.0f;
float sizeDirection = true;
float curSize = 0.4f;
float maxSize = 0.8f;
float minSize = 0.1f;
DirectionLight mainLight;
// Fragment Shader
static const char *fShader = "Shaders/shader.frag";
// Vertex Shader
static const char *vShader = "Shaders/shader.vert";
void calcAverageNormals(unsigned int *indices, unsigned int indiceCount, GLfloat *vertices, unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;

		glm::vec3 v1(vertices[in1] - vertices[in0],
					 vertices[in1 + 1] - vertices[in0 + 1],
					 vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0],
					 vertices[in2 + 1] - vertices[in0 + 1],
					 vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset;
		in1 += normalOffset;
		in2 += normalOffset;

		vertices[in0] += normal.x;
		vertices[in0 + 1] += normal.y;
		vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x;
		vertices[in1 + 1] += normal.y;
		vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x;
		vertices[in2 + 1] += normal.y;
		vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x;
		vertices[nOffset + 1] = vec.y;
		vertices[nOffset + 2] = vec.z;
	}
}
void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	uniformModel = shaderList[0].GetModelLocation();
	uniformProjection = shaderList[0].GetProjectionLocation();
}
void CreateObjects()
{
	brickTexture = Texture((char *)"Textures/brick.png");
	brickTexture.LoadTexture();
	dirtyTexture = Texture((char *)"Textures/dirt.png");
	dirtyTexture.LoadTexture();

	shinyMaterial = Material(1.0f, 32);
	dullMaterial = Material(0.3f, 4);

	mainLight = DirectionLight(1.0f, 1.0f, 1.0f,
							   0.1f, 0.3f,
							   0.0f, 0.0f, -1.0f);

	brickTexture.UseTexture();
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2};
	GLfloat vertices[] = {
		// x, y, z              u, v 		 nx, ny, nz
		-1.0f, -1.0f, -0.6f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f};
	calcAverageNormals(indices, 12, vertices, 32, 8, 5);
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);
}
void DrawTriangle(glm::mat4 DisplayProjection, Camera *camera)
{
	if (direction)
		triOffset += triIncrement;
	else
		triOffset -= triIncrement;

	if (abs(triOffset) >= triMaxOffset)
		direction = !direction;
	curAngle += 1.0f;
	if (curAngle > 360)
	{
		curAngle -= 360;
	}
	if (sizeDirection)
		curSize += 0.01f;
	else
		curSize -= 0.01f;

	if (curSize >= maxSize || curSize <= minSize)
		sizeDirection = !sizeDirection;

	shaderList[0].UseShader();
	uniformModel = shaderList[0].GetModelLocation();
	uniformProjection = shaderList[0].GetProjectionLocation();
	uniformView = shaderList[0].GetViewLocation();
	uniformAmbientColor = shaderList[0].GetAmbientColorLocation();
	uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();
	uniformDirection = shaderList[0].GetDirectionLocation();
	uniformDiffuseIntensity = shaderList[0].GetDiffuseIntensityLocation();
	uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
	uniformShininess = shaderList[0].GetShininessLocation();
	uniformEyePosition = shaderList[0].GetEyePositionLocation();

	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(DisplayProjection));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera->calculateViewMatrix()));
	glUniform3f(uniformEyePosition, camera->getCameraPosition().x, camera->getCameraPosition().y, camera->getCameraPosition().z);

	mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColor, uniformDiffuseIntensity, uniformDirection);
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(triOffset, 0.0f, -3.0f));
	model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	brickTexture.UseTexture();
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	meshList[0]->RenderMesh();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-triOffset, 0.0f, -3.0f));
	model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(curSize, curSize, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	dirtyTexture.UseTexture();
	dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	meshList[1]->RenderMesh();

	glUseProgram(0);
}