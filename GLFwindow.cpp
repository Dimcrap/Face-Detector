#include "GLFwindow.h"

bool GLFWWindow::init(int width,int height ,
    const char * title)
{ 
if(!glfwInit()){
    std::cerr<<"Failed to initialize GLFW\n";
    return false;
}

glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

m_window =glfwCreateWindow(width,height,title,NULL,NULL);
if(!m_window){
    std::cerr<<"Failed to create GLFW window\n";
    glfwTerminate();
    return false;
}

glfwMakeContextCurrent(m_window);
glfwSwapInterval(1);

return true;

};