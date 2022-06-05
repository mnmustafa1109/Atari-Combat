#ifndef TEXTURE_HXX
#define TEXTURE_HXX


#include <iostream>

// texture type 
enum TYPE { COLOR, TEXTURE, BOTH };

// class for texture
class Texture {
    unsigned int texture;
    int width;
    int height;
    int nrChannels;

   public:
    Texture();
    Texture(const std::string, bool flip);
    ~Texture();
    unsigned int getTexture();
    void bindTexture();
};

#endif  // !TEXTURE_HXX
