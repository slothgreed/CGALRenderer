#ifndef TEXTURE_GENERATOR_H
#define TEXTURE_GENERATOR_H

namespace KI
{

class TextureGenerator
{
public:
	TextureGenerator();
	~TextureGenerator();

	static void UVTexture(int size, TextureData& data);
	static void RamdomTexture(int size, int alpha, TextureData& data);
private:

};

}

#endif TEXTURE_GENERATOR_H