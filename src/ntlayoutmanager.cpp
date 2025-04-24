#include "ntlayoutmanager.h"
#include <algorithm>
#include <math.h>
#include <climits>
/*
NTLayoutManager::NTLayoutManager(NTObject* parent, const std::string& name)
	: NTObject(parent, name),
	  _layoutType(LayoutType::HORIZONTAL),
	  _spacing(1) {
	_margins = {0, 0, 0, 0};
}
*/
//--
/*
NTLayoutManager::NTLayoutManager(NTObject* parent, const std::string& name)
	: NTObject(parent, name),
	  _layoutType(LayoutType::HORIZONTAL),
	  _spacing(1),
	  _container(nullptr) {
	_margins = {0, 0, 0, 0};


	// Создаем обработчик изменений размера
	_resizeHandler = [this]() {
		if (_container) {
			this->updateLayout();
			//this->centerInContainer();
			this->centerInContainer(_container->width(), _container->height());
		}
	};
}
*/
NTLayoutManager::NTLayoutManager(NTObject* parent, const std::string& name)
	: NTObject(parent, name),
	  _layoutType(LayoutType::HORIZONTAL),
	  _spacing(1),
	  _container(nullptr) {
	_margins = {0, 0, 0, 0};
}
//--
//--
/*
void NTLayoutManager::setContainer(NTDisplay* display) {
	if (_container) {
		// Отписываемся от старого контейнера
		_container->removeResizeObserver(_resizeHandler);
	}

	_container = display;

	if (_container) {
		// Подписываемся на изменения размера
		_container->addResizeObserver(_resizeHandler);
		// Первоначальное обновление
		updateLayout();
	}
}
*/
void NTLayoutManager::setContainer(NTDisplay* display) {
	if (_container) {
		// Отписываемся от старого контейнера
		_container->removeResizeObserver(_resizeObserverId);
	}

	_container = display;

	if (_container) {
		// Подписываемся на изменения размера
		_resizeObserverId = _container->addResizeObserver([this]() {
			if (_container) {
				this->updateLayout();
				this->centerInContainer();
				//this->centerInContainer(_container->width(), _container->height());
			}
		});
		// Первоначальное обновление
		updateLayout();
	}
}
//--
//--
void NTLayoutManager::updateLayout() {
	if (!_container) return;

	std::lock_guard<std::mutex> lock(_imagesMutex);

	switch (_layoutType) {
		case LayoutType::HORIZONTAL:
			updateHorizontalLayout(_container->width(), _container->height());
			break;
		case LayoutType::VERTICAL:
			updateVerticalLayout(_container->width(), _container->height());
			break;
		case LayoutType::GRID:
			updateGridLayout(_container->width(), _container->height());
			break;
		case LayoutType::ABSOLUTE:
			// No automatic positioning for absolute layout
			break;
	}
}
//--

NTLayoutManager::~NTLayoutManager() {
	clearImages();
}

void NTLayoutManager::addImage(NTImage* image) {
	std::lock_guard<std::mutex> lock(_imagesMutex);
	_images.push_back(image);
}

void NTLayoutManager::removeImage(NTImage* image) {
	std::lock_guard<std::mutex> lock(_imagesMutex);
	_images.erase(std::remove(_images.begin(), _images.end(), image), _images.end());
}

void NTLayoutManager::clearImages() {
	std::lock_guard<std::mutex> lock(_imagesMutex);
	_images.clear();
}

void NTLayoutManager::setLayoutType(LayoutType type) {
	_layoutType = type;
}

void NTLayoutManager::setSpacing(int spacing) {
	_spacing = spacing;
}

void NTLayoutManager::setMargins(int top, int right, int bottom, int left) {
	_margins = {top, right, bottom, left};
}

