#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "lodepng.h"
namespace GameEngine
{
	typedef struct
	{
		unsigned char imageTypeCode;
		short int imageWidth;
		short int imageHeight;
		unsigned char bitCount;
		unsigned char* imageData;
	} TGAFILE;

	enum TEXTURETYPES {
		SARAGAN_BMP = 0,
		SARAGAN_RAW,
		SARAGAN_PNG,
		SARAGAN_JPG,
		SARAGAN_TGA
	};

	class Texture
	{

	public:

		Texture();
		~Texture();

		std::vector<unsigned char> imageResp;
		std::string image_string;
		std::string Data;

		unsigned int width, height;
		bool loaded;
		bool GeneratedBuffer;
		GLuint TextureID = 0;

		GLuint TextureType = GL_RGB;
		int Bpp;
		int bytesPerPixel;
		int ImageSize;

		TGAFILE tgaFile;

		TEXTURETYPES TextType;

		bool LoadFile(std::string imagepath, TEXTURETYPES Type);

		void GenerateBuffer();
		void GenerateAlphaBuffer();
		bool generateTgaBuffer();
		bool generateTgaStructBuffer();

		GLint LoadBMP(std::string imagepath);
		GLint LoadRAW(std::string imagepath);
		GLint LoadPNG(std::string imagepath);
		GLint LoadJPG(std::string imagepath);

		GLint LoadBMPFromString(std::string image);
		GLint LoadPNGFromString(std::string image);


		bool LoadTGAFromFile(std::string FilePath);
		bool LoadTGAFromString(std::string File);
		bool LoadUncompressed(std::string File);
		bool LoadCompressed(std::string File);

	};
}

#endif