/*
    Randy's UV Visualizer
    
    Texture Coordinates Example
    This example demonstrates how to use texture coordinates in OpenGL.\

    By using texture coordinates, we can map a 2D image onto a 3D object.
    this will be a basic rectangle with a texture applied.

    Final Goal:
    Load and display an Earth texture image on the rectangle.
    After this, the sphere mostly becomes a geometry problem.

    Next Milestone:
    UV gradient rectangle -> image-textured rectangle

*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// shader source strings should not be modified: make them const
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec2 aTexCoord;\n"
    "\n"
    "out vec2 ourTexCoord;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourTexCoord = aTexCoord;\n"
    "}\0";


// FragColor = vec4(ourTexCoord, 0.0, 1.0) should create a UV gradient
// Red = U coordinate
// Green = V coordinate
// Blue = 0.0
// Alpha = 1.0

// Now I'll replace FragColor to be able to sample pixels from an image
// Bug was here with FragColor
/*ourTexture = the image
ourTexCoord = where to sample
texture(ourTexture, ourTexCoord) = the color at that image location*/
const char* fragmentShaderSource = "#version 330 core\n"
    "in vec2 ourTexCoord;\n"
    "out vec4 FragColor;\n"
    "uniform sampler2D ourTexture;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   FragColor = texture(ourTexture, ourTexCoord);\n"
    "}\0";

float vertices[] = {
    // positions          // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
};

// indices for the rectangle
unsigned int indices[] = { 0, 1, 3, 1, 2, 3 };


int main(void) {

    // init GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }   

    // Tell GLFW that we want to use OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creating window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Texture Coordinates", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
    printf("OpenGL version: %s\n", glGetString(GL_VERSION));
    fprintf(stderr, "GLEW version: %s\n", glewGetString(GLEW_VERSION));

    // Compile Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Compile Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Link Shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete Shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Load and create a texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set the texture wrapping and filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load and create the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(1);
    
    // Need to check if the texture was loaded successfully
    unsigned char *data = stbi_load("assets/earth_texture_8k.png", &width, &height, &nrChannels, 0);

    if (data) {
        printf("Texture loaded: %d x %d, channels: %d\n", width, height, nrChannels);

        GLenum format = GL_RGB;
        if (nrChannels == 1) {
            format = GL_RED;
        }
        else if (nrChannels == 3) {
            format = GL_RGB;
        }
        else if (nrChannels == 4) {
            format = GL_RGBA;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        fprintf(stderr, "Failed to load texture\n");
    }

    stbi_image_free(data);

    // Create VAO and VBO and EBO
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind the VAO
    glBindVertexArray(VAO);

    // Bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position xyz
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture coordinates uv
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind the VAO
    glBindVertexArray(0);

   

    while (!glfwWindowShouldClose(window)) {

        // Clear the screen at the beginning of each frame
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        // Use the shader program and set the sampler
        glUseProgram(shaderProgram);
        glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);

        // Bind the texture and give openGL the texture unit
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Bind the VAO
        glBindVertexArray(VAO);

        // Draw the rectangle
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        // I forgot these 2 lines that allow the window to update and respond
        // to the user's input
        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();

    }

    // Terminate GLFW
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
