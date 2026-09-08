//Practica 3
//De la Peña Osorio Lilian
//Fecha de entrega 04 de septiembre 2026
//Numero de cuenta 423069439

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

const GLint WIDTH = 800, HEIGHT = 600;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 3_ Lilian De la Peña", nullptr, nullptr);

    if (nullptr == window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glViewport(0, 0, screenWidth, screenHeight);

    glEnable(GL_DEPTH_TEST);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

    // Vértices del cubo unitario: Posición (X,Y,Z) + Normales de superficie (Nx,Ny,Nz)
    float vertices[] = {
        // Posiciones          // Normales
        // Cara Frontal (Z +)
        -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,

        // Cara Trasera (Z -)
        -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,

        // Cara Izquierda (X -)
        -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,

        // Cara Derecha (X +)
         0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,

         // Cara Inferior (Y -)
         -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,
          0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,
          0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
          0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
         -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
         -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,

         // Cara Superior (Y +)
         -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
          0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
          0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
          0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
         -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
         -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Atributo Posición
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Atributo Normales
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Fondo gris oscuro tipo viewport 3D
        glClearColor(0.22f, 0.22f, 0.22f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.Use();

        // Matriz de vista (Cámara)
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -14.0f));
        view = glm::rotate(view, glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::rotate(view, glm::radians(-35.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");
        GLint colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
        GLint lightLoc = glGetUniformLocation(ourShader.Program, "lightDir");

        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        // Dirección de la luz (proviene desde arriba, frente y derecha)
        glUniform3f(lightLoc, -0.5f, -1.0f, -0.5f);

        glBindVertexArray(VAO);
        glm::mat4 model;

        // --- 1. BASE INFERIOR (Morado Oscuro) ---
        glUniform3f(colorLoc, 0.45f, 0.15f, 0.55f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.3f, -2.2f, 0.0f));
        model = glm::scale(model, glm::vec3(2.2f, 1.4f, 1.8f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- 2. SEGUNDO CUBO (Violeta) ---
        glUniform3f(colorLoc, 0.65f, 0.20f, 0.85f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.9f, 0.0f));
        model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- 3. TERCER CUBO (Azul Rey) ---
        glUniform3f(colorLoc, 0.20f, 0.35f, 0.90f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.5f, 0.2f, 0.0f));
        model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- 4. CUARTO BLOQUE (Azul Celeste) ---
        glUniform3f(colorLoc, 0.20f, 0.70f, 0.95f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.2f, 1.3f, 0.0f));
        model = glm::scale(model, glm::vec3(2.4f, 0.9f, 1.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- 5. QUINTO CUBO (Rosa Pastel) ---
        glUniform3f(colorLoc, 0.95f, 0.40f, 0.70f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.3f, 2.4f, 0.0f));
        model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // --- 6. CUBO SUPERIOR (Rosa Fucsia) ---
        glUniform3f(colorLoc, 1.00f, 0.10f, 0.50f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.3f, 3.6f, 0.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();

    return EXIT_SUCCESS;
}