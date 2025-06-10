// NTImage.cpp

#include "ntimage.h"

// Простой конструктор
NTImage::NTImage(NTObject* parent, const std::string& name)
	: NTObject(parent, name),
	_image({""}),
	_x(0), _y(0),
	_colorPair(nt::DEFAULT),
	_width(0), _height(0),
	_transparent(true)
{
    // To do... image, width, height, chanals
	std::lock_guard<std::mutex> lock(_mutex);
	notifyObservers();
}

// Полный конструктор
NTImage::NTImage(NTObject* parent, const std::string& name,
               const std::vector<std::string>& image,
			   int x, int y, nt::ColorPair colorPair)
	: NTObject(parent, name),
	_image(image),
	_x(x), _y(y),
	_colorPair(colorPair)
{
    // To do... image, width, height, chanals
	std::lock_guard<std::mutex> lock(_mutex);
	notifyObservers();
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
	std::lock_guard<std::mutex> lock(_mutex);
	notifyObservers();
}

// Деструктор
NTImage::~NTImage() = default;

// Оператор присваивания
NTImage& NTImage::operator=(const NTImage& other)
{
	if (this != &other) {
		std::unique_lock<std::mutex> lock1(_mutex, std::defer_lock);
		std::unique_lock<std::mutex> lock2(other._mutex, std::defer_lock);
		std::lock(lock1, lock2);

		NTObject::operator=(other);
		_image = other._image;
		_x = other._x;
		_y = other._y;
        _colorPair = other._colorPair;
	}
	notifyObservers();
	return *this;
}

//
void NTImage::setx(int x)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_x = x;
	notifyObservers();
}

//
int NTImage::x() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _x;
}

//
void NTImage::sety(int y)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_y = y;
	notifyObservers();
}

//
int NTImage::y() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _y;
}

//
void NTImage::setPosition(int x, int y)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_x = x;
	_y = y;
	notifyObservers();
}

//
unsigned int NTImage::width() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _width;
}

//
unsigned int NTImage::height() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _height;
}

//
void NTImage::setImage(const std::vector<std::string>& image)
{
	std::lock_guard<std::mutex> lock(_mutex);
    _image = image;
	notifyObservers();
}

//
const std::vector<std::string>& NTImage::image() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _image;
}

//
void NTImage::setColorPair(nt::ColorPair colorPair)
{
	std::lock_guard<std::mutex> lock(_mutex);
    _colorPair = colorPair;
	notifyObservers();
}

//
nt::ColorPair NTImage::colorPair() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _colorPair;
}

//
void NTImage::setWidth(unsigned int width)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_width = width;
	notifyObservers();
}

//
void NTImage::setTransparent(bool transparent)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_transparent = transparent;
	notifyObservers();
}

//
bool NTImage::isTransparent() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _transparent;
}

//
void NTImage::copyFrom(const NTImage& other)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_image = other._image;
	_width = other._width;
	_height = other._height;
	_transparent = other._transparent;
	_x = other._x;
	_y = other._y;
    _colorPair = other._colorPair;
	notifyObservers();
}

//
void NTImage::clearImage()
{
	std::lock_guard<std::mutex> lock(_mutex);
	_image.clear();
	_width = 0;
	_height = 0;
	_transparent = true;
	notifyObservers();
}
