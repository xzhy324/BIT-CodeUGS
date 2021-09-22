#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "utility/shader.h"
#include <iostream>
#include <cmath>

const float PI=3.1416;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw初始化窗体列表
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader myShader("vs1.vs","fs1.fs");
/*-------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/


    float vertices[] = {
            //位置               //颜色
            0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    };

    GLuint VAO,VBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);


    while(!glfwWindowShouldClose(window)){

        float timeValue=glfwGetTime();
        float rgb[3];
        rgb[0] = sin(timeValue) / 2.0f + 0.5f;
        rgb[1] = sin(timeValue+2.0f/3*PI) / 2.0f + 0.5f;
        rgb[2] = sin(timeValue+4.0f/3*PI) / 2.0f + 0.5f;
        for(int i=0;i<=2;i++){
            vertices[6*i+3+i]=rgb[i];
            vertices[6*i]=rgb[i]-0.5f;
            vertices[6*i+1]=rgb[2-i]-0.5f;
        }
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STREAM_DRAW);//把顶点数组数据带到array——buffer的内存中
        //位置属性
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 6*sizeof(float),(void*)0);//告诉OpenGL该如何使用这些数据,初始化与arraybuffer绑定的顶点对象的属性值
        /*1.顶点属性中的位置地址值 2.一个顶点的属性个数（这里读入3个坐标） 3.对应的数据类型 4.是否希望被标准化 5 两个顶点之间的步长 6 偏移量 */
        glEnableVertexAttribArray(0);//0 是顶点的位置属性地址值，由GLSL定义为0
        //颜色属性
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 6*sizeof(float),(void*) (3*sizeof(float)) );//告诉OpenGL该如何使用这些数据,初始化与arraybuffer绑定的顶点对象的属性值
        /*1.顶点属性中的颜色地址值 2.一个顶点的属性个数（这里读入3个rgb分量） 3.对应的数据类型 4.是否希望被标准化 5 两个顶点之间的步长 6 偏移量 */
        glEnableVertexAttribArray(1);//1 是顶点的颜色属性地址值，由GLSL定义为1


        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        myShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);//起始索引为0，所渲染顶点个数为3

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


/*-------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

/*
#version 330 core
out vec4 FragColor;
in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0);    // note how the position value is linearly interpolated to get all the different colors
}
*/
//==========================================
/*
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
}
*/