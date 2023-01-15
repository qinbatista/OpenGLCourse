#pragma once
#include "DirectionLight.h"
#include "PointLight.h"
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#define MAX_POINT_LIGHTS 3
class Shader
{
public:
	Shader();
	void CreateFromString(const char *vertexCode, const char *fragmentCode);
	void CreateFromFiles(const char *vertexLocation, const char *fragmentLocation);
	std::string ReadFile(const char *fileLocation);
	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColorLocation();
	GLuint GetDiffuseIntensityLocation();
	GLuint GetDirectionLocation();
	GLuint GetSpecularIntensityLocation();
	GLuint GetShininessLocation();
	GLuint GetEyePositionLocation();
	void SetDirectionalLight(DirectionLight *dLight);
	void UseShader();
	void ClearShader();
	~Shader();

private:
	int pointLightCount;
	GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition,
		uniformSpecularIntensity, uniformShininess;
	struct
	{
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		GLuint uniformDirection;
	} uniformDirectionLight;
	GLuint uniformPointLightCount;
	struct
	{
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;
	} uniformPointLight[MAX_POINT_LIGHTS];
	void CompileShader(const char *vertexCode, const char *fragmentCode);
	void AddShader(GLuint theProgram, const char *shaderCode, GLenum shaderType);
};
