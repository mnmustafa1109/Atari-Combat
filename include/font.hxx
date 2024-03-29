#ifndef FONT_HXX
#define FONT_HXX
#include "../include/glad.h"

#include "../include/glfw/glfw3.h"
#include "../include/freetype/ft2build.h"
#include <map>
#include "../include/shader.hxx"
#include "../include/glm/glm.hpp"


#include FT_FREETYPE_H

struct Character {
    GLuint TextureID;    // ID handle of the glyph texture
    glm::ivec2 Size;     // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;      // Horizontal offset to advance to next glyph
};

class Font {
   private:
    FT_Library ft;
    GLuint va_font, vb_font;
    FT_Face face;
    Shader* shader;
    std::map<GLchar, Character> Characters;

   public:
    Font();
    Font(std::string name);
    void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale,glm::vec3 color,bool reverse = false);
    void FontInit(std::string name);
    void FontSetup();
};
#endif  // DEBUG