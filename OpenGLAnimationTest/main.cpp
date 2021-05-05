#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "GlobalResources.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Model.h"
#include "GameObject.h"

#include "stb_image.h"

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

using namespace std;

void processInput(GLFWwindow* window);

GameObject* human;

glm::vec3 modelRotate(0.0f);
unsigned int animIndex = 0;

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

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "GLAD could not be initialized" << endl;
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	stbi_set_flip_vertically_on_load(true);

	Shader shader("Shaders/model.vert", "Shaders/model.frag");
//	monster = new Model(glm::vec3(0.0f), glm::vec3(90.0f, 0.0f, 90.0f), glm::vec3(0.5f));
	human = new GameObject("Models/Human/human.fbx", glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.03f));
	
//	human.AddAnimation("walk", "Models/Human/walk2.fbx", true);
	human->AddAnimation("run", "Models/Human/human.fbx", true);
	human->SetCurrentAnimation("idle");
	
	human->StartAnimator();


	shader.Use();

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 1.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		
	shader.SetMat4("projection", proj);
	shader.SetMat4("view", view);
	
	while (!glfwWindowShouldClose(window))
	{
		GlobalResources::updateDeltaTime();

		processInput(window);
		
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::vec3 rot = glm::vec3(0.0f, 70.0f, 0.0f) * GlobalResources::deltaTime;
		modelRotate += rot;

		human->Rotate(rot);

		if (modelRotate.y > 360.0f)
		{
			modelRotate = glm::vec3(0.0f, fmod(modelRotate.y, 360.0f), 0.0f);
			animIndex++;
			if (animIndex == 4)
				animIndex = 1;

			switch (animIndex)
			{
			case 1: human->SetCurrentAnimation("idle");
				break;
			case 2: human->SetCurrentAnimation("walk");
				break;
			case 3: human->SetCurrentAnimation("run");
				break;
			default: break;
			}
		}

		cout << modelRotate.y << endl;

		human->Update(GlobalResources::deltaTime);
		
		human->Render(&shader);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
		human->SetCurrentAnimation("idle");
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		human->SetCurrentAnimation("walk");
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		human->SetCurrentAnimation("run");
}