#ifndef RESOURCEMAN_HXX
#define RESOURCEMAN_HXX
#include <map>
#include "../include/shader.hxx"
#include "../include/shape.hxx"
#include "../include/texture.hxx"

class ResourceMan {
   public:
    Texture& getTexture(std::string name, std::string path);
    Shader& getShader(std::string name,
                      std::string vertexPath,
                      std::string fragmentPath);
    Shape& getShape(std::string name,
                    SHAPE shape,
                    float x,
                    float y,
                    float z,
                    float width,
                    float height,
                    float rotation,
                    Texture* texture,
                    Shader* shader);
    Texture& getTexture(std::string name);
    Shader& getShader(std::string name);
    Shape& getShape(std::string name);

    static ResourceMan* getInstance();

   private:
    static ResourceMan* instance;
    std::map<std::string, Texture*> textures;
    std::map<std::string, Shader*> shaders;
    std::map<std::string, Shape*> shapes;
};

#endif  // !RESOURCEMAN_HXX