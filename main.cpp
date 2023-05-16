#include <stdio.h>
#include <stdlib.h>
#include "projectile.h"
#include "ship.h"
#include "asteroid.h"
#include <iostream>
#include <string>

#include "dependente\glfw\glfw3.h"
#include "dependente/glm/gtc/type_ptr.hpp"

#include "shader.hpp"

#include <vector>
#include <tuple>
//variables
GLFWwindow* window;
const int width = 900, height = 900;

//mouse position
double xpos0;
double ypos0;

#include "object_manager.h"

struct wave
{
	static constexpr glm::vec3 beginColor=glm::vec3(0.0f, 0.0f, 0.2f);
	static constexpr glm::vec3 endColor=glm::vec3(0.3f,0.05f,0.05f);
	static const int transitionWaves=10;
	glm::vec3 color;
	int asterCount=1;
	int number=0;
	wave& next()
	{
		this->color=wave::beginColor+( wave::endColor-wave::beginColor) * ( this->number/ (float)wave::transitionWaves);
		this->number++;
		this->asterCount++;
		return *this;
	}
};

#include "object_manager.h"
projectile_manager projectiles;
asteroid_manager asteroids;

wave wav;

void spawnWave()
{

	wav.next();
	for(int a=0;a<wav.asterCount;a++)
	{
		float randomAngle=(rand()%314)/50.0f;
		float randomDist=(rand()%5+10)/5.0f;
		float randomAV=(rand()%100-50)/50.0f;
		float randomSize=(rand()%10+5)/100.0f;
		auto newAsteroid = asteroid(glm::vec3(glm::cos(randomAngle)*randomDist, glm::sin(randomAngle)*randomDist, 0), randomSize);
		newAsteroid.init();
		newAsteroid.angular_velocity = randomAV;
		asteroids.push(newAsteroid);
	}


}

ship sh(glm::vec3(0.0f, -1.0f, 0)); //not bug, is featur
bounding_box frame = bounding_box(glm::vec3(0.0f, 0.0f, 0),0.9f,0.9f);

//Handling cursor position
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	//std::cout << "The mouse cursor is: " << xpos << " " << ypos << std::endl;
	xpos0 = xpos;
	ypos0 = ypos;
}

int button1;
int action1;
int mods1;

//Ex 3: Add callback for mouse button
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	//std::cout << "The mouse button is: " << button << " " << action << " " << mods << std::endl;
	button1 = button;
	action1 = action;
	mods1 = mods;
}

int key2;
int scancode2;
int action2;
int mods2;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	key2 = key;
	scancode2 = scancode;
	action2 = action;
	mods2 = mods;
}

void window_callback(GLFWwindow* window, int new_width, int new_height)
{
	//what should we do here?
	glViewport(0, 0, new_width, new_height);
}

