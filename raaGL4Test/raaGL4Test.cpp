// raaGL4Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>


//#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <iostream>

#include <raaGL4RenderTools/raaShaderStack.h>
#include <raaGL4RenderTools/raaShaderProgramme.h>
#include <raaGL4RenderTools/raaAttributeListener.h>
#include <raaGL4RenderTools/raaMatrix4T.h>
#include <raaGL4RenderTools/raaVector4T.h>

float g_afPoints[] = { 0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f };

const char* vertex_shader =
"#version 400\n"
"in vec3 vp;"
"uniform mat4 transform;"
"void main() {"
"  gl_Position = transform * vec4(vp, 1.0);"
"}";

const char* fragment_shader =
"#version 400\n"
"out vec4 frag_colour;"
"void main() {"
"  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
"}";

//raaTransformStack g_TransformStack;

raaGL4::raaMatrix4fv g_Modelview;
raaGL4::raaMatrix4fv g_Projection;

raaGL4::raaShaderStack g_ShaderStack;

void resize(GLFWwindow *pWindow, int iWidth, int iHeight)
{
	glViewport(0, 0, iWidth, iHeight);
//	g_TransformStack.currentProjectionMatrix().setPerspectiveProjection(30.0f, ((float)iWidth)/((float)iHeight), 0.1f, 100.0f);
	g_Projection.perspective(30.0f, ((float)iWidth) / ((float)iHeight), 0.1f, 100.0f);
}

int main()
{


//	raaUtilities::setGL4(true);
	if(!glfwInit()) std::cout << "Error -> could not start GLFW3" << std::endl;

	GLFWwindow *pWindow = glfwCreateWindow(640, 480, "OGL4", 0, 0);

	if(!pWindow)
	{
		std::cout << "Error -> coudl not open window in GLFW3" << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(pWindow);



	glfwSetWindowSizeCallback(pWindow, resize);

	glewExperimental = GL_TRUE;
	glewInit();

	const GLubyte *pRenderer = glGetString(GL_RENDERER);
	const GLubyte *pVersion = glGetString(GL_VERSION);

	std::cout << "Renderer -> " << pRenderer << " :: Version -> " << pVersion << std::endl;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), g_afPoints, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	raaGL4::raaShaderProgramme*  pProgramme=g_ShaderStack.addProgramFromShaderGroup("simpleShader");
	
	raaGL4::raaMatrix4fv m;
	pProgramme->listeners()["transform"].setAttribute(&m);
/*
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);
*/




//	GLint transformLoc = glGetUniformLocation(shader_programme, "transform");

	glViewport(0, 0, 640, 480);

	raaGL4::raaVector4fv vTrans(0.0f, 0.0f, -10.0f, 0.0f);
	raaGL4::raaVector4fv vAxis(0.0f, 0.0f, 1.0f, 0.0f);

//	g_TransformStack.currentProjectionMatrix().setOrthoProjection(2.0f, -2.0f, -2.0f, 2.0f, 0.1f, 100.0f);

//	g_TransformStack.currentProjectionMatrix().setPerspectiveProjection(30.0f, 640.0f / 480.0f, 0.1f, 100.0f); 
//	g_TransformStack.currentModelViewMatrix().translate(vTrans);

	g_Projection.perspective(30.0f, 640.0f / 480.0f, 0.1f, 100.0f);
	g_Modelview.translate(vTrans);

	g_ShaderStack.useProgramme(pProgramme);

	float fAng = 0.0f;
	while (!glfwWindowShouldClose(pWindow)) 
	{
//		g_TransformStack.currentModelView().push();
//		g_TransformStack.currentModelViewMatrix().rotate(vAxis, fAng += 0.0001f);
	///	g_TransformStack.resolve();
		g_Modelview.push();
		g_Modelview.rotate(fAng += 0.0001f, vAxis);
		m = g_Modelview*g_Projection;

		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glUseProgram(shader_programme);



		glBindVertexArray(vao);
		// draw points 0-3 from the currently bound VAO with current in-use shader
//		glProgramUniformMatrix4fv(shader_programme, transformLoc, 1, true, g_TransformStack.get().get());
//		glProgramUniformMatrix4fv(shader_programme, transformLoc, 1, true, m.ptr());
		g_ShaderStack.updateCurrentProgrammeAttributes();

		glDrawArrays(GL_TRIANGLES, 0, 3);
		// update other events like input handling 
//		g_TransformStack.currentModelView().pop();
		g_Modelview.pop();
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(pWindow);
	}

	glfwTerminate();

    return 0;
}

