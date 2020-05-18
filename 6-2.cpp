//Header Inclusions
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// SOIL Image loader Inclusion
#include "SOIL2/SOIL2.h"

using namespace std; // Standard namespace

#define WINDOW_TITLE "Modern OpenGL" // Window title Macro

//Shader program Macro
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version "\n" #Source
#endif


//Variable declaration for shader, window size initialization, buffer and array objects
GLint shaderProgram, WindowWidth = 800, WindowHeight = 600;
GLuint VBO, CubeVAO, LightVAO;

//Subject position and scale
glm::vec3 cubePosition(0.0f, 0.0f, 0.0f);
glm::vec3 cuveScale(2.0f);

//Light position and scale
glm::vec3 lightPostion(0.5f, 0.5f, -3.0f);
glm::vec3 lightScale(0.3f);
glm::vec3 lightPostion(-0.5f, -0.5f, 3.0f);
glm::vec3 lightScale(0.1f);


//Camera position
glm::vec3 cameraPosition(0.0f, 0.0f, -6.0f);

//Camera rotation
float cameraRotation = glm::radians(-25.0f);

//Function prototypes
void UResizeWindow(int, int);
void URenderGraphics(void);
void UCreateShader(void);
void UCreateBuffers(void);
void UGenerateTexture(void);

//Vertex Shader Source Code
const GLchar * vertexShaderSource = GLSL(330,

		layout (location = 0) in vec3 postion; // VAP position 0 for vertex position data
		layout (location = 1) in vec3 normal; // VAP position 1 for normal

		out vec3 Normal; // For outgoing normals to fragment shader
		out vec3 FragmentPos; // For outgoing color / pixels to fragment shader

		// Uniform / Global variables for the transform matrices
		uniform mat4 model;
		uniform mat4 view;
		uniform mat4 projection;

void main(){
	gl_Position = projection * view * model * vec4(position, 1.0f); // transforms vertices to clip coordinates

	FragmentPos = vec3(model * vec4(position, 1.0f)); // Gets fragment / pixel position in world space only (exclude view and projection)

	Normal = mat3(transpose(inverse(model))) * normal; // get normal vectors in world space only and exclude normal translation properties

	}
);


// Cube Fragment Shader Source Code
const GLchar * cubeFragmentShaderSource = GLSL(330,

		in vec3 Normal; // For incoming normals
		in vec3 FragmentPos; // For incoming fragment position

		out vec4 cubeColor; // For outgoing cube color to the GPU

		// Uniform / Global variable for object color, light color, light position, and camera/view position
		uniform vec3 objectColor;
		uniform vec3 lightColor;
		uniform vec3 lightPos;
		uniform vec3 viewPosition;

	void main(){

		//Phong lighting model calculations to generate ambient, diffuse, and specular components

		// Calculate Ambient lighting
		float ambientStrenght = 0.1f; // Set ambient or global lighting strength
		vec3 ambient = ambientStrength * lightColor; // Generate ambient light color


		// Calculate Diffuse lighting
		vec3 norm = normalize(Normal); // Normalize vectors to 1 unit
		vec3 lightDirection = normalize(lightPos - FragmentPos); // Calculate distance (light Direction) between light source and fragments/pixels on
		float impace = max(dot(norm, lightDirection), 0.0); // Calculate diffuse impact by generating dot product of normal and light
		vec3 diffuse = impact * lightColor; // Generate diffuse light color


		// Calculate specular lighting
		float specularIntensity = 1.0f; // Set specular light strenght
		float highlightSize = 16.0f; // Set speculalr highlight size
		vec3 viewDir = normalize(viewPosition - FragmentPos); // Calculate view direction
		vec3 reflectDir = reflect(-lightDirection, norm); // Calculate reflection vector
		// Calculate specular component
		float specularComponent = pow(max(dot(viewDir, reflectDir), 0.0), highlightSize);
		vec3 specular = specularIntensity * specularComponent * lightColor;

		// Calculate specular lighting
			float specularIntensity = 0.1f; // Set specular light strenght
			float highlightSize = 16.0f; // Set speculalr highlight size
			vec3 viewDir = normalize(viewPosition - FragmentPos); // Calculate view direction
			vec3 reflectDir = reflect(-lightDirection, norm); // Calculate reflection vector

			// Calculate specular component
			float specularComponent = pow(max(dot(viewDir, reflectDir), 0.0), highlightSize);
			vec3 specular = specularIntensity * specularComponent * lightColor;

		// Calculate phong result
		vec3 phong = (ambient + diffuse + specular) * objectColor;

		cubecolor = vec4(phong, 1.0f); // Send lighting results to GPU

	}
);


// Lamp Shader Source Code
cont GLchar * lampVertexShaderSource = GLSL(330,

	layout (location = 0) in vec3 position; // VAP position 0 for vertex position data

	// Uniform / Global variables for the transform matrices
	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;

	void main()
	{
		gl_Position = projection * view * model * vec4(position, 1.0f); // Transforms vertices into clip coordinates
	}
);


