#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// NDC 标准化坐标
// OpenGL仅当3D坐标在3个轴（x、y和z）上的值在-1.0到1.0的范围内时才处理
const float vertices[] = {  // 三个顶点坐标
	-0.5f, -0.5f, 0.0f,     // z轴分量均为0，表明顶点深度均为0，目的是最终渲染一个2d效果的三角形
	0.5f,  -0.5f, 0.0f,
	0.0f,  0.5f,  0.0f
};

void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// 创建窗口
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "firstwindow", nullptr, nullptr);
	if (!window) {
		cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // 将当前opengl上下文绑定到窗口

	// 注册窗口相关的回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad加载opengl函数地址
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

	while (!glfwWindowShouldClose(window)) {  // main Render Loop
		// 接收用户指令
		processInput(window);                
		
		// 渲染迭代中执行的指令
		glClearColor(0.1, 0.2, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
	
	//  双缓冲技术，用两个内存区域来保存数据，分为前缓冲区和后缓冲区
	//  前缓冲区：显示绘制完成后的屏幕内容
	//  后缓冲区：进行绘制运算
	//  每一帧开始的时候，将两个缓冲区交换，这样后缓冲区又可以在前一帧基础上绘制新内容
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
 	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	std::cout << "Enter framebuffer_size " << "width: " << width << " height:" << height << std::endl;
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		cout << "Escape window" << endl;
		glfwSetWindowShouldClose(window, true);
	}
}