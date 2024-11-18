
// Headers
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <Core/Global.h>
#include <Util/Path.h>
#include <Components/Camera.h>

// Vertex shader
const std::string vertexShader = 
    "#version 330 core\n"
    "in vec3 pos;\n"
    "in vec2 texCoords;\n"
    "out vec2 TexCoords;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(pos, 1.0);\n"
    "    TexCoords = texCoords;\n"
    "}\n";
// Geometry shader
const std::string geometryShader = 
    "#version 330 core\n"
    "layout(points) in;\n"
    "layout(triangle_strip, max_vertices = 36) out;\n" // 6 faces * 2 triangles * 3 vertices
    "in vec2 TexCoords[];\n"
    "out vec2 FragTexCoords;\n"
    "uniform mat4 mvp;\n"
    "void main()\n"
    "{\n"
    "    FragTexCoords = TexCoords[0];\n"

    // Define the vertices for the cube
    "    vec4 vertices[8];\n"
    "    vertices[0] = vec4( 0.1,  0.1,  0.1, 1.0);\n" // Front top right
    "    vertices[1] = vec4( 0.1, -0.1,  0.1, 1.0);\n" // Front bottom right
    "    vertices[2] = vec4(-0.1, -0.1,  0.1, 1.0);\n" // Front bottom left
    "    vertices[3] = vec4(-0.1,  0.1,  0.1, 1.0);\n" // Front top left
    "    vertices[4] = vec4( 0.1,  0.1, -0.1, 1.0);\n" // Back top right
    "    vertices[5] = vec4( 0.1, -0.1, -0.1, 1.0);\n" // Back bottom right
    "    vertices[6] = vec4(-0.1, -0.1, -0.1, 1.0);\n" // Back bottom left
    "    vertices[7] = vec4(-0.1,  0.1, -0.1, 1.0);\n" // Back top left

    // Front face
    "    gl_Position = mvp * vertices[0]; EmitVertex();\n"
    "    gl_Position = mvp * vertices[1]; EmitVertex();\n"
    "    gl_Position = mvp * vertices[3]; EmitVertex();\n"
    "    gl_Position = mvp * vertices[2]; EmitVertex();\n"
    "    EndPrimitive();\n"

    // Back face
    "    gl_Position = mvp * vertices[4]; EmitVertex();\n"
    "    gl_Position = mvp * vertices[5]; EmitVertex();\n"
    "    gl_Position = mvp * vertices[7]; EmitVertex();\n"
    "    gl_Position = mvp * vertices[6]; EmitVertex();\n"
    "    EndPrimitive();\n"

    // Left face
    "    gl_Position = mvp * vertices[3]; EmitVertex();\n"
    "    gl_Position = mvp * vertices[2]; EmitVertex();\n"
    "    gl_Position = mvp * vertices[6]; EmitVertex();\n"
    "    gl_Position = mvp * vertices[7]; EmitVertex();\n"
    "    EndPrimitive();\n"

    // Right face
    "    gl_Position = mvp * vertices[0]; EmitVertex();\n"
    "    gl_Position = mvp * vertices[1]; EmitVertex();\n"
    "    gl_Position = mvp * vertices[5]; EmitVertex();\n"
    "    gl_Position = mvp * vertices[4]; EmitVertex();\n"
    "    EndPrimitive();\n"

    // Top face
    "    gl_Position = mvp * vertices[3]; EmitVertex();\n"
    "    gl_Position = mvp * vertices[0]; EmitVertex();\n"
    "    gl_Position = mvp * vertices[4]; EmitVertex();\n"
    "    gl_Position = mvp * vertices[7]; EmitVertex();\n"
    "    EndPrimitive();\n"

    // Bottom face
    "    gl_Position = mvp * vertices[1]; EmitVertex();\n"
    "    gl_Position = mvp * vertices[2]; EmitVertex();\n"
    "    gl_Position = mvp * vertices[6]; EmitVertex();\n"
    "    gl_Position = mvp * vertices[5]; EmitVertex();\n"
    "    EndPrimitive();\n"

    "}\n";