// Fragment Shader Source Code
const GLchar * lampFragmentShaderSource = GLSL(330,

	out vec4 color; // For outgoing lamp color (smaller cube) to the GPU

	void mai()
	{
		color = vec4(1.0f); // Set color to white (1.0f, 1.0f, 1.0f) with alpha 1.0

	}
);


//Main Program
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow(WINDOW_TITLE);

	glutReshapeFunc(UResizeWindow);


	glewExperimental = GL_TRUE;
		if (glewInit() !=GLEW_OK)
		{
			std::cout << "failed to initialize GLEW" << std::endl;
			return -1;

		}

	UCreateShader();

	UCreateBuffers();

	UGenerateTexture();

	//Uses the Shader program
	glUseProgram(shaderProgram);

	glClearColor(0.0f 0.0f, 0.0f, 1.0f); // Sets background color to black

	glutDisplayFunc(URenderGraphics);

	glutMainLoop();

	// Destroys Buffer objects once used
	glDeleteVertexArrays(1, &CubeVAO);
	glDeleteVertexArrays(1, &LightVAO);
	glDeleteBuffers(1, &VBO);

	return 0;
}

// Resizes the window
void UResizeWindow(int w, int h)
{
	WindowWidth = w;
	WindowHeight = h;
	glViewport(0, 0, WindowWidth, WindowHeight);
}


// Renders graphics
void URenderGraphics(void)
{

	glEnable(GL_DEPTH_TEST); // Enable z-depth

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clears the screen

	GLint modelLoc, viewLoc, projLoc, objectColorLoc, lightPositionLoc, viewPositionLoc;

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	// Use the Cube shader and activate the Cube Vertex Array Object for rendering and transforming
	glUseProgram(cubeShaderProgram);
	glBindVertexArray(CubeVAO);

	// Transforms the cube
	model = glm::translate(model, cubePosition);
	model = glm::scale(model, cubeScale);

	// Transforms the camera
	view = glm::translate(view, cameraPostion);
	view = glm::rotate(view, cameraRotation, glm::vec3(0.0f, 1.0f, 0.0f));

	// Set the camera projection to perspective
	projection = glm::perspective(45.0f, (GLfloat)WindowWidth / (GLfloat)WindowHeight, 0.1f, 100.0f);

	// Reference matrix uniforms from the Cube Shader program
	modelLoc = glGetUniformLocation(cubeShaderProgram, "model");
	viewLoc = glGetUniformLocation(cubeShaderProgram, "view");
	projLoc = glGetUniformLocation(cubeShaderProgram, "projection");

	// Pass matrix data to the Cube Shader program's matrix uniforms
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Reference matrix uniforms from the Cube Shader program for the cube color, light color, light position, and camera position
	objectColorLoc = glGetUniformLocation(cubeShaderProgram, "objectColor");
	lightColorLoc = glGetUniformLocation(cubeShaderProgram, "lightColor");
	lightPositionLoc = glGetUniformLocation(cubeShaderProgram, "lightPos");
	viewPositionLoc = glGetUniformLocation(cubeShaderProgram, "viewPosition");

	// Pass color, light, and camera data to the Cube Shader program's corresponding uniforms
	glUniform3f(objectColorLoc, objectColor.r, objectColor.g, objectColor.b);
	glUniform3f(lightColorLoc, lightColor.r, lightColor.g, lightColor.b);
	glUniform3f(lightPositionLoc, lightPosition.x, lightPosition.y, lightPosition.z);

	glUniform3f(viewPositionLoc, cameraPosition.x, cameraPositio.y, cameraPosition.z);

	glUniform3f(viewPositionLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);

	glDrawArrays(GL_TRIANGLES, 0, 36); // Draw the primitives / cube

	glBindVertexArray(0); // Deactivate the Cube Vertex Array Object


	// Use the Lamp Shader and activate the Lamp Vertex Object for rendering and transforming
	glUseProgram(lampShaderProgram);
	glBindVertexArray(LightVAO);

	// Transform the smaller cube used as a visual que for the light source
	model = glm::translate(model, lightPosition);
	model = glm::scale(model, lightScale);

	// Reference matrix uniforms from the Lamp Shader program
	modelLoc = glGetUniformLocation(lampShaderProgram, "model");
	viewLoc = glGetUniformLocation(lampShaderProgram, "view");
	projLoc = glGetUniformLocation(lampShaderProgram, "projection");

	// Pass matrix data to the Lamp Shader program's matrix uniforms
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUnifromMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glDrawArrays(GL_TRIANGLES, 0, 36); // Draw the primitives / small cube(lamp)

	glBindVertexArray(0); // Deactivate the Lamp Vertex Array Object

	glutPostRedisplay(); // marks the current window to be redisplayed
	glutSwapBuffers(); // Flips the back buffer with teh front buffer every frame. Similar to GL FLus


}

