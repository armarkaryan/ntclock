// NTImage.h

#ifndef NTIMAGE_H
#define NTIMAGE_H

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <algorithm>

#include "nttypes.h"
#include "ntobject.h"

class NTImage : public NTObject
{
public:
	// ctor/dtor
	NTImage(NTObject *parent = nullptr, const std::string &name = "");
	NTImage(NTObject* parent, const std::string& name,
			   const std::vector<std::string>& image,
               int x, int y, NTObject::ColorPair color, NTObject::ImageSize size);
	~NTImage();

	// Конструктор копирования
	NTImage(const NTImage& other);

	// Оператор присваивания
	NTImage& operator=(const NTImage& other);

    // Координаты изображения
	void setx(int x){_x = x;}
	int x() const { return _x; }

	void sety(int y){_y = y;}
	int y() const { return _y; }

    //
    NTObject::ColorPair color() const { return _color; }

	//
    void setImage(const std::vector<std::string>& image);
	const std::vector<std::string>& image() const;

	unsigned int width() const;
	unsigned int height() const;
	unsigned int channels() const;
	const std::vector<std::string>& getImageLines() const;

	void resize(unsigned int newWidth, unsigned int newHeight);
    void setColorPair(NTObject::ColorPair pair);
    void setImageSize(NTObject::ImageSize size);

private:
    std::vector<std::string> _image;
	std::vector<std::string> _imageLines;
	unsigned int _width;
	unsigned int _height;
	unsigned int _channels;
	int _x;
	int _y;
    NTObject::ColorPair _color;
    NTObject::ImageSize _size;

	void copyFrom(const NTImage& other);
	void clearImage();
	void updateImageFromLines();
	void updateLinesFromImage();
};

#endif // NTIMAGE_H
