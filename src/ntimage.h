// NTImage.h

#ifndef NTIMAGE_H
#define NTIMAGE_H

#include <vector>
#include <string>

#include "nttypes.h"
#include "ntobject.h"
//#include <algorithm>

class NTImage : public NTObject
{
public:
	/*// Цветовые пары (текст/фон)
	enum ColorPair {
		DEFAULT = 1,
		RED_TEXT,
		GREEN_TEXT,
		BLUE_TEXT,
		YELLOW_TEXT,
		CYAN_TEXT,
		MAGENTA_TEXT,
		WHITE_TEXT,
		CUSTOM
	};

	// Поддерживаемые размеры изображений
	enum ImageSize {
		SIZE_4x4,
		SIZE_8x4,
		SIZE_4x8,
		SIZE_8x8,
		SIZE_8x16,
		SIZE_16x8,
		SIZE_16x16
	};*/

	// ctor/dtor
	NTImage(NTObject *parent = nullptr, const std::string &name = "");
	NTImage(NTObject* parent, const std::string& name,
			   const std::vector<std::string>& image,
			   int x, int y, ColorPair color, ImageSize size);
	/*NTImage(NTObject *parent = nullptr, const std::string &name = "",
			const std::vector<std::string>& image = {},
			int x = 0,
			int y = 0,
			ColorPair color = DEFAULT,
			ImageSize size = SIZE_8x8);*/

/*
	NTImage(NTObject* parent, const std::string& name,
			const std::vector<std::string>& image,
			int x, int y,
			ColorPair color,
			ImageSize size);
*/
	~NTImage();

	// Конструктор копирования
	NTImage(const NTImage& other);

	// Оператор присваивания
	NTImage& operator=(const NTImage& other);

	void setx(int x){_x = x;}
	int x() const { return _x; }

	void sety(int y){_y = y;}
	int y() const { return _y; }

	ColorPair color() const { return _color; }

	//
	void setImage(const std::vector<std::string>& image) { _image = image; }
	//const std::vector<std::string>& image() const { return _image; }
	const std::vector<std::string>& image() const;

	//
	bool loadFromFile(const std::string &filename);
	bool saveToFile(const std::string &filename) const;

	unsigned int width() const;
	unsigned int height() const;
	unsigned int channels() const;
	//const std::vector<unsigned char>& imageData() const;
	const std::vector<std::string>& getImageLines() const;

	void convertToGrayscale();
	void resize(unsigned int newWidth, unsigned int newHeight);
	void setColorPair(ColorPair pair);
	void setImageSize(ImageSize size);
	void setPosition(int x, int y);

private:
	//std::vector<unsigned char> _image;
	std::vector<std::string> _image;  // Change from vector<unsigned char> to vector<string>
	//std::vector<std::string>& image() const;
	std::vector<std::string> _imageLines;
	unsigned int _width;
	unsigned int _height;
	unsigned int _channels;
	int _x;
	int _y;
	ColorPair _color;
	ImageSize _size;

	void copyFrom(const NTImage& other);
	void clearImage();
	void updateImageFromLines();
	void updateLinesFromImage();
};

#endif // NTIMAGE_H
