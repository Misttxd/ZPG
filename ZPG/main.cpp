#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdio>
#include <cstdlib>

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


int main()
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return EXIT_FAILURE;
    }

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

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(px, py, 0.0f);        // 3. posuň zpátky
        glRotatef(angle, x,y,z);  // 2. zarotuj
        glTranslatef(-px, -py, 0.0f);        // 1. posuň P do počátku

        glBegin(GL_TRIANGLE_FAN);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.5f, 0.5f, 0.0f);

            glColor3f(1.0f, 1.0f, 0.0f);
            glVertex3f(0.5f, -0.5f, 0.0f);

            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-0.5f, -0.5f, 0.0f);

            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(-0.5f, 0.5f, 0.0f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;

}