// NTImage.cpp

#include "ntimage.h"

// Простой конструктор
NTImage::NTImage(NTObject* parent, const std::string& name)
    : NTObject(parent, name), _width(8), _height(8), _channels(0),
      _x(0), _y(0), _colorPair(DEFAULT), _size(SIZE_8x8)
{
    // To do... image, width, height, chanals
}

// Полный конструктор
NTImage::NTImage(NTObject* parent, const std::string& name,
               const std::vector<std::string>& image,
               int x, int y, ColorPair colorPair, ImageSize size)
    : NTObject(parent, name), _image(image), _x(x), _y(y), _colorPair(colorPair), _size(size)
{
    // To do... image, width, height, chanals
}

// Конструктор копирования
NTImage::NTImage(const NTImage& other)
    : NTObject(other.parent(), other.name()),
      _image(other._image),
      _x(other._x),
      _y(other._y),
      _colorPair(other._colorPair),
      _size(other._size)
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
		_size = other._size;
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
unsigned int NTImage::channels() const
{
	return _channels;
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
void NTImage::setColorPair(NTObject::ColorPair colorPair)
{
    _colorPair = colorPair;
}

//
void NTImage::setImageSize(NTObject::ImageSize size)
{
	_size = size;
}

//
void NTImage::copyFrom(const NTImage& other)
{
	_image = other._image;
	_width = other._width;
	_height = other._height;
	_channels = other._channels;
	_x = other._x;
	_y = other._y;
    _colorPair = other._colorPair;
	_size = other._size;
}

void NTImage::clearImage()
{
	_image.clear();
	_width = 0;
	_height = 0;
	_channels = 0;
}