/*const std::string geometryShader = */
/*    "#version 330 core\n"*/
/*    "layout(points) in;\n"*/
/*    "layout(line_strip, max_vertices = 16) out;\n"*/
/*    "in vec2 TexCoords[];\n"*/
/*    "out vec2 FragTexCoords;\n"*/
/*    "uniform mat4 mvp;\n"*/
/*    "void main()\n"*/
/*    "{\n"*/
/*    "    FragTexCoords = TexCoords[0];\n"*/
/*    "    gl_Position = mvp * gl_in[0].gl_Position;\n"*/
/*    "    vec4 NEU = mvp * vec4( 0.1,  0.1,  0.1, 0.0);\n"*/
/*    "    vec4 NED = mvp * vec4( 0.1, -0.1,  0.1, 0.0);\n"*/
/*    "    vec4 NWU = mvp * vec4( 0.1,  0.1, -0.1, 0.0);\n"*/
/*    "    vec4 NWD = mvp * vec4( 0.1, -0.1, -0.1, 0.0);\n"*/
/*    "    vec4 SEU = mvp * vec4(-0.1,  0.1,  0.1, 0.0);\n"*/
/*    "    vec4 SED = mvp * vec4(-0.1, -0.1,  0.1, 0.0);\n"*/
/*    "    vec4 SWU = mvp * vec4(-0.1,  0.1, -0.1, 0.0);\n"*/
/*    "    vec4 SWD = mvp * vec4(-0.1, -0.1, -0.1, 0.0);\n"*/
/*    "    gl_Position = gl_in[0].gl_Position + NED;\n"*/
/*    "    EmitVertex();\n"*/
/*    "    gl_Position = gl_in[0].gl_Position + NWD;\n"*/
/*    "    EmitVertex();\n"*/
/*    "    gl_Position = gl_in[0].gl_Position + SWD;\n"*/
/*    "    EmitVertex();\n"*/
/*    "    gl_Position = gl_in[0].gl_Position + SED;\n"*/
/*    "    EmitVertex();\n"*/
/*    "    gl_Position = gl_in[0].gl_Position + SEU;\n"*/
/*    "    EmitVertex();\n"*/
/*    "    gl_Position = gl_in[0].gl_Position + SWU;\n"*/
/*    "    EmitVertex();\n"*/
/*    "    gl_Position = gl_in[0].gl_Position + NWU;\n"*/
/*    "    EmitVertex();\n"*/
/*    "    gl_Position = gl_in[0].gl_Position + NEU;\n"*/
/*    "    EmitVertex();\n"*/
/*    "    gl_Position = gl_in[0].gl_Position + NED;\n"*/
/*    "    EmitVertex();\n"*/
/*    "    gl_Position = gl_in[0].gl_Position + SED;\n"*/
/*    "    EmitVertex();\n"*/
/*    "    gl_Position = gl_in[0].gl_Position + SEU;\n"*/
/*    "    EmitVertex();\n"*/
/*    "    gl_Position = gl_in[0].gl_Position + NEU;\n"*/
/*    "    EmitVertex();\n"*/
/*    "    gl_Position = gl_in[0].gl_Position + NWU;\n"*/
/*    "    EmitVertex();\n"*/
/*    "    gl_Position = gl_in[0].gl_Position + NWD;\n"*/
/*    "    EmitVertex();\n"*/
/*    "    gl_Position = gl_in[0].gl_Position + SWD;\n"*/
/*    "    EmitVertex();\n"*/
/*    "    gl_Position = gl_in[0].gl_Position + SWU;\n"*/
/*    "    EmitVertex();\n"*/
/*    "    EndPrimitive();\n"*/
/*    "}\n";*/