int main(void)
{

	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	// Open a window and create its OpenGL context
	window = glfwCreateWindow(width, height, "Lab Project", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwTerminate();
		return -1;
	}

	//specify the size of the rendering window
	glViewport(0, 0, width, height);

	// Dark blue background
	glClearColor(wave::beginColor.r, wave::beginColor.g, wave::beginColor.b, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Create and compile our GLSL program from the shaders
	rendered_object::shader_ref = LoadShaders("vertex.glsl", "fragment.glsl");

	sh.init();
  
	// Set a callback for handling mouse cursor position
	// Decomment for a callback example
	glfwSetCursorPosCallback(window, cursor_position_callback);
	// the function prints in terminal the position of the mouse
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, key_callback);
	//Ex4 - Set callback for window resizing
	glfwSetFramebufferSizeCallback(window, window_callback);
	// Check if the window was closed

	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window))
	{
		//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true); // sau break();

		// Swap buffers
		glfwSwapBuffers(window);

		// Check for events
		glfwPollEvents();

		// Screen Color change for every wave
		if(wav.number>0)
			glClearColor(wav.color.r, wav.color.g, wav.color.b, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		bool alive = sh.health>0;

		// ship's movement
		if(alive)
		{
			if (glfwGetKey(window, GLFW_KEY_W)) {
				sh.addVel(glm::vec3(0.0f, 0.1f, 0));
			}
			if (glfwGetKey(window, GLFW_KEY_S)) {
				sh.addVel(glm::vec3(0.0f, -0.1f, 0));
			}
			if (glfwGetKey(window, GLFW_KEY_D)) {
				sh.addVel(glm::vec3(0.1f, 0.0f, 0));
			}
			if (glfwGetKey(window, GLFW_KEY_A)) {
				sh.addVel(glm::vec3(-0.1f, 0.0f, 0));
			}
					// shoot bullet
			static int lastPress;
			int currentPress;
			if ((currentPress=glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))!=lastPress&&currentPress==GLFW_PRESS) {
				projectiles.push(sh.shoot());
				//std::cout<<"projectiles: "<<projectiles.size()<<std::endl;
				//sh.addAngularVel(-1);
			}
			lastPress=currentPress;

			glm::vec3 mousePos = glm::vec3((2.0f * xpos0 - width) / width, (-2.0f * ypos0 + height) / height, 0);

			sh.pointTo(mousePos);


		}
		else
		{
			static bool runOnce=false;
			if(!runOnce)
			{
				runOnce=true;
				glfwSetWindowTitle(window,"Game over!");
			}
		}
		




		static int waveTimer;
		if((waveTimer++)>100)
		{
			waveTimer=0;
			if(asteroids.size()==0)
			{
				spawnWave();
				if(alive)
				{
					std::string titleString="Wave " + std::to_string(wav.number);
					glfwSetWindowTitle(window, titleString.c_str());
				}
			}
		}
// 		static int lastWavePress;
// 		int currentWavePress;
// 		if ((currentWavePress=glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))!=lastWavePress&&currentWavePress==GLFW_PRESS) {
// 			spawnWave();
// 			//sh.addAngularVel(1);
// 		}
		/*
		if (glfwGetKey(window, GLFW_KEY_M)) {
			trans = glm::mat4(1);
			trans = glm::translate(trans, glm::vec3((xpos0 - (width / 2)) / (width / 2), (- ypos0 + (height / 2)) / (height / 2), 0));
		}
		*/
		
		// doesnt let the ship exit the window frame
		auto col = frame.getCollision(sh);
        //std::cout<<"oof"<<col.norm.x <<" "<<col.norm.y<<" "<<col.dist<<std::endl;
		if(col.collided())
		{
			//std::cout<<"oof"<<col.norm.x <<" "<<col.norm.y<<" "<<col.dist<<std::endl;
			sh.addVel(col.norm*col.dist*10.0f);
		}

		sh.deltaT(0.01);
		
		projectiles.forEach([](int projIndex,projectile& proj)
		{
			proj.deltaT(0.01);
			proj.render();

			//TODO check for collisions with asteroids

			asteroids.forEach([&](int asterIndex, asteroid& aster)
			{
				auto asteroidCollision = proj.getCollision(aster);
				if(asteroidCollision.collided())
				{
	// 				aster.vel=glm::vec3(0,0,0);
	// 				aster.angular_velocity+=2;
					projectiles.erase(projIndex);
					std::cout<<"Asteroid hit! ";
					if(--aster.health<=0)
					{
						asteroids.erase(asterIndex);
						std::cout<<"Total damage!"<<std::endl;
					}
					else
					{
						std::cout<<aster.health<<" health left"<<std::endl;
					}
				}

			});

			auto projCollision = frame.getCollision(proj);
			if(projCollision.collided())
			{
				projectiles.erase(projIndex);
			}
		});
		
		asteroids.forEach([](int index, asteroid& aster)
		{
			aster.deltaT(0.01);
			aster.render();
			auto asterCollision = frame.getCollision(aster);
			if( asterCollision.collided())
			{
				//asteroids.erase(iter);
				//aster.addVel(col.norm*col.dist);
				aster.vel=glm::normalize(-2.0f*asterCollision.norm+aster.vel)*glm::length(aster.vel);
			}

			asterCollision = sh.getCollision(aster);
			if(asterCollision.collided())
			{
					if((sh.health--)>0)
					{
						std::cout << "Ship Health: " << sh.health << std::endl;
						asteroids.erase(index);
					}
					else
					{
						sh.addVel(-asterCollision.norm*asterCollision.dist);
					}
			}

			aster.addVel(glm::normalize(sh.getPos()-aster.getPos())*0.005f);
			asteroids.forEach([&](int asterIndex, asteroid& aster2)
			{
				if(&aster2==&aster)
				{
					return;
				}
				auto a2aCollision = aster.getCollision(aster2);
				if(a2aCollision.collided())
				{
					std::cout<<"bounce"<<std::endl;
					aster.addVel(-a2aCollision.norm*a2aCollision.dist);
					//aster.vel=glm::normalize(-2.0f*asterCollision.norm+aster.vel)*glm::length(aster.vel);
					//aster2.vel=glm::normalize(2.0f*asterCollision.norm+aster2.vel)*glm::length(aster2.vel);
				}

			});

		});
    
		sh.render();

	}

	// Cleanup
	//glDeleteBuffers(1, &vbo);
	//glDeleteBuffers(1, &ibo);
	//glDeleteVertexArrays(1, &vao);
	//glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
