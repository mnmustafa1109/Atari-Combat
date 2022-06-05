#include "../include/font.hxx"
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <string>
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include "../include/resourceman.hxx"
#include "../include/shader.hxx"

// DOnt call this function directly i said DO NOT
Font::Font(){};

// pass the name of the font and the contructor will init and render all the
// glyphs in it
Font::Font(std::string name) {
    this->FontInit(name);
    this->FontSetup();
}

// pass the string text , axis of positon , its scale  color and if you want to
// print it with some padding i mean like setw wala alternative
void Font::RenderText(std::string text,
                      GLfloat x,
                      GLfloat y,
                      GLfloat scale,
                      glm::vec3 color,
                      bool reverse) {
    // Binding vertex array for font class
    glUseProgram(0);
    glBindVertexArray(0);
    glActiveTexture(0);
    shader->use();
    shader->setv3f("textColor", color[0], color[1], color[2]);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(va_font);
    // to iterate through the string
    std::string::const_iterator c, e;
    // if reverse is false then print the string from left to right
    if (reverse == false) {
        for (c = text.begin(), e = text.end(); c != e; ++c) {
            // get the glyphs of that characters
            Character ch = Characters[*c];

            GLfloat xpos = x + ch.Bearing.x * scale;
            GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

            GLfloat w = ch.Size.x * scale;
            GLfloat h = ch.Size.y * scale;
            // Update vb_font for each character
            GLfloat vertices[6][4] = {
                {xpos, ypos + h, 0.0, 0.0},    {xpos, ypos, 0.0, 1.0},
                {xpos + w, ypos, 1.0, 1.0},

                {xpos, ypos + h, 0.0, 0.0},    {xpos + w, ypos, 1.0, 1.0},
                {xpos + w, ypos + h, 1.0, 0.0}};
            // Render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            // Update content of vb_font memory
            glBindBuffer(GL_ARRAY_BUFFER, vb_font);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices),
                            vertices);  // Be sure to use glBufferSubData and
                                        // not glBufferData
            // Unbinding the currently bound buffer
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // Render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // Now advance cursors for next glyph (note that advance is number
            // of 1/64 pixels)
            x += (ch.Advance >> 6) *
                 scale;  // Bitshift by 6 to get value in pixels (2^6 = 64
                         // (divide amount of 1/64th pixels by 64 to get amount
                         // of pixels))
        }
    } else {
        // reverse the string
        std::string rev_text = text;
        // reverse the string
        std::reverse(rev_text.begin(), rev_text.end());
        // print the string from right to left
        for (c = rev_text.begin(), e = rev_text.end(); c != e; ++c) {
            // get the glyphs of the characters
            Character ch = Characters[*c];

            GLfloat xpos = x - ch.Bearing.x * scale;
            GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

            GLfloat w = ch.Size.x * scale;
            GLfloat h = ch.Size.y * scale;
            // Update vb_font for each character
            GLfloat vertices[6][4] = {
                {xpos - w, ypos + h, 0.0, 0.0}, {xpos - w, ypos, 0.0, 1.0},
                {xpos, ypos, 1.0, 1.0},

                {xpos - w, ypos + h, 0.0, 0.0}, {xpos, ypos, 1.0, 1.0},
                {xpos, ypos + h, 1.0, 0.0}};
            // Render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            // Update content of vb_font memory
            glBindBuffer(GL_ARRAY_BUFFER, vb_font);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices),
                            vertices);  // Be sure to use glBufferSubData and
                                        // not glBufferData
            // Unbinding the currently bound buffer
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // Render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // Now advance cursors for next glyph (note that advance is number
            // of 1/64 pixels)
            x -= (ch.Advance >> 6) *
                 scale;  // Bitshift by 6 to get value in pixels (2^6 = 64
                         // (divide amount of 1/64th pixels by 64 to get amount
                         // of pixels))
        }
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

// pass the name of the font and the and it will find the font file and load it
void Font::FontInit(std::string name) {
    // Compile and setup the shader
    ResourceMan* resman = ResourceMan::getInstance();
    // projection matrix and the shader
    shader = &resman->getShader("textshader");
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(90.0f), (float)800 / (float)600,
                                  0.1f, 100.0f);
    shader->use();
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projection1"), 1,
                       GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, "view1"), 1, GL_FALSE,
                       glm::value_ptr(view));
    // Load the freetype library
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library"
                  << std::endl;
    }
    std::string f_name = "../data/fonts/" + name;
    // Load font as face from the file
    if (FT_New_Face(ft, f_name.c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }
    // render quality of the font
    FT_Set_Pixel_Sizes(face, 0, 96);
    printf("FreeType Initialization successfull\n");

    return;
}

void Font::FontSetup() {
    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load first 128 characters of ASCII set
    for (GLubyte c = 0; c < 128; c++) {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
                     face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                     face->glyph->bitmap.buffer);

        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned>(face->glyph->advance.x)};
        Characters.insert(std::pair<GLchar, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    // Destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    // Configure va_font/vb_font for texture quads
    glGenVertexArrays(1, &va_font);
    glGenBuffers(1, &vb_font);
    glBindVertexArray(va_font);
    glBindBuffer(GL_ARRAY_BUFFER, vb_font);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL,
                 GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}