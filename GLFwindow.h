#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

class GLFWWindow{
    private:
        GLFWwindow* m_window;
    public:
        bool init(int width=1280,int height =720,
            const char * title="detector");
        GLFWwindow * getWindow(){return m_window;}
        bool shouldClose(){ return glfwWindowShouldClose(m_window);}    
        void pollEvents (){return glfwPollEvents();}
        void swapBuffers(){ glfwSwapBuffers(m_window);}
        void cleanup(){ glfwDestroyWindow(m_window);glfwTerminate();}
        void setCurrWindow(){glfwMakeContextCurrent(m_window);
            std::cout << "Making context current for window: " << m_window << std::endl;}
};