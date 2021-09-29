#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

#include "fs.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"





void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void ProcessInput(GLFWwindow *window);

//
GLint CreateProgram(const std::string & vsstr, const std::string & gsstr, const std::string & fsstr);

// Window dimensions
const GLuint WIDTH = 1500, HEIGHT = 900;

GLFWwindow* window = nullptr;
GLint shaderProgram;
GLuint VBO, VAO, EBO;
bool bIsWireframe = false;
unsigned int texture;



void Init()
{
   // Init GLFW
   glfwInit();

   // Set all the required options for GLFW
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

   // Create a GLFWwindow object that we can use for GLFW's functions
   window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
   glfwMakeContextCurrent(window);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   // Set the required callback functions
   glfwSetKeyCallback(window, key_callback);

   // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
   glewExperimental = GL_TRUE;

   // Initialize GLEW to setup the OpenGL Function pointers
   glewInit();

   // Define the viewport dimensions
//   int width, height;
//   glfwGetFramebufferSize(window, &width, &height);
//   glViewport(0, 0, width, height);
//   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


   // Build and compile our shader program
   //shaderProgram = CreateProgram(gettext("basic.vert"), "", gettext("basic.frag"));
   shaderProgram = CreateProgram(gettext("basic_model_space.vert"), "", gettext("basic.frag"));
}

void CreateModel0()
{
    // Set up vertex data (and buffer(s)) and attribute pointers
 /*  GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // Left
         0.5f, -0.5f, 0.0f, // Right
         0.0f,  0.5f, 0.0f  // Top
   };*/
   GLfloat vertices[] = {
        0.0f, 0.0f,   0.0f, // Left
         45250.5f,  44000.5f,   0.0f, // Right
         -0.5f,  0.5f,   0.0f  // Top
   };

   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);

   // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
   glBindVertexArray(VAO);

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
   glEnableVertexAttribArray(0);

   glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

   glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
}

const float tex_coord_scale = 100;
const float tex_coord_scale2 = 1;

const int COUNT_ELLEMENTS_DRAW = 33;

