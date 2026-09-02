#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdio>
#include <cstdlib>
#include "Model.h"



static void error_callback(int error, const char* description){
    fprintf(stderr, "GLFW error %d: %s\n", error, description);
}


float speed = 45.0f;
float x = 0.0f;
float y = 0.0f;
float z = 1.0f;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        speed = -speed;
    }

    if (key == GLFW_KEY_X && action == GLFW_PRESS) {
        x = 1.0f;
        y = 0.0f;
        z = 0.0f;
    }
    if (key == GLFW_KEY_Y && action == GLFW_PRESS) {
        x = 0.0f;
        y = 1.0f;
        z = 0.0f;
    }
    if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
        x = 0.0f;
        y = 0.0f;
        z = 1.0f;
    }
}

static void window_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 vc;"
"out vec3 barva;"
"void main () {"
"barva = vc;"
"     gl_Position = vec4 (vp, 1.0);"
"}";

const char* fragment_shader =
"#version 330\n"
"out vec4 frag_colour;"
"in vec3 barva;"
"void main () {"
"     frag_colour = vec4 (barva, 1.0);"
"}";

float pointsCtverec[] = {
     0.9f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.9f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.1f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.1f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,

};

float pointsTrojuhelnik[] = {
     -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     -0.8f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.2f, -0.8f, 0.0f, 0.0f, 0.0f, 1.0f

};


static bool zkontrolujShader(GLuint shader, const char* jmeno)
{
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Chyba prekladu shaderu (%s): %s\n", jmeno, strInfoLog);
        delete[] strInfoLog;
        return false;
    }
    return true;
}

static bool zkontrolujProgram(GLuint program)
{
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Chyba linkovani programu: %s\n", strInfoLog);
        delete[] strInfoLog;
        return false;
    }
    return true;
}

int main()
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "ERROR: glewInit selhal\n");
        return EXIT_FAILURE;
    }


    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSwapInterval(1);

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("GLEW: %s\n", glewGetString(GLEW_VERSION));
    printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    glm::mat4 testM = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0, 0, 1));
    printf("GLM test (ma byt 0.707 0.707): %.3f %.3f\n", testM[0][0], testM[0][1]);


    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader, NULL);
    glCompileShader(vertexShader);
    if (!zkontrolujShader(vertexShader, "vertex")) return EXIT_FAILURE;

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
    glCompileShader(fragmentShader);
    if (!zkontrolujShader(fragmentShader, "fragment")) return EXIT_FAILURE;

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fragmentShader);
    glAttachShader(shaderProgram, vertexShader);
    glLinkProgram(shaderProgram);
    if (!zkontrolujProgram(shaderProgram)) return EXIT_FAILURE;

    Model ctverec(pointsCtverec, sizeof(pointsCtverec), 4, GL_TRIANGLE_FAN);

    Model trojuhelnik(pointsTrojuhelnik, sizeof(pointsTrojuhelnik), 3, GL_TRIANGLES);


    

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    double last = glfwGetTime();
    float angle = 1.0f;

    while (!glfwWindowShouldClose(window))
    {
        double now = glfwGetTime();
        float  dt = static_cast<float>(now - last);
        last = now;

        angle += speed * dt;


        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const float px = 0.5f, py = 0.5f;

        glUseProgram(shaderProgram);
        ctverec.draw();
        trojuhelnik.draw();


        glfwSwapBuffers(window);
        GLenum e = glGetError();
        if (e != GL_NO_ERROR) printf("GL error: 0x%x\n", e);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;

}