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

glewExperimental=GL_TRUE;
GLenum glewErr=glewInit();
if(glewErr!=GLEW_OK){
    std::cerr<<"Failed to initialize GLEW:"
            <<glewGetErrorString(glewErr)<<std::endl;
    glfwTerminate();
    return false;
}

std::cout<<"OpenGL Version :"<<glGetString(GL_VERSION)<<std::endl;
std::cout<<"GLSL Version:"<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;
glfwSwapInterval(1);

return true;

};