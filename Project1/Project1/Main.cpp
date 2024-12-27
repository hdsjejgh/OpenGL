#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";




int main() {
	//initialize glfw
	glfwInit();

	//tell glfw what version is being used (its 3(major version).3(minor version))
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//tells glfw what profile is being used
	//core profile contained all modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//defines coordinates of a triangle
	GLfloat vertices[] = {
		-0.75f, -0.75f, 0.0f,
		0.75f,-0.75f,0.0f,
		0.75f,0.75f,0.0f
	};


	//creates 800x800 windows named Hello
	GLFWwindow* window = glfwCreateWindow(400, 225, "Hello", NULL, NULL);
	//error handling for if window doesnt work for some reason
	if (window == NULL) { std::cout << "Failed to create window" << std::endl; glfwTerminate(); return -1; }

	//adds window to current context
	glfwMakeContextCurrent(window);
	//load glad
	gladLoadGL();

	//specify viewport (from (0,0) to (800,800))
	//honestly no clue what this does, it works fine without it
	glViewport(0, 0, 400, 225);


	//(GLuint is an OpenGL unsigned integer)
	//makes the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//compiles shader to machine code
	glCompileShader(vertexShader);

	//same thing but with fragment shader
	GLuint fragmentShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//creates shader program, adds both shaders to it, then links program to opengl
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	//vertex array object, and vertex buffer object
	GLuint VAO, VBO;
	
	glGenVertexArrays(1, &VAO); //makes vertex array object, have to make make before VBO  **IMPORTANT** 
	glGenBuffers(1, &VBO); //makes buffer object

	glBindVertexArray(VAO); //binds vertex array to opengl
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //same with the array buffer

	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices, GL_STATIC_DRAW);//stores vertices in the buffer

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //honestly no clue what this does
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	//adds changing color to rgba color to back buffer
	glClearColor(1.0f,0.66f,0.00f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//switches front and back buffers
	glfwSwapBuffers(window);

	//keeps window open until you close it
	while (!glfwWindowShouldClose(window)) {

		glClearColor(1.0f, 0.66f, 0.00f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram); //activates shaders
		glBindVertexArray(VAO); //binds vao
		glDrawArrays(GL_TRIANGLES, 0, 3); //draw the triangle
		glfwSwapBuffers(window); //swap buffers to update frame
		glfwPollEvents();

	}

	//deletes vertex things an shader stuff to clean up program just in case
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//destroys window
	glfwDestroyWindow(window);
	//terminates glfw
	glfwTerminate();
	return 0;
}