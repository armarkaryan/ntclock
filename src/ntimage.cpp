// NTImage.cpp

#include <fstream>
#include <stdexcept>
#include <algorithm>

#include "ntimage.h"

// Простой конструктор
NTImage::NTImage(NTObject* parent, const std::string& name)
	: NTObject(parent, name), _x(0), _y(0), _color(DEFAULT), _size(SIZE_8x8) {}
/*
NTImage::NTImage(NTObject *parent, const std::string &name)
	: NTObject(parent, name),
	  _width(0),
	  _height(0),
	  _channels(0),
	  _x(0),
	  _y(0),
	  _color(DEFAULT),
	  _size(SIZE_8x8)
{
}*/

NTImage::NTImage(NTObject* parent, const std::string& name,
			   const std::vector<std::string>& image,
			   int x, int y, ColorPair color, ImageSize size)
	: NTObject(parent, name), _image(image), _x(x), _y(y), _color(color), _size(size) {}

NTImage::~NTImage() = default;

/*
// Полный конструктор
NTImage::NTImage(NTObject* parent, const std::string& name,
			   const std::vector<std::string>& image,
			   int x, int y, ColorPair color, ImageSize size)
	: NTObject(parent, name), _image(image), _x(x), _y(y), _color(color), _size(size) {updateImageFromLines();}
	*/
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
// Деструктор
NTImage::~NTImage() = default;
*/

NTImage::NTImage(const NTImage& other)
	: NTObject(other.parent(), other.name()),
	  _image(other._image),
	  _x(other._x),
	  _y(other._y),
	  _color(other._color),
	  _size(other._size) {
}


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

bool NTImage::loadFromFile(const std::string &filename)
{
	std::ifstream file(filename);
	if (!file.is_open()) {
		return false;
	}

	_imageLines.clear();
	std::string line;
	while (std::getline(file, line)) {
		_imageLines.push_back(line);
	}

	updateImageFromLines();
	return true;
}

bool NTImage::saveToFile(const std::string &filename) const
{
	std::ofstream file(filename);
	if (!file.is_open()) {
		return false;
	}

	for (const auto& line : _imageLines) {
		file << line << '\n';
	}

	return true;
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

/*const std::vector<unsigned char>& NTImage::imageData() const
{
	return _imageData;
}*/

const std::vector<std::string>& NTImage::image() const
{
	return _image;
}

const std::vector<std::string>& NTImage::getImageLines() const
{
	return _imageLines;
}
/*
void NTImage::convertToGrayscale()
{
	if (_channels < 3) return;

	for (size_t i = 0; i < _image.size(); i += _channels) {
		unsigned char gray = static_cast<unsigned char>(
			0.299 * _image[i] +
			0.587 * _image[i+1] +
			0.114 * _image[i+2]);

		_image[i] = gray;
		_image[i+1] = gray;
		_image[i+2] = gray;
	}
}
*/

void NTImage::convertToGrayscale() {
	// Удалите эту реализацию или перепишите для работы со строками
	// Текущая реализация не имеет смысла для vector<string>
}

void NTImage::resize(unsigned int newWidth, unsigned int newHeight)
{
	// Простейшая реализация ресайза - просто изменить размеры
	// В реальной реализации нужно было бы делать интерполяцию пикселей
	_width = newWidth;
	_height = newHeight;

	// Обновляем данные изображения
	updateImageFromLines();
}

void NTImage::setColorPair(ColorPair pair)
{
	_color = pair;
}

void NTImage::setImageSize(ImageSize size)
{
	_size = size;
}

void NTImage::setPosition(int x, int y)
{
	_x = x;
	_y = y;
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
