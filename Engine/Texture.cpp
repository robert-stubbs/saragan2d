#include "EnginePCH.h"

#include "Texture.h"
#include "Engine.h"

#include "cErrorLogger.h"

namespace GameEngine
{
	Texture::Texture()
	{
		TextureID = 0;
		loaded = false;
		GeneratedBuffer = false;
		width = 0;
		height = 0;
	}

	Texture::~Texture()
	{
	}


	bool Texture::LoadFile(std::string imagepath, TEXTURETYPES Type)
	{
		TextType = Type;
		switch (Type)
		{
		case SARAGAN_BMP:
		{
			TextureID = LoadBMP(imagepath);
		} break;
		case SARAGAN_RAW:
		{
			TextureID = LoadRAW(imagepath);
		} break;
		case SARAGAN_PNG:
		{

		} break;
		case SARAGAN_JPG:
		{

		} break;
		}

		return true;
	}

	void Texture::GenerateBuffer()
	{

		Engine::getRenderer().GenerateTextureBuffer(
			TextureID,
			width,
			height,
			static_cast<void*>(&image_string),
			COLOR_TYPE::ENGINE_RGB,
			COLOR_TYPE::ENGINE_RGB,
			VALUE_TYPE::UNSIGNED_BYTE
		);

		Engine::getRenderer().BindTextureBufferParams(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		Engine::getRenderer().BindTextureBufferParams(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		Engine::getRenderer().GenerateTextureMipmap();

		Engine::getRenderer().UnbindTextureBuffer();

		GeneratedBuffer = true;
	}

	void Texture::GenerateAlphaBuffer()
	{
		TextureID = 0;


		Engine::getRenderer().GenerateTextureBuffer(
			TextureID,
			width,
			height,
			&imageResp[0],
			COLOR_TYPE::ENGINE_RGBA,
			COLOR_TYPE::ENGINE_RGBA,
			VALUE_TYPE::UNSIGNED_BYTE
		);

		Engine::getRenderer().BindTextureBufferParams(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		Engine::getRenderer().BindTextureBufferParams(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		Engine::getRenderer().GenerateTextureMipmap();

		Engine::getRenderer().UnbindTextureBuffer();

		GeneratedBuffer = true;
	}

	bool Texture::generateTgaBuffer()
	{

		Engine::getRenderer().GenerateTextureBuffer(
			TextureID,
			width,
			height,
			static_cast<void*>(&Data),
			COLOR_TYPE::ENGINE_RGBA,
			COLOR_TYPE::ENGINE_RGBA,
			VALUE_TYPE::UNSIGNED_BYTE
		);

		Engine::getRenderer().BindTextureBufferParams(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		Engine::getRenderer().BindTextureBufferParams(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		Engine::getRenderer().UnbindTextureBuffer();

		GeneratedBuffer = true;
		Data.clear();

		return true;
	}

	bool Texture::generateTgaStructBuffer()
	{
		Engine::getRenderer().GenerateTextureBuffer(
			TextureID,
			tgaFile.imageWidth,
			tgaFile.imageHeight,
			tgaFile.imageData,
			COLOR_TYPE::ENGINE_RGB,
			COLOR_TYPE::ENGINE_RGB,
			VALUE_TYPE::UNSIGNED_BYTE
		);

		Engine::getRenderer().BindTextureBufferParams(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		Engine::getRenderer().BindTextureBufferParams(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		Engine::getRenderer().UnbindTextureBuffer();

		GeneratedBuffer = true;

		return true;
	}

	void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace) {
		size_t pos = 0;
		while ((pos = subject.find(search, pos)) != std::string::npos) {
			subject.replace(pos, search.length(), replace);
			pos += replace.length();
		}
	}

	void trim(std::string& s)
	{
		size_t p = s.find_first_not_of(" \t");
		s.erase(0, p);
		p = s.find_last_not_of(" \t");
		if (std::string::npos != p)
			s.erase(p + 1);
	}


	GLint Texture::LoadBMPFromString(std::string image)
	{
		TextType = SARAGAN_BMP;
		if ((int)image.size() > 0)
		{
			image_string = image;
			bool isSet = false;


			std::istringstream stream(image_string);
			std::string line;

			char lineHeader[54];

			stream.read(lineHeader, sizeof(lineHeader));

			if (lineHeader[0] != 'B' || lineHeader[1] != 'M')
			{
				cErrorLogger::Log().WriteToConsole("Not a correct BMP file\n");
				return 0;
			}
			//cout << ">Correct BMP Format\n";

			// Read ints from the byte array
			unsigned int imageSize = *(int*)&(lineHeader[0x22]);
			width = *(int*)&(lineHeader[0x12]);
			height = *(int*)&(lineHeader[0x16]);

			if (imageSize == 0) { imageSize = width * height * 3; }



			std::ostringstream foobar; // output to string
			foobar << stream.rdbuf();
			image_string = foobar.str();


			loaded = true;
		}
		return 0;
	}

	GLint Texture::LoadPNGFromString(std::string image)
	{
		// Load file and decode image.try
		try {
			unsigned error = lodepng::decodeFromString(imageResp, width, height, image);
			// If there's an error, display it.
			if (error != 0)
			{
				cErrorLogger::Log().WriteToConsole("error ");
				cErrorLogger::Log().WriteToConsole((int)error);
				cErrorLogger::Log().WriteToConsole(": ");
				cErrorLogger::Log().WriteToConsole(lodepng_error_text(error));
				cErrorLogger::Log().WriteToConsole("\n");
				return 1;
			}
		}
		catch (...) {
			cErrorLogger::Log().WriteToConsole("Couldnt Load Texture");
		}
		TextType = SARAGAN_PNG;

		loaded = true;
		return 0;
	}

	bool Texture::LoadTGAFromFile(std::string FilePath)
	{
		FILE* filePtr;
		unsigned char ucharBad;
		short int sintBad;
		long imageSize;
		int colorMode;
		unsigned char colorSwap;

		TGAFILE* f = new TGAFILE();

		// Open the TGA file.
		fopen_s(&filePtr, FilePath.c_str(), "rb");
		if (filePtr == NULL)
		{
			return false;
		}

		// Read the two first bytes we don't need.
		fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
		fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

		// Which type of image gets stored in imageTypeCode.
		fread(&f->imageTypeCode, sizeof(unsigned char), 1, filePtr);

		// For our purposes, the type code should be 2 (uncompressed RGB image)
		// or 3 (uncompressed black-and-white images).
		if (f->imageTypeCode != 2 && f->imageTypeCode != 3)
		{
			fclose(filePtr);
			return false;
		}

		// Read 13 bytes of data we don't need.
		fread(&sintBad, sizeof(short int), 1, filePtr);
		fread(&sintBad, sizeof(short int), 1, filePtr);
		fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
		fread(&sintBad, sizeof(short int), 1, filePtr);
		fread(&sintBad, sizeof(short int), 1, filePtr);

		// Read the image's width and height.
		fread(&f->imageWidth, sizeof(short int), 1, filePtr);
		fread(&f->imageHeight, sizeof(short int), 1, filePtr);

		// Read the bit depth.
		fread(&f->bitCount, sizeof(unsigned char), 1, filePtr);

		// Read one byte of data we don't need.
		fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

		// Color mode -> 3 = BGR, 4 = BGRA.
		colorMode = f->bitCount / 8;
		imageSize = f->imageWidth * f->imageHeight * colorMode;

		// Allocate memory for the image data.
		f->imageData = (unsigned char*)malloc(sizeof(unsigned char) * imageSize);

		// Read the image data.
		fread(f->imageData, sizeof(unsigned char), imageSize, filePtr);

		// Change from BGR to RGB so OpenGL can read the image data.
		for (int imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode)
		{
			colorSwap = f->imageData[imageIdx];
			f->imageData[imageIdx] = f->imageData[imageIdx + 2];
			f->imageData[imageIdx + 2] = colorSwap;
		}

		tgaFile = *f;

		fclose(filePtr);
		return true;
	}

	bool Texture::LoadTGAFromString(std::string File)
	{
		std::string uncompTGA = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		std::string compTGA = { 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


		std::istringstream stream(File);

		std::string header = stream.str();
		header.resize(12);


		if (header == compTGA)
		{
			LoadCompressed(File);
			return true;
		}
		else if (header == uncompTGA) {

			LoadUncompressed(File);
			return true;
		}
		loaded = true;
		return false;
	}

	bool Texture::LoadUncompressed(std::string File)
	{
		std::istringstream stream(File);
		TextureType = GL_RGB;

		char* buffer = new char[12];
		stream.read(buffer, 12);

		unsigned char header[6];
		stream.read((char*)header, 6);

		width = (int)header[1] * 256 + (int)header[0];
		height = (int)header[3] * 256 + (int)header[2];
		Bpp = (int)header[4];

		if ((width <= 0) || (height <= 0) || ((Bpp != 24) && (Bpp != 32)))	// Make sure all information is valid
		{
			cErrorLogger::Log().WriteToConsole(" TGA: Invalid Texture Information\n");
			return false;
		}


		if (Bpp == 32)
		{													// Else if its 32 BPP
			TextureType = GL_RGBA;
		}

		bytesPerPixel = Bpp / 8;

		ImageSize = bytesPerPixel * width * height;

		std::ostringstream foobar;
		foobar << stream.rdbuf();
		Data = foobar.str();
		Data.resize(ImageSize);

		for (GLuint cswap = 0; cswap < (GLuint)ImageSize; cswap += bytesPerPixel)
		{
			Data[cswap] ^= Data[cswap + 2] ^= Data[cswap] ^= Data[cswap + 2];
		}

		if (Data.size())
		{
			return true;
		}


		return false;
	}

	bool Texture::LoadCompressed(std::string File)
	{
		std::istringstream stream(File);
		TextureType = GL_RGB;


		char* buffer = new char[12];
		stream.read(buffer, 12);

		unsigned char header[6];
		stream.read((char*)header, 6);

		width = (int)header[1] * 256 + (int)header[0];
		height = (int)header[3] * 256 + (int)header[2];
		Bpp = (int)header[4];

		if ((width <= 0) || (height <= 0) || ((Bpp != 24) && (Bpp != 32)))	// Make sure all information is valid
		{
			cErrorLogger::Log().WriteToConsole("TGA: Invalid Texture Information\n");
			return false;
		}

		if (Bpp == 32)
		{													// Else if its 32 BPP
			TextureType = GL_RGBA;
		}

		bytesPerPixel = Bpp / 8;

		ImageSize = bytesPerPixel * width * height;

		Data.resize(ImageSize);

		if (Data.size() <= 0)
		{
			return false;
		}

		GLuint pixelcount = height * width;							// Nuber of pixels in the image
		GLuint currentpixel = 0;												// Current pixel being read
		GLuint currentbyte = 0;												// Current byte 
		GLubyte* colorbuffer = (GLubyte*)malloc(bytesPerPixel);			// Storage for 1 pixel

		do {
			GLubyte chunkheader = 0;


			char chunkHeader[1];
			if (!stream.read(chunkHeader, sizeof(GLubyte)))
			{
				return false;
			}

			chunkheader = (GLubyte)chunkHeader[0];

			if (chunkheader < 128)
			{
				chunkheader++;
				for (short counter = 0; counter < chunkheader; counter++)
				{
					char* buffer = new char[bytesPerPixel];
					stream.read(buffer, bytesPerPixel);
					colorbuffer = (::byte*)buffer;

					Data[currentbyte] = colorbuffer[2];
					Data[currentbyte + 1] = colorbuffer[1];
					Data[currentbyte + 2] = colorbuffer[0];

					if (bytesPerPixel == 4)
					{
						Data[currentbyte + 3] = colorbuffer[3];
					}

					currentbyte += bytesPerPixel;
					currentpixel++;

					if (currentpixel > pixelcount)											// Make sure we havent read too many pixels
					{
						return false;
					}

				}

			}
			else {
				chunkheader -= 127;
				char* buffer = new char[bytesPerPixel];
				stream.read(buffer, bytesPerPixel);
				colorbuffer = (::byte*)buffer;
				for (short counter = 0; counter < chunkheader; counter++)
				{
					Data[currentbyte] = colorbuffer[2];
					Data[currentbyte + 1] = colorbuffer[1];
					Data[currentbyte + 2] = colorbuffer[0];
					if (bytesPerPixel == 4)
					{
						Data[currentbyte + 3] = colorbuffer[3];
					}

					currentbyte += bytesPerPixel;
					currentpixel++;

					if (currentpixel > pixelcount)											// Make sure we havent read too many pixels
					{
						return false;
					}
				}
			}



		} while (currentpixel < pixelcount);

		return true;
	}


	GLint Texture::LoadBMP(std::string imagepath)
	{
		// Data read from the header of the BMP file
		unsigned char header[54]; // Each BMP file begins by a 54-bytes header
		unsigned int dataPos;     // Position in the file where the actual data begins
		unsigned int imageSize;   // = width*height*3
		// Actual RGB data
		unsigned char* data;

		trim(imagepath);

		// Open the file
		FILE* file;
		fopen_s(&file, imagepath.c_str(), "rb");
		if (!file)
		{
			cErrorLogger::Log().WriteToConsole("Image could not be opened\n");
			return 0;
		}

		if (fread(header, 1, 54, file) != 54)
		{ // If not 54 bytes read : problem
			cErrorLogger::Log().WriteToConsole("Not a correct BMP file\n");
			return false;
		}

		if (header[0] != 'B' || header[1] != 'M')
		{
			cErrorLogger::Log().WriteToConsole("Not a correct BMP file\n");
			return 0;
		}

		// Read ints from the byte array
		dataPos = *(int*)&(header[0x0A]);
		imageSize = *(int*)&(header[0x22]);
		width = *(int*)&(header[0x12]);
		height = *(int*)&(header[0x16]);

		// Some BMP files are misformatted, guess missing information
		if (imageSize == 0)    imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
		if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

		// Create a buffer
		data = new unsigned char[imageSize];

		// Read the actual data from the file into the buffer
		fread(data, 1, imageSize, file);

		//Everything is in memory now, the file can be closed
		fclose(file);

		// Create one OpenGL texture
		glGenTextures(1, &TextureID);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, TextureID);

		// Give the image to OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

		// When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		// Generate mipmaps, by the way.
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		return TextureID;
	}

	GLint Texture::LoadRAW(std::string imagepath)
	{
		GLuint texture;
		int width, height;
		BYTE* data;
		FILE* file;

		// open texture data
		fopen_s(&file, imagepath.c_str(), "rb");
		if (file == NULL)
		{
			cErrorLogger::Log().WriteToConsole("Failed to open Texture\n");
			return 0;
		}

		// allocate buffer
		width = 256;
		height = 256;
		data = (BYTE*)malloc(width * height * 3);

		// read texture data
		fread(data, width * height * 3, 1, file);
		fclose(file);

		// allocate a texture name
		glGenTextures(1, &texture);

		// select our current texture
		glBindTexture(GL_TEXTURE_2D, texture);

		// select modulate to mix texture with color for shading
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		// when texture area is small, bilinear filter the closest mipmap
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		// when texture area is large, bilinear filter the original
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		// the texture wraps over at the edges (repeat)
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );

		// free buffer
		free(data);

		glBindTexture(GL_TEXTURE_2D, 0);

		return texture;
	}

	GLint Texture::LoadPNG(std::string imagepath)
	{
		// Load file and decode image.
		unsigned error = lodepng::decode(imageResp, width, height, imagepath);

		if (error != 0)
		{
			cErrorLogger::Log().WriteToConsole("error ");
			cErrorLogger::Log().WriteToConsole((int)error);
			cErrorLogger::Log().WriteToConsole(": ");
			cErrorLogger::Log().WriteToConsole(lodepng_error_text(error));
			cErrorLogger::Log().WriteToConsole("\n");
			return 1;
		}

		return 0;
	}

	GLint Texture::LoadJPG(std::string imagepath)
	{
		// Data read from the header of the BMP file
		unsigned char header[54]; // Each BMP file begins by a 54-bytes header
		unsigned int dataPos;     // Position in the file where the actual data begins
		unsigned int width, height;
		unsigned int imageSize;   // = width*height*3
		// Actual RGB data
		unsigned char* data;


		//ReplaceStringInPlace(imagepath, "\\", "/");
		//ReplaceStringInPlace(imagepath, " C", "C");

		// MUST SCAN FILE FOR \\'s
		trim(imagepath);

		// Open the file
		FILE* file;
		fopen_s(&file, imagepath.c_str(), "rb");
		if (!file)
		{
			cErrorLogger::Log().WriteToConsole("Image could not be opened\n");
			return 0;
		}

		if (fread(header, 1, 54, file) != 54)
		{ // If not 54 bytes read : problem
			cErrorLogger::Log().WriteToConsole("Not a correct BMP file\n");
			return false;
		}

		if (header[0] != 'B' || header[1] != 'M')
		{
			cErrorLogger::Log().WriteToConsole("Not a correct BMP file\n");
			return 0;
		}

		// Read ints from the byte array
		dataPos = *(int*)&(header[0x0A]);
		imageSize = *(int*)&(header[0x22]);
		width = *(int*)&(header[0x12]);
		height = *(int*)&(header[0x16]);

		// Some BMP files are misformatted, guess missing information
		if (imageSize == 0)    imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
		if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

		// Create a buffer
		data = new unsigned char[imageSize];

		// Read the actual data from the file into the buffer
		fread(data, 1, imageSize, file);

		//Everything is in memory now, the file can be closed
		fclose(file);

		// Create one OpenGL texture
		GLuint textureID;
		glGenTextures(1, &textureID);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, textureID);

		// Give the image to OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

		// When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		// Generate mipmaps, by the way.
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		TextureID = textureID;
		return textureID;
	}
}