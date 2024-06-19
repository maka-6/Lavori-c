#include <stdio.h>
#include <GLFW/glfw3.h>

int main(){
    glfwInit();

    GLFWwindow * window = glfwCreateWindow( 1980, 1080, "hello", NULL, NULL);

    while (!glfwWindowShouldClose(window)){

    }
    return 0;
}