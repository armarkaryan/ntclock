// NTImage.h

#ifndef NTIMAGE_H
#define NTIMAGE_H

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <algorithm>

#include "ntobject.h"

class NTImage : public NTObject
{
public:
	// ctor/dtor
	NTImage(NTObject *parent = nullptr, const std::string &name = "");
    NTImage(NTObject *parent, const std::string& name,
			   const std::vector<std::string>& image,
			   int x, int y, nt::ColorPair colorPair);
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
	void setImage(const std::vector<std::string>& image);
	const std::vector<std::string>& image() const;

    //
	void setColorPair(nt::ColorPair colorPair);
	nt::ColorPair colorPair() const { return _colorPair; }

	//
	void setWidth(unsigned int width){ _width = width; }
	unsigned int width() const;

	//
	void setHeight(unsigned int height){ _height = height; }
	unsigned int height() const;

	//
	void setTransparent(unsigned int transparent){ _transparent = transparent; }
	bool isTransparent() const;

private:
    std::vector<std::string> _image;
	unsigned int _width;
	unsigned int _height;
	bool _transparent;
	int _x;
	int _y;
	nt::ColorPair _colorPair;

	void copyFrom(const NTImage& other);
	void clearImage();
};

#endif // NTIMAGE_H
