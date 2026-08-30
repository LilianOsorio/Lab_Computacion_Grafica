//practica #2
//De la Peña Osorio Lilian
//Fecha de entrega 28 de agosto 2026
//Numero de cuenta 423069439
//Imagen de referencia: Bob Esponja Pixel Art (https://es.pinterest.com/pin/536209899404446585/)

#include <iostream>

// Incluir GLEW antes de GLFW para inicializar los punteros de funciones de OpenGL
#include <GL/glew.h>

// GLFW maneja la creación de la ventana y los eventos de teclado/mouse
#include <GLFW/glfw3.h>

// Dimensiones de la ventana
const GLint WIDTH = 800, HEIGHT = 800;

// Tamaño y origen del Pixel Art
const int GRID_COLS = 22;
const int GRID_ROWS = 28;
const float PIXEL_SIZE = 0.06f;

// Origen (esquina superior izquierda del dibujo)
const float START_X = -0.66f;
const float START_Y = 0.84f;

// Matriz de colores:
// 0: Transparente, 1: Negro, 2: Amarillo, 3: Blanco, 4: Azul, 5: Rojo, 6: Café
const int bobEsponja[28][22] = {

    // Fila 0
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

    // Fila 1
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},

    // Fila 2
    {0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},

    // Fila 3
    {0,0,1,2,2,2,1,2,1,2,2,2,2,2,1,2,1,2,2,2,1,0},

    // Fila 4
    {0,0,1,2,2,2,2,1,1,1,2,2,2,1,1,1,2,2,2,2,1,0},

    // Fila 5
    {0,0,1,2,2,2,1,3,3,3,1,2,1,3,3,3,1,2,2,2,1,0},

    // Fila 6
    {0,0,1,2,2,1,3,3,4,4,3,1,3,4,4,3,3,1,2,2,1,0},

    // Fila 7
    {0,0,1,2,2,1,3,4,1,1,4,1,4,1,1,4,3,1,2,2,1,0},

    // Fila 8
    {0,0,1,2,2,1,3,4,1,1,4,1,4,1,1,4,3,1,2,2,1,0},

    // Fila 9
    {0,0,1,2,2,1,3,3,4,4,1,2,1,4,4,3,3,1,2,2,1,0},

    // Fila 10
    {0,0,1,2,2,2,1,3,3,3,1,2,1,3,3,3,1,2,2,2,1,0},

    // Fila 11
    {0,0,0,1,2,2,2,1,1,1,2,2,2,1,1,1,2,2,2,1,0,0},

    // Fila 12
    {0,0,0,1,2,2,1,2,2,2,2,2,2,2,2,2,1,2,2,1,0,0},

    // Fila 13
    {0,0,0,1,2,2,2,1,1,1,1,1,1,1,1,1,2,2,2,1,0,0},

    // Fila 14
    {0,0,0,1,2,2,2,2,1,3,3,1,3,3,1,2,2,2,2,1,0,0},

    // Fila 15
    {0,0,1,1,2,2,2,2,1,3,3,1,3,3,1,2,2,2,2,1,1,0},

    // Fila 16
    {0,1,3,3,1,2,2,2,2,1,1,1,1,1,2,2,2,2,1,3,3,1},

    // Fila 17
    {0,1,3,3,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,3,3,1},

    // Fila 18 - Boca
    {0,0,1,3,1,3,3,3,3,3,3,5,3,3,3,3,3,3,1,3,1,0},

    // Fila 19
    {0,0,1,2,1,1,1,1,1,1,1,5,1,1,1,1,1,1,1,2,1,0},

    // Fila 20 - Pantalón
    {0,1,1,2,1,6,6,6,6,6,6,5,6,6,6,6,6,6,1,2,1,1},

    // Fila 21
    {0,1,2,2,1,6,6,6,6,6,6,6,6,6,6,6,6,6,1,2,2,1},

    // Fila 22
    {0,1,1,1,1,6,6,6,6,1,1,1,1,1,6,6,6,6,1,1,1,1},

    // Fila 23
    {0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0},

    // Fila 24 - Piernas
    {0,0,0,0,0,0,1,3,1,0,0,0,0,0,1,3,1,0,0,0,0,0},

    // Fila 25
    {0,0,0,0,0,0,1,3,1,0,0,0,0,0,1,3,1,0,0,0,0,0},

    // Fila 26 - Zapatos
    {0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0},

    // Fila 27
    {0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0}
};

// Función para establecer el color de OpenGL según el id
void setPixelColor(int colorId) {
    switch (colorId) {
    case 1: glColor3f(0.0f, 0.0f, 0.0f); break; // Negro (Bordes)
    case 2: glColor3f(0.98f, 0.92f, 0.2f); break; // Amarillo (Cuerpo)
    case 3: glColor3f(1.0f, 1.0f, 1.0f); break; // Blanco (Ojos/Camisa/Dientes)
    case 4: glColor3f(0.24f, 0.63f, 0.94f); break; // Azul (Ojos)
    case 5: glColor3f(0.88f, 0.15f, 0.15f); break; // Rojo (Corbata)
    case 6: glColor3f(0.53f, 0.33f, 0.16f); break; // Café (Pantalón)
    }
}

// Primitiva 1: GL_TRIANGLE_FAN para dibujar cada celda/cuadrado del pixel art
void drawPixelArt() {
    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            int colorId = bobEsponja[row][col];
            if (colorId == 0) continue; // Saltar espacio transparente

            float x = START_X + (col * PIXEL_SIZE);
            float y = START_Y - (row * PIXEL_SIZE);

            setPixelColor(colorId);
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f(x, y);
            glVertex2f(x + PIXEL_SIZE, y);
            glVertex2f(x + PIXEL_SIZE, y - PIXEL_SIZE);
            glVertex2f(x, y - PIXEL_SIZE);
            glEnd();
        }
    }
}

// Primitiva 2: GL_LINES para dibujar una línea de soporte/base
void drawBaseLine() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(-0.8f, -0.88f);
    glVertex2f(0.8f, -0.88f);
    glEnd();
}

// Primitiva 3: GL_POINTS para marcar puntos de referencia en las esquinas
void drawReferencePoints() {
    glPointSize(6.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    glVertex2f(-0.8f, -0.88f);
    glVertex2f(0.8f, -0.88f);
    glEnd();
}

int main() {
    if (!glfwInit()) {
        std::cout << "Error al inicializar GLFW" << std::endl;
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica #2 Lilian De la Peña", NULL, NULL);
    if (!window) {
        std::cout << "Error al crear la ventana" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Error al inicializar GLEW" << std::endl;
        return 1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Fondo gris claro
        glClearColor(0.92f, 0.92f, 0.92f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Renderizado del dibujo con 3 primitivas distintas
        drawPixelArt();         // GL_TRIANGLE_FAN
        drawBaseLine();         // GL_LINES
        drawReferencePoints();  // GL_POINTS

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}