void CreateModel()
{
    // set up vertex data (and buffer(s)) and configure vertex attributes

   float vertices[] = {

      0,0,0,1,    1,1,1,   0* tex_coord_scale2,0* tex_coord_scale2,
      0,10,0,1,    1,1,1,   1* tex_coord_scale2,0* tex_coord_scale2,
      10,10,0,1,    1,1,1,   1* tex_coord_scale2,1* tex_coord_scale2,
      10,0,0,1,    1,1,1,   0* tex_coord_scale2,1* tex_coord_scale2,

      -19.43327,	12.89543,	-115.00028, 1,   1,1,1,  0.67503,	0.62914,
      -14.57128,	12.63592,	-117.56154, 1,  1,1,1,	0.67206,	0.64398,
      -19.48535,	12.69921,	-117.45734, 1,  1,1,1, 0.67992,	0.63339,

      -24.39947,	12.49844,	-117.35318, 1,   1,1,1,	0.68779,	0.62281,
      -19.48535,	12.69921,	-117.45734, 1,   1,1,1,	0.67992,	0.63339,
      -19.53744,	12.53655,	-119.9144, 1,   1,1,1,	0.68482,	0.63765,

      -19.48535,	12.69921,	-117.45734, 1,   1,1,1,	0.67992,	0.63339,
      -14.57128,	12.63592,	-117.56154, 1,   1,1,1,	0.67206,	0.64398,
      -14.62339,	12.44809,	-120.01859, 1,   1,1,1,	0.67695,	0.64823,

      -19.48535,	12.69921,	-117.45734, 1,   1,1,1,	0.67992,	0.63339,
      -14.62339,	12.44809,	-120.01859, 1,   1,1,1,	0.67695,	0.64823,
      -19.53744,	12.53655,	-119.9144, 1,   1,1,1,	0.68482,	0.63765,

      0,0,0,1,    1,1,1,   0* tex_coord_scale2,0* tex_coord_scale2,
      -4000,0,0,1,    1,1,1,   1000* tex_coord_scale2,0* tex_coord_scale2,
      0,0,-10,1,    1,1,1,   0* tex_coord_scale2,1* tex_coord_scale2,

      10,0,0,1,    1,1,1,   0* tex_coord_scale2,0* tex_coord_scale2,
      4000,0,0,1,    1,1,1,   1000* tex_coord_scale2,0* tex_coord_scale2,
      10,0,-10,1,    1,1,1,   0* tex_coord_scale2,1* tex_coord_scale2,
      
      10,0,-10,1,    1,1,1,   0* tex_coord_scale2,0* tex_coord_scale2,
      10,0, -5000,1,    1,1,1,   1000* tex_coord_scale2,0* tex_coord_scale2,
      20,0,-10,1,    1,1,1,   0* tex_coord_scale2,1* tex_coord_scale2,

      0,0,0,1,    1,1,1,   0* tex_coord_scale2,0* tex_coord_scale2,
      0,0, 5000,1,    1,1,1,   1000* tex_coord_scale2,0* tex_coord_scale2,
      -10,0,0,1,    1,1,1,   0* tex_coord_scale2,1* tex_coord_scale2,

      10,0,3,1,    1,1,1,   0* tex_coord_scale2,0* tex_coord_scale2,
      5000,0,3,1,    1,1,1,   1000* tex_coord_scale2,0* tex_coord_scale2,
      10,5000,3,1,    1,1,1,   0* tex_coord_scale2,1000* tex_coord_scale2,

   };

   unsigned int indices[]  = {
      0,1,2,2,3,0, 4,5,6,7,8,9, 10,11,12,13,14,15,
      16,17,18, 19,20,21, 22,23,24, 25,26,27, 28,29,30
   };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);   // 3  4
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(4 * sizeof(float)));   // 3  4
    glEnableVertexAttribArray(1);

    // texture coord attribute

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)((4 + 3) * sizeof(float)));   // 6  7
    glEnableVertexAttribArray(2);
}