// Create the Shader program
void UCreateShader()
{

	// Cube Vertex shader
	GLint cubeVertexShader = glCreateShader(GL_VERTEX_SHADER); // Creates the Vertex shader
	glShaderSource(cubeVertexShader, 1, &vertexShaderSource, NULL); // Attaches the Vertex shader to the source code
	glCompileShader(cubeVertexShader); // Compiles the Vertex shader

	// Cube Fragment shader
	GLint cubeFragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Creates the Fragment shader
	glShaderSource(cubeFragmentShader, 1, &fragmentShaderSource, NULL); // Attaches the Fragment shader to the source code
	glCompileShader(cubeFragmentShader); // Complies the Fragment shader

	// Cube Shader program
	subeShaderProgram = glCreateProgram(); // Creates the Shader program and returns and id
	glAttachShader(cubeShaderProgram, vertexShader); // Attach Vertex shader to the Shader program
	glAttachShader(cubeShaderProgram); //Link Vertex and Fragment shaders to Shader program
	glLinkProgram(cubeShaderProgram); // Link Vertex and Fragment shader to Shader program

	// Delete the Vertex and Fragment shaders once linked
	glDeleteShader(cubeVertexShader);
	glDeleteShader(cubeFragmentShader);

	// Lamp Vertex shader
	GLint lampVertexShader = glCreateShader(GL_VERTEX_SHADER); // Creates the Vertex shader
	glShaderSource(lampFragmentShader, 1, &lampFragmentSource, NULL); // Attaches the Fragment shader to the source code
	glCompileShader(lampFragmentShader); // Compiles the Fragment shader

	// Lamp Shader program
	lampShaderProgram = glCreateProgram(); // Creates the Shader program and returns an id
	glAttachShader(lampShaderProgram,lampVertexShader); // Attach Vertex shader to the Shader program
	glAttachShader(lampShaderProgram, lampFragmentShader);; // attach Fragment shader to the Shader program
	glLinkProgram(lampShaderProgram); // Link Vertex and Fragment shaders to Shader program

	// Delete the lamp shaders once linked
	glDeleteShader(lampVertexShader);
	glDeleteShader(lampFragmentShader);

}


// Creates the Buffer and Array Objects
void UCreateBuffers()
{
	// Position and Texture coordinate data for 18 triangles
	GLfloat vertices[] = {
						// Positions			// Texture Coordinates
						0.0f, 0.0f, -0.5f,		0.0f, 0.0f,
						0.0f, 1.0f, -0.5f,		1.0f, 0.0f,
						1.0f, 1.0f, -0.5f,		1.0f, 1.0f,
						1.0f, 1.0f, -0.5f,		1.0f, 1.0f,
						1.0f, 0.0f, -0.5f,		0.0f, 1.0f,
						0.0f, 0.0f, -0.5f,		0.0f, 0.0f,

						0.0f, 0.0f, -0.5f,		0.0f, 0.0f,
						0.5f, 0.5f, 1.0f,		1.0f, 1.0f,
						0.0f, 1.0f, -0.5f,		1.0f, 0.0f,

						0.0f, 1.0f, -0.5f,		1.0f, 0.0f,
						0.5f, 0.5f, 1.0f,		1.0f, 1.0f,
						1.0f, 1.0f, -0.5f,		0.0f, 0.0f,

						1.0f, 1.0f, -0.5f,		0.0f, 0.0f,
						0.5f, 0.5f, 1.0f,		1.0f, 1.0f,
						1.0f, 0.0f, -0.5f,		0.0f, 0.0f,

						1.0f, 0.0f, -0.5f,		0.0f, 0.0f
						0.5f, 0.5f, 0.5f,		1.0f, 1.0f,
						0.0f, 0.0f, -0.5f,		0.0f, 1.0f,
			};

	// Generate buffer ids for cube
	glGenVertexArray(1,&CubeVAO); // Vertex Array Object for Cube vertices
	glGenBuffers(1, &VBO);

	// Activate the VAO before binding and setting VBOs and VAPs
	glBindVertexArray(CubeVAO);

	// Active the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBuferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Copy vertices to VBO

	// Set attribute pointer 0 to hold Positon data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0); // Enables vertex attribute

	// Set attribute pointer 1 to hold Normal data.
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0); // Deactivates the VAO

		// Generate buffer ids for lamp (smaller cube)
		glGenVertexArray(1, &LightVAO); // Vertex Array Object for Cube vertex copies to serve as light source


		// Activate the VAO before binding and setting any VBOs and VAP
		glBindVertexArray(lightVAO);

		// Reference the same VBO for its vertices
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		// Set attribute pointer 0 to hold Position data (used for the lamp)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (glvoid*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);

}

// Generate and load the texture
void UGenerateTexture(){
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		int width, height;

		unsigned char* image = SOIL_LOAD_image("grid.png", &width, &height, 0, SOIL_LOAD_RGB); // Loads texture file

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture
}
