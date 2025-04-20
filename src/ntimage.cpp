// NTImage.cpp

#include "ntimage.h"

// Простой конструктор
NTImage::NTImage(NTObject* parent, const std::string& name)
    : NTObject(parent, name), _width(8), _height(8), _channels(0),
      _x(0), _y(0), _color(DEFAULT), _size(SIZE_8x8)
{
    // To do... image, width, height, chanals
}

// Полный конструктор
NTImage::NTImage(NTObject* parent, const std::string& name,
               const std::vector<std::string>& image,
               int x, int y, ColorPair color, ImageSize size)
    : NTObject(parent, name), _image(image), _x(x), _y(y), _color(color), _size(size)
{
    // To do... image, width, height, chanals
}

// Конструктор копирования
NTImage::NTImage(const NTImage& other)
    : NTObject(other.parent(), other.name()),
      _image(other._image),
      _x(other._x),
      _y(other._y),
      _color(other._color),
      _size(other._size)
{
    // To do... width, height, chanals
}

// Деструктор
NTImage::~NTImage() = default;

/*
NTImage::NTImage(NTObject *parent,
				 const std::string &name,
				 const std::vector<std::string>& image,
				 int x,
				 int y,
				 ColorPair color,
				 ImageSize size)
	: NTObject(parent, name),
	  _imageLines(image),
	  _x(x),
	  _y(y),
	  _color(color),
	  _size(size)
{
	updateImageFromLines();
}
*/

/*
NTImage::NTImage(const NTImage& other)
{
	copyFrom(other);
}
*/

/*
NTImage::~NTImage()
{
	clearImage();
}
*/

/*
// Конструктор копирования
NTImage::NTImage(const NTImage& other)
    : NTObject(other.parent(), other.name()),
      _image(other._image),
      _x(other._x),
      _y(other._y),
      _color(other._color),
      _size(other._size) {}

      */

/*
NTImage& NTImage::operator=(const NTImage& other)
{
	if (this != &other) {
		clearImage();
		copyFrom(other);
	}
	return *this;
}
*/

// Оператор присваивания
NTImage& NTImage::operator=(const NTImage& other) {
	if (this != &other) {
		NTObject::operator=(other);
		_image = other._image;
		_x = other._x;
		_y = other._y;
		_color = other._color;
		_size = other._size;
	}
	return *this;
}

unsigned int NTImage::width() const
{
	return _width;
}

unsigned int NTImage::height() const
{
	return _height;
}

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
const std::vector<std::string>& NTImage::getImageLines() const
{
	return _imageLines;
}

//
void NTImage::resize(unsigned int newWidth, unsigned int newHeight)
{
	// Простейшая реализация ресайза - просто изменить размеры
	// В реальной реализации нужно было бы делать интерполяцию пикселей
	_width = newWidth;
	_height = newHeight;

	// Обновляем данные изображения
	updateImageFromLines();
}

void NTImage::setColorPair(NTObject::ColorPair pair)
{
	_color = pair;
}

void NTImage::setImageSize(NTObject::ImageSize size)
{
	_size = size;
}

void NTImage::copyFrom(const NTImage& other)
{
	_image = other._image;
	_imageLines = other._imageLines;
	_width = other._width;
	_height = other._height;
	_channels = other._channels;
	_x = other._x;
	_y = other._y;
	_color = other._color;
	_size = other._size;
}

void NTImage::clearImage()
{
	_image.clear();
	_imageLines.clear();
	_width = 0;
	_height = 0;
	_channels = 0;
}

/*
void NTImage::updateImageFromLines()
{
	if (_imageLines.empty()) {
		clearImage();
		return;
	}

	_height = _imageLines.size();
	_width = 0;

	// Находим максимальную ширину
	for (const auto& line : _imageLines) {
		if (line.length() > _width) {
			_width = line.length();
		}
	}

	// Предполагаем 3 канала (RGB)
	_channels = 3;
	_image.resize(_width * _height * _channels, 0);

	// Заполняем данные изображения
	// (здесь упрощенная реализация - в реальности нужно учитывать цветовые пары)
	for (size_t y = 0; y < _height; ++y) {
		const std::string& line = _imageLines[y];
		for (size_t x = 0; x < line.length(); ++x) {
			size_t index = (y * _width + x) * _channels;
			char c = line[x];
			// Простое заполнение - все символы как белые
			_image[index] = 255;     // R
			_image[index+1] = 255;  // G
			_image[index+2] = 255;   // B
		}
	}
}
*/
void NTImage::updateImageFromLines() {
	// Реализуйте логику для работы со строками
}

/*
void NTImage::updateLinesFromImage()
{
	_imageLines.clear();
	if (_imageempty()) return;

	for (size_t y = 0; y < _height; ++y) {
		std::string line;
		for (size_t x = 0; x < _width; ++x) {
			size_t index = (y * _width + x) * _channels;
			// Простое преобразование - если пиксель не черный, ставим символ
			if (_image[index] > 0 || _image[index+1] > 0 || _image[index+2] > 0) {
				line += '#';
			} else {
				line += ' ';
			}
		}
		_imageLines.push_back(line);
	}
}
*/
void NTImage::updateLinesFromImage() {
	// Упрощенная реализация
	if (_image.empty()) return;

	for (auto& line : _image) {
		for (size_t x = 0; x < line.size(); x++) {
			if (line[x] != ' ') {  // Просто проверяем, не пробел ли
				// Какая-то логика обработки
			}
		}
	}
}