void CreateTexture()
{
    // load and create a texture 
    // -------------------------
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load("diff_2.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

GLint CreateProgram(const std::string &vsstr, const std::string &gsstr, const std::string &fsstr)
{
   GLint vertexShaderIdx = 0, geometryShaderIdx = 0, fragmentShaderIdx = 0;
   vertexShaderIdx = glCreateShader(GL_VERTEX_SHADER);
   if(!vsstr.empty())
   {
      GLint vertexShaderStatus = 0;
      std::string vertexShaderLog;
      if(vertexShaderIdx)
      {
         const GLsizei vertexShaderSourceSize = vsstr.size();
         const char * vssrc =  vsstr.c_str();
         glShaderSource(vertexShaderIdx, 1, &vssrc, &vertexShaderSourceSize);
         glCompileShader(vertexShaderIdx);
         glGetShaderiv(vertexShaderIdx, GL_COMPILE_STATUS, &vertexShaderStatus);
         if(vertexShaderStatus == GL_FALSE)
         {
            vertexShaderLog.resize(65535);
            GLsizei writen = 0;
            glGetShaderInfoLog(vertexShaderIdx, vertexShaderLog.size(), &writen, &vertexShaderLog[0]);
            printf("%s\n", vertexShaderLog.c_str());
            return 0;
         }
      }
   }
   if(!gsstr.empty())
   {
      geometryShaderIdx = glCreateShader(GL_GEOMETRY_SHADER);
      GLint geometryShaderStatus = 0;
      std::string geometryShaderLog;
      if(geometryShaderIdx)
      {
         const GLsizei geometryShaderSourceSize = gsstr.size();
         const char * gssrc =  gsstr.c_str();
         glShaderSource(geometryShaderIdx, 1, &gssrc, &geometryShaderSourceSize);
         glCompileShader(geometryShaderIdx);
         glGetShaderiv(geometryShaderIdx, GL_COMPILE_STATUS, &geometryShaderStatus);
         if(geometryShaderStatus == GL_FALSE)
         {
            geometryShaderLog.resize(65535);
            GLsizei writen = 0;
            glGetShaderInfoLog(geometryShaderIdx, geometryShaderLog.size(), &writen, &geometryShaderLog[0]);
            printf("%s\n", geometryShaderLog.c_str());
            return 0;
         }
      }
   }
   if(!fsstr.empty())
   {
      fragmentShaderIdx = glCreateShader(GL_FRAGMENT_SHADER);
      GLint fragmentShaderStatus = 0;
      std::string fragmentShaderLog;
      if(fragmentShaderIdx)
      {
         const GLsizei fragmentShaderSourceSize = fsstr.size();
         const char * fssrc =  fsstr.c_str();
         glShaderSource(fragmentShaderIdx, 1, &fssrc, &fragmentShaderSourceSize);
         glCompileShader(fragmentShaderIdx);
         glGetShaderiv(fragmentShaderIdx, GL_COMPILE_STATUS, &fragmentShaderStatus);
         if(fragmentShaderStatus == GL_FALSE)
         {
            fragmentShaderLog.resize(65535);
            GLsizei writen = 0;
            glGetShaderInfoLog(fragmentShaderIdx, fragmentShaderLog.size(), &writen, &fragmentShaderLog[0]);
            printf("%s\n", fragmentShaderLog.c_str());
            return 0;
         }
      }
   }
   GLint link_status = 0;
   std::string programLog;
   GLint program = glCreateProgram();
   if(vertexShaderIdx) {
      glAttachShader(program, vertexShaderIdx);
   }
   if(geometryShaderIdx) {
      glAttachShader(program, geometryShaderIdx);
   }
   if(fragmentShaderIdx) {
      glAttachShader(program, fragmentShaderIdx);
   }
   glLinkProgram(program);
   glGetProgramiv(program, GL_LINK_STATUS, &link_status);
   if(link_status == GL_FALSE)
   {
      programLog.resize(65535);
      GLsizei writen = 0;
      glGetProgramInfoLog(program, programLog.size(), &writen, &programLog[0]);
      printf("%s\n", programLog.c_str());
      return 0;
   }

   if(vertexShaderIdx) {
      glDetachShader(program, vertexShaderIdx);
      glDeleteShader(vertexShaderIdx);
   }
   if(geometryShaderIdx) {
      glDetachShader(program, geometryShaderIdx);
      glDeleteShader(geometryShaderIdx);
   }
   if(fragmentShaderIdx) {
      glDetachShader(program, fragmentShaderIdx);
      glDeleteShader(fragmentShaderIdx);
   }
   return program;
}



void Draw1()
{
      // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
      //glfwPollEvents();

      // Render
      // Clear the colorbuffer
      glViewport(0, 0, WIDTH, HEIGHT);
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

         // bind Texture
         glBindTexture(GL_TEXTURE_2D, texture);

      // Draw our first triangle
      glUseProgram(shaderProgram);
      glBindVertexArray(VAO);


      //glDrawArrays(GL_TRIANGLES, 0, 3);
      //glBindVertexArray(0);
 ///   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);


      // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
      // -------------------------------------------------------------------------------
      glfwSwapBuffers(window);
      glfwPollEvents();
}

struct UniformMVP
{
   glm::mat4 model;
   glm::mat4 view;
   glm::mat4 proj;
} mvp;

// camera control
double g_xpos, g_ypos;

//glm::vec3 camera_position = glm::vec3(5,5, 15);
glm::vec3 camera_position = glm::vec3(5,-1, 5);
glm::vec3 camera_direction = glm::vec3(0,0,-1);
glm::vec3 camera_up = glm::vec3(0, 1, 0);


void Update(GLFWwindow *window)
{
   double xpos, ypos; 
   float deltaX, deltaY, deltaZ, strafe;
   deltaX = deltaY = deltaZ = strafe = 0;
   glfwGetCursorPos(window, &xpos, &ypos);

   if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
   {
      deltaX = g_xpos - xpos;
      deltaY = g_ypos - ypos; 
      
      if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      {
          deltaZ = 1;  
      }

      if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      {
          deltaZ = -1;  
      }

      if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      {
          strafe = -1;  
      }

      if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      {
          strafe = 1;  
      }
   }

   auto rotation = glm::quat(glm::vec3(deltaY * 0.002f, deltaX * -0.002f,0));
   camera_direction = camera_direction * rotation;
   //camera_up = camera_up * rotation;

   glm::vec3 right = glm::cross(camera_direction, camera_up);

   camera_position += (camera_direction * deltaZ * 0.1f);
   camera_position += (right * strafe * 0.1f);

   g_xpos = xpos;
   g_ypos = ypos;

   static auto startTime = std::chrono::high_resolution_clock::now();

   auto currentTime = std::chrono::high_resolution_clock::now();
   float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

   time = 1;

   //mvp.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
   mvp.model = glm::mat4(1.0f);
   //mvp.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

   mvp.view = glm::lookAt(camera_position, camera_position + camera_direction, camera_up);
   //mvp.view = glm::mat4(1.0f);
   //mvp.view = glm::lookAt(glm::vec3(5,5, 15), glm::vec3(5,5, -5), glm::vec3(0.0f, 1.0f, 0.0f));
   mvp.proj = glm::perspective(glm::radians(45.0f), WIDTH / (float) HEIGHT, 0.1f, 1000.0f);
   mvp.proj[1][1] *= -1;

   GLint modelLocation = glGetUniformLocation(shaderProgram, "model");
   glProgramUniformMatrix4fv(shaderProgram, modelLocation, 1, false,  glm::value_ptr(mvp.model));

   GLint viewLocation = glGetUniformLocation(shaderProgram, "view");
   glProgramUniformMatrix4fv(shaderProgram, viewLocation, 1, false,  glm::value_ptr(mvp.view));

   GLint projLocation = glGetUniformLocation(shaderProgram, "proj");
   glProgramUniformMatrix4fv(shaderProgram, projLocation, 1, false,  glm::value_ptr(mvp.proj));
}

void Draw()
{

      // Render
      // Clear the colorbuffer
      
      glViewport(0, 0, WIDTH, HEIGHT);
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // bind Texture
      glBindTexture(GL_TEXTURE_2D, texture);

      // Draw our first triangle
      glUseProgram(shaderProgram);
      glBindVertexArray(VAO);

      //glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);
      glDrawElements(GL_TRIANGLES, COUNT_ELLEMENTS_DRAW, GL_UNSIGNED_INT, 0);


      // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
      // -------------------------------------------------------------------------------
      glfwSwapBuffers(window);
      glfwPollEvents();
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
}


// The MAIN function, from here we start the application and run the game loop
int main()
{
   Init();
   CreateModel();
   CreateTexture();

   // Game loop
   while (!glfwWindowShouldClose(window))
   {
      // input
      // -----
      //ProcessInput(window);
      Update(window);

      Draw();
   }

   // Properly de-allocate all resources once they've outlived their purpose
   glDeleteVertexArrays(1, &VAO);
   glDeleteBuffers(1, &VBO);
   glDeleteBuffers(1, &EBO);

   // Terminate GLFW, clearing any resources allocated by GLFW.
   glfwTerminate();
   return 0;
}

// Is called whenever a key is pressed/released via GLFW
/*void processInput(GLFWwindow* window)
{
   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
       glfwSetWindowShouldClose(window, GL_TRUE);


   else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
   {
      if(bIsWireframe == false)
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      else
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

      bIsWireframe = !bIsWireframe;
   }
}*/

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
   if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
       glfwSetWindowShouldClose(window, GL_TRUE);

   else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
   {
      if(bIsWireframe == false)
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      else
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

      bIsWireframe = !bIsWireframe;
   }
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void ProcessInput(GLFWwindow *window)
{
   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);

    //glfwGetMonitorUserPointer()  

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
