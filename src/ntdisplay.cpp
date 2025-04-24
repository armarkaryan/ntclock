#include <vector>
#include <string>
#include <mutex>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <ncurses.h>
#include <unistd.h>
#include <signal.h>

#include "ntdisplay.h"

//
NTDisplay::NTDisplay(NTObject* parent, const std::string& name)
	: NTObject(parent, name)  // Pass parameters directly, not using parent()
{
	// initialization code
	running = false;
	_needsRedraw =false;
	term_width = 0;
	term_height = 0;
	bg_color = COLOR_BLACK;
	supports_rgb = false;

	// Инициализация ncurses и проверка поддержки RGB
	initNcurses();

	// Запуск потока обработки
	start();
}

//
NTDisplay::~NTDisplay() {
	stop();
}

// Добавить изображение для отображения
void NTDisplay::addImage(const NTImage &img)
{
	std::lock_guard<std::mutex> lock(images_mutex);
	_images.push_back(&img);
	img.addObserver([this]() { _needsRedraw = true; });
	_needsRedraw = true;

}
/*
void addChild(const NTImage &img) {
		images.push_back(&img);
		// Подписываемся на изменения ребёнка
		img.addObserver([this]() { _needsRedraw = true; });
	}
*/

// Очистить все изображения
void NTDisplay::clearImages()
{
	std::lock_guard<std::mutex> lock(images_mutex);
	_images.clear();
	_needsRedraw = true;
}

// Установить пользовательские цвета (текст/фон) в стандартной палитре
void NTDisplay::setCustomColor(short text_color, short bg_color) {
	std::lock_guard<std::mutex> lock(colors_mutex);
	init_pair(nt::CUSTOM, text_color, bg_color);
}

// Установить RGB-цвет текста и фона (если поддерживается)
bool NTDisplay::setRgbColor(short r_text, short g_text, short b_text,
                     short r_bg, short g_bg, short b_bg) {
	if (!supports_rgb) return false;
	
	std::lock_guard<std::mutex> lock(colors_mutex);
	// Создаем новый цвет в палитре
	init_color(100, r_text * 1000 / 255, g_text * 1000 / 255, b_text * 1000 / 255);
	init_color(101, r_bg * 1000 / 255, g_bg * 1000 / 255, b_bg * 1000 / 255);
	// Связываем цветовую пару
	init_pair(nt::CUSTOM, 100, 101);
	
	return true;
}

// Залить весь терминал цветом фона (стандартные цвета)
void NTDisplay::fillBackground(short bg_color) {
	std::lock_guard<std::mutex> lock(colors_mutex);
	this->bg_color = bg_color;
	bkgd(COLOR_PAIR(nt::DEFAULT) | ' ');
	init_pair(nt::DEFAULT, COLOR_WHITE, bg_color);
	_needsRedraw = true;
}

// Залить весь терминал RGB-цветом фона (если поддерживается)
bool NTDisplay::fillBackgroundRgb(short r, short g, short b) {
	if (!supports_rgb) return false;
	
	std::lock_guard<std::mutex> lock(colors_mutex);
	// Создаем новый цвет фона
	init_color(102, r * 1000 / 255, g * 1000 / 255, b * 1000 / 255);
	// Обновляем пару DEFAULT
	init_pair(nt::DEFAULT, COLOR_WHITE, 102);
	bkgd(COLOR_PAIR(nt::DEFAULT) | ' ');
	
	_needsRedraw = true;
	return true;
}

// Проверить, поддерживается ли RGB
bool NTDisplay::isRgbSupported() const {
	return supports_rgb;
}

//
void NTDisplay::initNcurses() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	timeout(0);
	
	// Проверка поддержки цветов
	if (!has_colors()) {
		endwin();
		fprintf(stderr, "Терминал не поддерживает цвета\n");
		return;
	}

	start_color();
	use_default_colors();

	// Проверка поддержки RGB (256 или truecolor)
	supports_rgb = (can_change_color() && COLORS >= 256);
	
	// Инициализация стандартных цветов
	init_pair(nt::DEFAULT, COLOR_WHITE, bg_color);
	init_pair(nt::RED_TEXT, COLOR_RED, bg_color);
	init_pair(nt::GREEN_TEXT, COLOR_GREEN, bg_color);
	init_pair(nt::BLUE_TEXT, COLOR_BLUE, bg_color);
	init_pair(nt::YELLOW_TEXT, COLOR_YELLOW, bg_color);
	init_pair(nt::CYAN_TEXT, COLOR_CYAN, bg_color);
	init_pair(nt::MAGENTA_TEXT, COLOR_MAGENTA, bg_color);
	init_pair(nt::WHITE_TEXT, COLOR_WHITE, bg_color);
	init_pair(nt::CUSTOM, COLOR_WHITE, bg_color);
}

