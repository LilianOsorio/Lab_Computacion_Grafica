//Practica 04 - Modelado geométrico
//De la Peña Osorio Lilian
//Fecha de entrega 11 de sptiembre 2026
//Numero de cuenta 423069439

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rotX = 0.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad f
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 04_LilianDelaPeña", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers

	

	// use with Perspective Projection
	float verticesBlanco[] = {
		-0.5f, -0.5f, 0.5f, 0.95f, 0.95f,0.95f,//Front
		0.5f, -0.5f, 0.5f,  0.95f, 0.95f,0.95f,
		0.5f,  0.5f, 0.5f,  0.95f, 0.95f,0.95f,
		0.5f,  0.5f, 0.5f,  0.95f, 0.95f,0.95f,
		-0.5f,  0.5f, 0.5f, 0.95f, 0.95f,0.95f,
		-0.5f, -0.5f, 0.5f, 0.95f, 0.95f,0.95f,
		
		-0.5f, -0.5f, -0.5f, 0.95f, 0.95f,0.95f, //Back
		0.5f, -0.5f, -0.5f, 0.95f, 0.95f,0.95f,
		0.5f,  0.5f, -0.5f, 0.95f, 0.95f,0.95f,
		0.5f,  0.5f, -0.5f, 0.95f, 0.95f,0.95f,
		-0.5f,  0.5f, -0.5f, 0.95f, 0.95f,0.95f,
		-0.5f, -0.5f, -0.5f, 0.95f, 0.95f,0.95f,
		
		 0.5f, -0.5f,  0.5f,  0.95f, 0.95f,0.95f,//Right
		 0.5f, -0.5f, -0.5f,  0.95f, 0.95f,0.95f,
		 0.5f,  0.5f, -0.5f,  0.95f, 0.95f,0.95f,
		 0.5f,  0.5f, -0.5f,  0.95f, 0.95f,0.95f,
		 0.5f,  0.5f,  0.5f,  0.95f, 0.95f,0.95f,
		 0.5f,  -0.5f, 0.5f, 0.95f, 0.95f,0.95f,
      
		-0.5f,  0.5f,  0.5f,  0.95f, 0.95f,0.95f,//left
		-0.5f,  0.5f, -0.5f,  0.95f, 0.95f,0.95f,
		-0.5f, -0.5f, -0.5f,  0.95f, 0.95f,0.95f,
		-0.5f, -0.5f, -0.5f,  0.95f, 0.95f,0.95f,
		-0.5f, -0.5f,  0.5f,  0.95f, 0.95f,0.95f,
		-0.5f,  0.5f,  0.5f,  0.95f, 0.95f,0.95f,
		
		-0.5f, -0.5f, -0.5f, 0.95f, 0.95f,0.95f,//bottom
		0.5f, -0.5f, -0.5f,  0.95f, 0.95f,0.95f,
		0.5f, -0.5f,  0.5f,  0.95f, 0.95f,0.95f,
		0.5f, -0.5f,  0.5f,  0.95f, 0.95f,0.95f,
		-0.5f, -0.5f,  0.5f, 0.95f, 0.95f,0.95f,
		-0.5f, -0.5f, -0.5f, 0.95f, 0.95f,0.95f,
		
		-0.5f,  0.5f, -0.5f, 0.95f, 0.95f,0.95f,//top
		0.5f,  0.5f, -0.5f, 0.95f, 0.95f,0.95f,
		0.5f,  0.5f,  0.5f,  0.95f, 0.95f,0.95f,
		0.5f,  0.5f,  0.5f,  0.95f, 0.95f,0.95f,
		-0.5f,  0.5f,  0.5f, 0.95f, 0.95f,0.95f,
		-0.5f,  0.5f, -0.5f, 0.95f, 0.95f,0.95f,
	};

	float verticesRosa[] = {
		-0.5f, -0.5f, 0.5f,  0.98f, 0.68f, 0.68f,
		 0.5f, -0.5f, 0.5f,  0.98f, 0.68f, 0.68f,
		 0.5f,  0.5f, 0.5f,  0.98f, 0.68f, 0.68f,
		 0.5f,  0.5f, 0.5f,  0.98f, 0.68f, 0.68f,
		-0.5f,  0.5f, 0.5f,  0.98f, 0.68f, 0.68f,
		-0.5f, -0.5f, 0.5f,  0.98f, 0.68f, 0.68f,

		-0.5f, -0.5f, -0.5f, 0.98f, 0.68f, 0.68f,
		 0.5f, -0.5f, -0.5f, 0.98f, 0.68f, 0.68f,
		 0.5f,  0.5f, -0.5f, 0.98f, 0.68f, 0.68f,
		 0.5f,  0.5f, -0.5f, 0.98f, 0.68f, 0.68f,
		-0.5f,  0.5f, -0.5f, 0.98f, 0.68f, 0.68f,
		-0.5f, -0.5f, -0.5f, 0.98f, 0.68f, 0.68f,

		0.5f, -0.5f,  0.5f, 0.98f, 0.68f, 0.68f,
		 0.5f, -0.5f, -0.5f, 0.98f, 0.68f, 0.68f,
		 0.5f,  0.5f, -0.5f, 0.98f, 0.68f, 0.68f,
		 0.5f,  0.5f, -0.5f, 0.98f, 0.68f, 0.68f,
		 0.5f,  0.5f,  0.5f, 0.98f, 0.68f, 0.68f,
		 0.5f, -0.5f,  0.5f, 0.98f, 0.68f, 0.68f,

		 -0.5f,  0.5f,  0.5f, 0.98f, 0.68f, 0.68f,
		 -0.5f,  0.5f, -0.5f, 0.98f, 0.68f, 0.68f,
		 -0.5f, -0.5f, -0.5f, 0.98f, 0.68f, 0.68f,
		 -0.5f, -0.5f, -0.5f, 0.98f, 0.68f, 0.68f,
		 -0.5f, -0.5f,  0.5f, 0.98f, 0.68f, 0.68f,
		 -0.5f,  0.5f,  0.5f, 0.98f, 0.68f, 0.68f,

		 -0.5f, -0.5f, -0.5f, 0.98f, 0.68f, 0.68f,
		  0.5f, -0.5f, -0.5f, 0.98f, 0.68f, 0.68f,
		  0.5f, -0.5f,  0.5f, 0.98f, 0.68f, 0.68f,
		  0.5f, -0.5f,  0.5f, 0.98f, 0.68f, 0.68f,
		 -0.5f, -0.5f,  0.5f, 0.98f, 0.68f, 0.68f,
		 -0.5f, -0.5f, -0.5f, 0.98f, 0.68f, 0.68f,

		 -0.5f,  0.5f, -0.5f, 0.98f, 0.68f, 0.68f,
		  0.5f,  0.5f, -0.5f, 0.98f, 0.68f, 0.68f,
		  0.5f,  0.5f,  0.5f, 0.98f, 0.68f, 0.68f,
		  0.5f,  0.5f,  0.5f, 0.98f, 0.68f, 0.68f,
		 -0.5f,  0.5f,  0.5f, 0.98f, 0.68f, 0.68f,
		 -0.5f,  0.5f, -0.5f, 0.98f, 0.68f, 0.68f,
		};

	float verticesNegro[] = {
		-0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, 0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, 0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,

		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	};

	float verticesAmarillo[] = {
		-0.5f, -0.5f, 0.5f,  1.0f, 0.75f, 0.0f,
		 0.5f, -0.5f, 0.5f,  1.0f, 0.75f, 0.0f,
		 0.5f,  0.5f, 0.5f,  1.0f, 0.75f, 0.0f,
		 0.5f,  0.5f, 0.5f,  1.0f, 0.75f, 0.0f,
		-0.5f,  0.5f, 0.5f,  1.0f, 0.75f, 0.0f,
		-0.5f, -0.5f, 0.5f,  1.0f, 0.75f, 0.0f,

		-0.5f, -0.5f, -0.5f, 1.0f, 0.75f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.75f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 0.75f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 0.75f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.75f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.75f, 0.0f,
		
		0.5f, -0.5f,  0.5f, 1.0f, 0.75f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.75f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 0.75f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 0.75f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.75f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.75f, 0.0f,
		
		 -0.5f,  0.5f,  0.5f, 1.0f, 0.75f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.75f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.75f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.75f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 0.75f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.75f, 0.0f,
		-
		0.5f, -0.5f, -0.5f, 1.0f, 0.75f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.75f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.75f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.75f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 0.75f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.75f, 0.0f,
		
		-0.5f,  0.5f, -0.5f, 1.0f, 0.75f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 0.75f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.75f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.75f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.75f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.75f, 0.0f,
	};

	GLuint VAO[4], VBO[4];
	glGenVertexArrays(4, VAO);
	glGenBuffers(4, VBO);

	// BLANCO (Cuerpo)
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBlanco), verticesBlanco, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// ROSA (Boca)
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesRosa), verticesRosa, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// NEGRO (Ojos)
	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesNegro), verticesNegro, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// AMARILLO (Cuernos)
	glBindVertexArray(VAO[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesAmarillo), verticesAmarillo, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.6f, 0.8f, 0.95f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
	

		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f)); 
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	
		
		glBindVertexArray(VAO[0]);
		//Cabeza
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.4f, 0.8f));
		model = glm::scale(model, glm::vec3(1.8f, 1.4f, 1.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cuerpo
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, -0.8f));
		model = glm::scale(model, glm::vec3(1.6f, 1.6f, 2.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//PATAS
		//Delanteras
		//Izq
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.6f, -1.2f, 0.1f));
		model = glm::scale(model, glm::vec3(0.35f, 0.6f, 0.35f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Der
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.6f, -1.2f, 0.1f));
		model = glm::scale(model, glm::vec3(0.35f, 0.6f, 0.35f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Traseras
		//Izq
		model = glm::mat4(1.0f);	
		model = glm::translate(model, glm::vec3(-0.6f, -1.2f, -1.7f));
		model = glm::scale(model, glm::vec3(0.35f, 0.6f, 0.35f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Der
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.6f, -1.2f, -1.7f));
		model = glm::scale(model, glm::vec3(0.35f, 0.6f, 0.35f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Cola
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, -2.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.8f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Boca
		glBindVertexArray(VAO[1]);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.3f, 1.4f));
		model = glm::scale(model, glm::vec3(1.8f, 0.7f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Colita
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, -2.25f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// OJOS
		glBindVertexArray(VAO[2]);

		// Ojo Izquierdo
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.45f, 0.65f, 1.61f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.05f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Ojo Derecho
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.45f, 0.65f, 1.61f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.05f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Manchas
		//Cabeza
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.2f, 1.11f, 0.4f));
		model = glm::scale(model, glm::vec3(0.8f, 0.02f, 0.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Cuerpo
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.81f, -0.1f, -0.8f));
		model = glm::scale(model, glm::vec3(0.02f, 0.8f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Punta colita
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, -2.45f));
		model = glm::scale(model, glm::vec3(0.22f, 0.22f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(VAO[3]);

		// Cuerno Izquierdo
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.65f, 1.25f, 0.7f));
		model = glm::scale(model, glm::vec3(0.3f, 0.35f, 0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cuerno Derecho
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.65f, 1.25f, 0.7f));
		model = glm::scale(model, glm::vec3(0.3f, 0.35f, 0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);
				
		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	//Limpia el  buffer de memoria
	glDeleteVertexArrays(4, VAO);
	glDeleteBuffers(4,VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }


 // Nos permite movernos en el espacio 3D con las teclas A,D,W,S,PageUp,PageDown y rotar con las flechas izquierda y derecha
 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		 movY += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		 movY -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.4f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.4f;
	 if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		 rotX += 0.4f;
	 if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		 rotX -= 0.4f;
 }


