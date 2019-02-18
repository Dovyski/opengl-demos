/**
 * Basic input features of GLFW, including handling of mouse and keyboard input.
 */

#include <iostream>
#include <GLFW/glfw3.h>

#define WIDTH 500
#define HEIGHT 500

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::cout << "keyCallback -> Key: " << key << " action: ";
	
	if (action == GLFW_PRESS) {
		std::cout << "PRESS";
	} else if (action == GLFW_REPEAT) {
		std::cout << "REPEAT";
	} else if (action == GLFW_RELEASE) {
		std::cout << "RELEASE";
	}

	std::cout << std::endl;
}

void mousePosCallback(GLFWwindow* window, double xpos, double ypos)
{
	std::cout << "mousePosCallback -> cursor is at: (" << xpos << "," << ypos << ")" << std::endl;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	std::cout << "mouseButtonCallback -> ";

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		std::cout << "button: LEFT ";
	} else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
		std::cout << "button: MIDDLE ";
	} else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		std::cout << "button: RIGHT ";
	}

	if (action == GLFW_PRESS) {
		std::cout << "action: PRESS";
	} else if (action == GLFW_RELEASE) {
		std::cout << "action: RELEASE";
	}

	std::cout << std::endl;
}

void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	std::cout << "mouseScrollCallback -> xoffset: " << xoffset << " yoffset: " << yoffset << std::endl;
}

int main()
{
	GLFWwindow* window;
	int width, height;

	if (!glfwInit()) {
		std::cout << "Problem to initialize GLFW" << std::endl;
		exit(1);
	}

	window = glfwCreateWindow(WIDTH, HEIGHT, "Hello world, GLFW!", NULL, NULL);

	if (!window) {
		std::cout << "Problem to create GLFW window" << std::endl;
		glfwTerminate();
		exit(1);
	}

	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mousePosCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetScrollCallback(window, mouseScrollCallback);

	glfwMakeContextCurrent(window);

	while (glfwWindowShouldClose(window) == 0 && glfwGetKey(window, GLFW_KEY_ESCAPE) == 0) {
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glBegin(GL_TRIANGLES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-0.6f, -0.4f, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.6f, -0.4f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.f, 0.6f, 0.f);
		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