// Очистка ресурсов ncurses
void NTDisplay::cleanupNcurses(){
	endwin();
}

//
void NTDisplay::start() {
	running = true;
    worker_thread = std::thread(&NTDisplay::worker, this);
}

//
void NTDisplay::stop() {
	running = false;
	cv.notify_all();
	if (worker_thread.joinable()) {
		worker_thread.join();
	}
	endwin();
}
/*
//
void NTDisplay::worker() {
int new_width = 0, new_height = 0;

        signal(SIGWINCH, [](int) {});

        getmaxyx(stdscr, term_height, term_width);

// В методе worker(), при обнаружении изменения размера:
if (new_width != term_width || new_height != term_height) {
	term_width = new_width;
	term_height = new_height;
	clear();
	refresh();
	_needsRedraw = true;

	// Уведомляем наблюдателей
	std::lock_guard<std::mutex> lock(_observersMutex);
	for (auto& observer : _resizeObservers) {
		observer();
	}
}

        while (running) {
            // Проверка изменения размера терминала
            int new_width, new_height;
            getmaxyx(stdscr, new_height, new_width);
            
            if (new_width != term_width || new_height != term_height) {
                term_width = new_width;
                term_height = new_height;
                clear();
                refresh();
				_needsRedraw = true;
            }

            // Отрисовка изображений
			if (_needsRedraw) {
                drawImages();
				_needsRedraw = false;
            }

            // Ожидание событий
            std::unique_lock<std::mutex> lock(images_mutex);
            cv.wait_for(lock, std::chrono::milliseconds(100));
        }

        endwin();
}
*/
void NTDisplay::worker() {
	signal(SIGWINCH, [](int) {});

	getmaxyx(stdscr, term_height, term_width);

	while (running) {
		// Проверка изменения размера терминала
		int new_width, new_height;
		getmaxyx(stdscr, new_height, new_width);

		if (new_width != term_width || new_height != term_height) {
			term_width = new_width;
			term_height = new_height;
			clear();
			refresh();
			_needsRedraw = true;

			// Уведомляем наблюдателей
			std::lock_guard<std::mutex> lock(_observersMutex);
			for (auto& [id, observer] : _resizeObservers) {
				observer();  // Вызываем только функцию, игнорируя id
			}
		}

		// Остальной код...
		// Отрисовка изображений
			if (_needsRedraw) {
				drawImages();
				_needsRedraw = false;
			}

			// Ожидание событий
			std::unique_lock<std::mutex> lock(images_mutex);
			cv.wait_for(lock, std::chrono::milliseconds(100));
	}
	endwin();
}

void NTDisplay::drawImages() {
	for (const auto& img : _images) {
		attron(COLOR_PAIR(img->colorPair()));

		for (size_t y = 0; y < img->image().size() && (img->y() + static_cast<int>(y)) < term_height; y++) {
			if (img->y() + static_cast<int>(y) < 0) continue;

			const std::string& line = img->image()[y];
			for (size_t x = 0; x < line.size() && (img->x() + static_cast<int>(x)) < term_width; x++) {
				if (img->x() + static_cast<int>(x) < 0) continue;
				mvaddch(img->y() + static_cast<int>(y), img->x() + static_cast<int>(x), line[x]);
			}
		}

		attroff(COLOR_PAIR(img->colorPair()));
	}

	refresh();
}

// Обработчик сигнала изменения размера терминала
void NTDisplay::handleResize(int sig){
}

//--
/*void NTDisplay::addResizeObserver(std::function<void()> observer) {
	std::lock_guard<std::mutex> lock(_observersMutex);
	_resizeObservers.push_back(observer);
}*/
size_t NTDisplay::addResizeObserver(std::function<void()> observer) {
	std::lock_guard<std::mutex> lock(_observersMutex);
	size_t id = _nextObserverId++;
	_resizeObservers.emplace_back(id, std::move(observer));
	return id;
}
/*void NTDisplay::removeResizeObserver(std::function<void()> observer) {
	std::lock_guard<std::mutex> lock(_observersMutex);
	_resizeObservers.erase(
		std::remove(_resizeObservers.begin(), _resizeObservers.end(), observer),
		_resizeObservers.end()
	);
}*/
void NTDisplay::removeResizeObserver(size_t id) {
	std::lock_guard<std::mutex> lock(_observersMutex);
	_resizeObservers.erase(
		std::remove_if(_resizeObservers.begin(), _resizeObservers.end(),
			[id](const auto& pair) { return pair.first == id; }),
		_resizeObservers.end()
	);
}
//--
