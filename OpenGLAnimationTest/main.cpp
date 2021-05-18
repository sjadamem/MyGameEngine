#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/gtc/quaternion.hpp>
#include <iostream>
#include <string>

#include "GlobalResources.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"
#include "Cube.h"

#include "StaticMesh.h"

#include "stb_image.h"

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

using namespace std;

void processInput(GLFWwindow* window);
void mouse_position_callback(GLFWwindow* window, double x, double y);

bool mouse = true;
float lastX, lastY = 0.0f;

GameObject* human;
Camera* camera;

glm::vec3 mEulerAngles(0.0f, 0.0f, 0.0f);
unsigned int animIndex = 0;

void processInput(GLFWwindow* window);
void mouse_position_callback(GLFWwindow* window, double x, double y);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Animation Code Test", NULL, NULL);

	if (window == NULL)
	{
		cout << "Failed to create GLFWwindow" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, mouse_position_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "GLAD could not be initialized" << endl;
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	stbi_set_flip_vertically_on_load(true);

	Mesh* mesh = new StaticMesh(Cube());

	camera = new Camera(glm::vec3(0.0f, 1.0f, 10.0f));

	Shader animateShader("Shaders/model.vert", "Shaders/model.frag");
	Shader meshShader	("Shaders/basic.vert", "Shaders/basic.frag");

//	Shader 
	human = 
		new GameObject(
			"Models/Human/human.fbx", 
			glm::vec3(0.0f, -1.0f, 0.0f), 
			glm::vec3(0.0f), 
			glm::vec3(0.005f)
	);
	human->AddAnimation("run", "Models/Human/human.fbx", true);
	human->SetCurrentAnimation("idle");
	
	human->StartAnimator();


//	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	
	while (!glfwWindowShouldClose(window))
	{
		GlobalResources::updateDeltaTime();
		
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera->GetViewMatrix();
		
		processInput(window);
		
		animateShader.Use();
		animateShader.SetMat4("projection", proj);
		animateShader.SetMat4("view", view);
		
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
//		glm::vec3 rot = glm::vec3(70.0f, 0.0f, 0.0f) * GlobalResources::deltaTime;

//		human->Rotate(rot);

		human->Update(GlobalResources::deltaTime);
		human->Render(&animateShader);

		meshShader.Use();
		meshShader.SetMat4("projection", proj);
		meshShader.SetMat4("view", view);
		meshShader.SetMat4("model", glm::mat4(1.0f));
		mesh->Render(&meshShader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
		human->SetCurrentAnimation("idle");
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		human->SetCurrentAnimation("walk");
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		human->SetCurrentAnimation("run");

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->Move(FORWARD, GlobalResources::deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->Move(BACKWARD, GlobalResources::deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->Move(RIGHT,	GlobalResources::deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->Move(LEFT, GlobalResources::deltaTime);
}

void mouse_position_callback(GLFWwindow* window, double x, double y)
{
	if (mouse)
	{
		lastX = (float)x;
		lastY = (float)y;
		mouse = false;
	}

	float xOffset = (float)x - lastX;
	float yOffset = lastY - (float)y;		//y - lastY does reverse yOffset. Friends don't let friends play with reverse camera controls!

	lastX = (float)x;
	lastY = (float)y;

	camera->Turn(xOffset, yOffset, GlobalResources::deltaTime);
}