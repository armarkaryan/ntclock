#include <vector>
#include <string>
#include <mutex>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <ncurses.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>

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
	_images.clear(); // Check f needed
	endwin();
}

//
void NTDisplay::worker() {
	//
	while (running) {
/*
		// Проверка изменения размера терминала
		//std::unique_lock<std::mutex> lock(term_mutex);
		//std::unique_lock<std::mutex> lock(images_mutex);
		struct winsize w;
		ioctl(0, TIOCGWINSZ, &w);
		int new_height = w.ws_row;
		int new_width = w.ws_col;
		resizeterm(new_height, new_width);
*/

		// Проверка изменения размера терминала
		// Синхронизация доступа к терминалу
		int new_height;
		int new_width;
		struct winsize w;

		{
			//std::unique_lock<std::mutex> term_lock(term_mutex);
			std::lock_guard<std::mutex> lock(term_mutex);
			if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == -1) {
				perror("ioctl failed");
				return;
			}
			new_height = w.ws_row;
			new_width = w.ws_col;
		}

		resizeterm(new_height, new_width);
		refresh(); // Обязательно обновить экран после изменения размера

		if (new_width != term_width || new_height != term_height)
		{
			term_width = new_width;
			term_height = new_height;
			clear();
			refresh();
			_needsRedraw = true;

			// Уведомляем наблюдателей
			{
				std::lock_guard<std::mutex> lock(_observersMutex);
				for (auto& [id, observer] : _resizeObservers) {
					observer();  // Вызываем только функцию, игнорируя id
				}
			}

			//
			{
				//std::unique_lock<std::mutex> lock(images_mutex);
				std::lock_guard<std::mutex> lock(colors_mutex);
				init_pair(5, COLOR_RED, COLOR_BLACK);
				attron(COLOR_PAIR(5));
				mvprintw(0, 0, "Terminal size: %dx%d", height(), width());
				attroff(COLOR_PAIR(5));
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
//std::unique_lock<std::mutex> lock(images_mutex);
	for (const auto& img : _images) {

		//attron(COLOR_PAIR(9));
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
		//attroff(COLOR_PAIR(9));
	}

	refresh();
}
