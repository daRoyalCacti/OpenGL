#include "iostream"

//glad must be included before GLWF
//#include "glad/glad.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "callbacks.h"
#include "global.h"
#include "inputs.h"
#include "errors.h"


float vertices[] = {	//normalized derive coordinates
       	-0.5f, -0.5f, 0.0f,
      	 0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
};

//vertex shader code
const char *vertexShaderSource = "#version 330 core\n"
    	"layout (location = 0) in vec3 aPos;\n"
       	"void main(){\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";


const char *fragmentShaderSource = "#version 330 core\n"
    	"out vec4 FragColor;\n"
 	"void main(){\n"
	"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";



int main() {
	//init
	//=========================================================================================================================================
	glfwInit();	//intitalising GLFW
	//configuring GLFW
	//glfwWindowHint(<what option to configure (takes some enums)>, <integer that sets the value>)
	//https://www.glfw.org/docs/latest/window.html#window_hints	(for options)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);		//telling GLFW the opengl version want to use
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);		//in this case 4.6
								// - GLFW makes proper arrangements when creating the OpenGl context
								// - GLFW failes if whne the user does not have the proper version of OpenGl
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//we want to use core-profiling
									// - gets access to a small amount of OpenGl features 
	
	//creating a window object
	GLFWwindow* window = glfwCreateWindow(settings::window_width, settings::window_height, settings::window_name, NULL, NULL);
	if (window == NULL)	//if the window failed to create
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);	//making the windows the main context on the current thread

	//intialising GLAD
	// - required before calling any OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}  

	//tell OpenGL the size and positioning of the viewport inside the window	
	glViewport(settings::viewport_ll, settings::viewport_lr, settings::viewport_width, settings::viewport_height);

	//tell GLFW what to do on window resize
	// - also gets called when the window is first displayed
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	
	//setting Vertex array Object
	// - stores glVertexAttribPointer (for vertex attribute configurations and vertex buffer objects assocated with the vertex attributes)
	unsigned VAO;
	glGenVertexArrays(1, &VAO);

	//bind the VAO first, then bind and set vertex buffers, then configure vertex attributes
	glBindVertexArray(VAO);




	//allocating memory and uploading the vertex data
	unsigned int VBO;	//stores the id of the buffer object
				// - if want more than 1 buffer object, the can be an array of unsigned ints
				
	glGenBuffers(1, &VBO);	//Generating the ids
				// - 1 for 1 object
				// - the ids are stored in VBO
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	//specifying the type of the buffer object
						// in this case it is a vertex buffer so GL_ARRAY_BUFFER
	
	//any buffer calls that are made from here on are referencing the bounding buffer (VBO)
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	//copies the vertex data to the buffers memory
											// - first argument is the type of buffer want to copy into
											// - second argument is the size of the data in bytes to pass the to the buffer
											// - third argument is the actual data
											// - forth argument specifics how to graphics card should manage the supplied data
											//   -- GL_STREAM_DRAW has the data sent once and used a few times (by the GPU)
											//   -- Gl_STATIC_DRAW has the data sent once and used many times
											//   -- GL_DYNAMIC_DRAW has the sent many times (because it is changing) and used many times

	//current have the vertex data stored on the memory of the graphics card in a vertex buffer named VBO
	
	//linking vertex attributes
	// - telling opengl how to interpret the vertex data
	//working with the current bound VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);	//first parameter specifices while attribute to configure
											// - want 0 because position in the vertex shader is set by location = 0
											//second parameter specifies the size of the vertex attribute
											// - vertex attribute is a vec3 so its is composed of 3 values
											//third argument specifies the type of the data
											// - GL_FLOAT size a vec in GLSL consists of floating point values
											//fourth argument specifies if the data should be normalised
											// - Should be true if inputting integer data (not so GL_FALSE)
											//firth argument is the stride (space between consecutive vertex attributes)
											// - the next position is located 3 floats away (tightly packed)
											//last argument is the offset (where the data begins in the buffer)
											// - the data is at the start of the data so 0
											// - requires the weird cast to a void*
	glEnableVertexAttribArray(0);
		


	//compiling the vertex shader
	unsigned vertexShader = glCreateShader(GL_VERTEX_SHADER);	//assigning an ID to reference the vertex shader
									//GL_VERTEX_SHADER because want to create a vertexShader
	
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);	//attaching the shader source code to the sharder object
									// - first argument is the shader object to compile to
									// - second argument specifies how many strings the source code is (only 1 here)
									// - third argument is the actual source code
									// - leave forth argument blank
	
	glCompileShader(vertexShader);		//compiling the shader

	//checking for errors compiling the shader
	check_shader_compile(vertexShader);	//function defined in errors.h	



	//compiling the fragment shader
	//same as for the vertex shader but with GL_FRAGMENT_SHADER
	unsigned fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	check_shader_compile(fragmentShader);



	//Creating the shader program
	// - the linked version of multiple shaders
	// - have to activate this shader program when rendering objects
	// - the activated shader program wil be used when issueing render calls
	//
	// - links the output of each shader to the inputs of the next shader
	
	unsigned shaderProgram = glCreateProgram();	//creating the shader program and attaching it to an id (to reference the object)

	glAttachShader(shaderProgram, vertexShader);	//attach the shaders to the program (in the correct order)
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);		//link the shaders

	check_shaderProgram_linking(shaderProgram);	//defined in errors.h

	glDeleteShader(vertexShader);	//can delete the shader objects now
	glDeleteShader(fragmentShader);	//they've been link into the program object
	


	//render
	//===================================================================================================================================
	
		//the render loop
	// - keeps running until the user says to stop
	while (!glfwWindowShouldClose(window)) {	//was the window instructed to close (e.g. by pressing the 'x')

		processInput(window);		//processing keyboard and mouse inputs

		//clearing the screen (so don't see the results from the previous  frame)
		glClearColor(settings::window_clear_color_r, settings::window_clear_color_g, settings::window_clear_color_b, settings::window_clear_color_a);	//setting the clear color
		glClear(GL_COLOR_BUFFER_BIT);	//want to clear the color buffer
						//also possible
						// - GL_DEPTH_BUFFER BIT
						// - GL_STENCIL_BUFFER_BIT


		glUseProgram(shaderProgram);	//activate the shader program
						//every shader and rendering call after use will use this program object
		
		glBindVertexArray(VAO);		//setting the vertex buffer object to draw along with its attribute pointers

		glDrawArrays(GL_TRIANGLES, 0, 3);	//GL_TRIANGLES because drawing triangles
							// second argument specifies the starting index of the vertex array to draw
							// third arguemtn is for how many vertices to draw




		glfwSwapBuffers(window);	//swaps the color buffer (2D buffer that contains color values for each pixel in the window)
						// - shows the output to the screen
						// - has double buffering because single buffering can cause flickering

		glfwPollEvents();		//checks if any events were triggered (e.g. keyboard and mouse inputs)
						// - updates the window states
						// - calls corresponding functions register via callbacks
	}





	//cleanup
	//=================================================================================================================================
	
	glfwTerminate();	//clean/delete all of GLFW's resources that were allocated


	return 0;
}