void NTLayoutManager::updateLayout(int containerWidth, int containerHeight) {
	std::lock_guard<std::mutex> lock(_imagesMutex);

	switch (_layoutType) {
		case LayoutType::HORIZONTAL:
			updateHorizontalLayout(containerWidth, containerHeight);
			break;
		case LayoutType::VERTICAL:
			updateVerticalLayout(containerWidth, containerHeight);
			break;
		case LayoutType::GRID:
			updateGridLayout(containerWidth, containerHeight);
			break;
		case LayoutType::ABSOLUTE:
			// No automatic positioning for absolute layout
			break;
	}
}
/*
void NTLayoutManager::centerInContainer(int containerWidth, int containerHeight) {
	std::lock_guard<std::mutex> lock(_imagesMutex);
	if (_images.empty()) return;

	// Find bounding box of all images
	int minX = INT_MAX, maxX = INT_MIN;
	int minY = INT_MAX, maxY = INT_MIN;

	for (const auto& img : _images) {
		minX = std::min(minX, img->x());
		maxX = std::max(maxX, img->x() + static_cast<int>(img->width()));
		minY = std::min(minY, img->y());
		maxY = std::max(maxY, img->y() + static_cast<int>(img->height()));
	}

	int totalWidth = maxX - minX;
	int totalHeight = maxY - minY;

	int offsetX = (containerWidth - totalWidth) / 2 - minX;
	int offsetY = (containerHeight - totalHeight) / 2 - minY;

	for (auto& img : _images) {
		img->setx(img->x() + offsetX);
		img->sety(img->y() + offsetY);
	}
}
*/
//--
void NTLayoutManager::centerInContainer() {
//void NTLayoutManager::centerInContainer(int containerWidth, int containerHeight) {
	if (!_container || _images.empty()) return;

	std::lock_guard<std::mutex> lock(_imagesMutex);

	// ... существующая реализация centerInContainer,
	// но с использованием _container->width() и _container->height() ...
	// Find bounding box of all images
	int minX = INT_MAX, maxX = INT_MIN;
	int minY = INT_MAX, maxY = INT_MIN;

	for (const auto& img : _images) {
		minX = std::min(minX, img->x());
		maxX = std::max(maxX, img->x() + static_cast<int>(img->width()));
		minY = std::min(minY, img->y());
		maxY = std::max(maxY, img->y() + static_cast<int>(img->height()));
	}

	int totalWidth = maxX - minX;
	int totalHeight = maxY - minY;

	//int offsetX = (containerWidth - totalWidth) / 2 - minX;
	int offsetX = (_container->width() - totalWidth) / 2 - minX;
	//int offsetY = (containerHeight - totalHeight) / 2 - minY;
	int offsetY = (_container->height() - totalHeight) / 2 - minY;

	for (auto& img : _images) {
		img->setx(img->x() + offsetX);
		img->sety(img->y() + offsetY);
	}
}
//--

void NTLayoutManager::updateHorizontalLayout(int containerWidth, int containerHeight) {
	int currentX = _margins.left;
	int currentY = _margins.top;

	for (auto& img : _images) {
		img->setx(currentX);
		img->sety(currentY);
		currentX += static_cast<int>(img->width()) + _spacing;
	}
}

void NTLayoutManager::updateVerticalLayout(int containerWidth, int containerHeight) {
	int currentX = _margins.left;
	int currentY = _margins.top;

	for (auto& img : _images) {
		img->setx(currentX);
		img->sety(currentY);
		currentY += static_cast<int>(img->height()) + _spacing;
	}
}

void NTLayoutManager::updateGridLayout(int containerWidth, int containerHeight) {
	// Simple grid layout - could be enhanced
	int cols = static_cast<int>(std::sqrt(_images.size()));
	if (cols == 0) cols = 1;

	int currentX = _margins.left;
	int currentY = _margins.top;
	int maxRowHeight = 0;
	int itemsInRow = 0;

	for (auto& img : _images) {
		img->setx(currentX);
		img->sety(currentY);

		currentX += static_cast<int>(img->width()) + _spacing;
		maxRowHeight = std::max(maxRowHeight, static_cast<int>(img->height()));
		itemsInRow++;

		if (itemsInRow >= cols) {
			itemsInRow = 0;
			currentX = _margins.left;
			currentY += maxRowHeight + _spacing;
			maxRowHeight = 0;
		}
	}
}
