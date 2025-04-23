// NTImage.cpp

#include "ntimage.h"

// Простой конструктор
NTImage::NTImage(NTObject* parent, const std::string& name)
	: NTObject(parent, name), _width(8), _height(8), _transparent(true),
	  _x(0), _y(0), _colorPair(nt::DEFAULT)
{
    // To do... image, width, height, chanals
}

// Полный конструктор
NTImage::NTImage(NTObject* parent, const std::string& name,
               const std::vector<std::string>& image,
			   int x, int y, nt::ColorPair colorPair)
	: NTObject(parent, name), _image(image), _x(x), _y(y), _colorPair(colorPair)
{
    // To do... image, width, height, chanals
}

// Конструктор копирования
NTImage::NTImage(const NTImage& other)
    : NTObject(other.parent(), other.name()),
      _image(other._image),
      _x(other._x),
      _y(other._y),
	  _colorPair(other._colorPair)
{
    // To do... width, height, chanals
}

// Деструктор
NTImage::~NTImage() = default;

// Оператор присваивания
NTImage& NTImage::operator=(const NTImage& other)
{
	if (this != &other) {
		NTObject::operator=(other);
		_image = other._image;
		_x = other._x;
		_y = other._y;
        _colorPair = other._colorPair;
	}
	return *this;
}

//
unsigned int NTImage::width() const
{
	return _width;
}

//
unsigned int NTImage::height() const
{
	return _height;
}

//
bool NTImage::isTransparent() const
{
	return _transparent;
}

//
void NTImage::setImage(const std::vector<std::string>& image)
{
    _image = image;
}

//
const std::vector<std::string>& NTImage::image() const
{
	return _image;
}

//
void NTImage::setColorPair(nt::ColorPair colorPair)
{
    _colorPair = colorPair;
}

//
void NTImage::copyFrom(const NTImage& other)
{
	_image = other._image;
	_width = other._width;
	_height = other._height;
	_transparent = other._transparent;
	_x = other._x;
	_y = other._y;
    _colorPair = other._colorPair;
}

void NTImage::clearImage()
{
	_image.clear();
	_width = 0;
	_height = 0;
	_transparent = true;
}
