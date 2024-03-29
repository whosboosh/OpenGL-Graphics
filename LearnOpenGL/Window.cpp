#include "Window.h"
#include <iostream>
#include <glm/glm.hpp>

Window::Window()
{
	width = 800;
	height = 600;
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
}

int Window::Initialise()
{
	if (!glfwInit())
	{
		printf("Error Initialising GLFW");
		glfwTerminate();
		return 1;
	}

	// Create the window
	mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("Error creating GLFW window!");
		glfwTerminate();
		return 1;
	}

	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowUserPointer(mainWindow, this);
	glfwSetCursorPosCallback(mainWindow, mouse_callback);
	glfwSetKeyCallback(mainWindow, key_callback);
	glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);
}

int Window::switchApi()
{
	// Setup GLFW Windows Properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatiblity
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Enable multisampling buffer for MSAA
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Get buffer size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set the current context
	glfwMakeContextCurrent(mainWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Create Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
}

GLfloat Window::getXChange()
{
	GLfloat change = xChange;
	xChange = 0.0f;
	return change;
}

GLfloat Window::getYChange()
{
	GLfloat change = yChange;
	yChange = 0.0f;
	return change;
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
		}
	}
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	auto app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	int bufferWidth;
	int bufferHeight;
	glfwGetFramebufferSize(app->mainWindow, &bufferWidth, &bufferHeight);

	app->bufferWidth = bufferWidth;
	app->bufferHeight = bufferHeight;
}

void Window::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (theWindow->mouseFirstMoved) 
	{
		theWindow->lastX = xpos;
		theWindow->lastY = ypos;
		theWindow->mouseFirstMoved = false;
	}
	theWindow->xChange = xpos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - ypos;

	theWindow->lastX = xpos;
	theWindow->lastY = ypos;
}

