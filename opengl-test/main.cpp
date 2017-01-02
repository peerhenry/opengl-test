#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

// begin shit!

const GLint WIDTH = 640, HEIGHT = 480;

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
	// === START ===
	if (!glfwInit()) {
		printf("GLFW Initialization failed!");
		return EXIT_FAILURE;
	}
	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Test", glfwGetPrimaryMonitor(), NULL);
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Test", nullptr, nullptr);
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	if (!window)
	{
		printf("window or opengl context creation failed.");
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		printf("GLEW Initialization failed!");
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	glfwSetKeyCallback(window, key_callback);
	
	// === RUN ===
	int counter = 0;
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw opengl stuff

		glfwSwapBuffers(window);

		// sleep
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		printf("Running %i\n", counter);
		counter++;
	}

	// === END ===
	glfwDestroyWindow(window);
	glfwTerminate();
	return EXIT_SUCCESS;
}