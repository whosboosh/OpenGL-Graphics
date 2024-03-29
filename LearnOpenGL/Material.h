#pragma once
#include <glad/glad.h>
#include "Shader.h"

class Material
{
public:
	Material();
	Material(GLfloat sIntensity, GLfloat shine);

	void UseMaterial(Shader* shader);

	~Material();
private:
	GLfloat specularIntensity;
	GLfloat shininess;
};