// Fragment shader
const std::string fragmentShader = 
    "#version 330 core\n"
    "in vec2 FragTexCoords;\n"
    "out vec4 outColor;\n"
    /*"uniform sampler2d texture;\n"*/
    "void main()\n"
    "{\n"
    "    outColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
    /*"    outColor = vec4(FragTexCoords.x, FragTexCoords.y, 1.0, 1.0);\n"*/
    /*"    outColor = texture2D(texture, FragTexCoords);\n"*/
    "}\n";

// Shader creation helper

int main()
{
    auto t_start = std::chrono::high_resolution_clock::now();

    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    auto& window = Global::getWindow();

    gladLoadGL(sf::Context::getFunction);
    
/*glEnable(GL_DEPTH_TEST);*/
/*glDisable(GL_CULL_FACE); */

    auto assetsDir = Util::getExecutablePath() / "assets";
    auto shadersDir = Util::getExecutablePath() / "shaders";

    auto& textureAtlas = Global::getTexture();
    textureAtlas.loadFromFile(assetsDir / "red.jpg");
    textureAtlas.setSmooth(true);
    // Load shaders
    sf::Shader shader;
    shader.loadFromFile(
        shadersDir / "cube.vert",
        shadersDir / "cube.geo",
        shadersDir / "cube.frag"
    );
    /*shader.loadFromMemory(vertexShader, geometryShader, fragmentShader);*/
    /*shader.setUniform("texture", textureAtlas);*/

    Camera camera;
    camera.setPosition(glm::vec3(0.0f, 0.0f, 0.0f))
          .setTarget(glm::vec3(1.5f, 1.5f, 2.0f))
          .setUp(glm::vec3(0.0f, 0.0f, 1.0f))
          .setProjection(ProjectionType::Perspective)
          .setFOV(45.0f)
          .setNearFar(1.0f, 10.0f)
          .setAspectRatio()
          .update();

    GLfloat points[] = {
        //  Coordinates             Color
        -0.45f,  0.45f, -0.45f, 1.0f, 0.0f, // 0.0f,
         0.45f,  0.45f, -0.45f, 0.0f, 1.0f, // 0.0f,
         0.45f, -0.45f, -0.45f, 0.0f, 0.0f, // 1.0f,
        -0.45f, -0.45f, -0.45f, 1.0f, 1.0f, // 0.0f,
        -0.45f,  0.45f,  0.45f, 0.0f, 1.0f, // 1.0f,
         0.45f,  0.45f,  0.45f, 1.0f, 0.0f, // 1.0f,
         0.45f, -0.45f,  0.45f, 1.0f, 0.5f, // 0.5f,
        -0.45f, -0.45f,  0.45f, 0.5f, 1.0f, // 0.5f,
    };

    // Create VBO with point coordinates
    GLuint vbo, vao;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    glBindVertexArray(vao);
    GLint posAttrib = glGetAttribLocation(shader.getNativeHandle(), "pos");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

    GLint colAttrib = glGetAttribLocation(shader.getNativeHandle(), "texCoords");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    // Set up transformation matrices
    glm::mat4 view = glm::lookAt(
        glm::vec3(1.5f, 1.5f, 2.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);

    bool running = true;
    while (running)
    {
        sf::Event windowEvent;
        while (window.pollEvent(windowEvent))
        {
            if (windowEvent.type == sf::Event::Closed)
                running = false;
        }

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Calculate transformation
        auto t_now = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(
            model,
            0.25f * time * glm::radians(180.0f),
            glm::vec3(0.0f, 0.0f, 1.0f)
        );
        /*auto vp = camera.getVP();*/
        auto vp = proj * view;

        // Set the model matrix uniform
        shader.setUniform("mvp", sf::Glsl::Mat4(glm::value_ptr(vp * model)));

        // Use the shader program
        sf::Shader::bind(&shader);

        // Render frame
        glBindVertexArray(vao);
        glDrawArrays(GL_POINTS, 0, 8);

        // Swap buffers
        window.display();
    }

    // Cleanup
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    window.close();
    return 0;
}
