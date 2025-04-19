#include <vector>
#include <string>
#include <mutex>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <ncurses.h>
#include <unistd.h>
#include <signal.h>

//#include "digits_8x8.h"
#include "ntdisplay.h"


NTerminalDisplay::NTerminalDisplay(NTObject* parent, const std::string& name)
	: NTObject(parent, name)  // Pass parameters directly, not using parent()
{
	// initialization code
	running = false;
	needs_redraw =false;
	term_width = 0;
	term_height = 0;
	bg_color = COLOR_BLACK;
	supports_rgb = false;

	// Инициализация ncurses и проверка поддержки RGB
	initNcurses();

	// Запуск потока обработки
	start();
}

//NTerminalDisplay::NTerminalDisplay() :
/*NTerminalDisplay::NTerminalDisplay()
	: NTObject(parent, name),
	running(false),
	needs_redraw(false), 
	term_width(0), 
	term_height(0), 
	bg_color(COLOR_BLACK), 
	supports_rgb(false) {
        
	// Инициализация ncurses и проверка поддержки RGB
	initNcurses();
	
	// Запуск потока обработки
	start();
}*/

NTerminalDisplay::~NTerminalDisplay() {
	stop();
}

/*
// Добавить изображение для отображения
void NTerminalDisplay::addImage(const std::vector<std::string>& image, 
											int x, int y, 
											ColorPair color, 
											ImageSize size) {
	std::lock_guard<std::mutex> lock(images_mutex);
	ImageInfo info;
	info.image = image;
	info.x = x;
	info.y = y;
	info.color = color;
	info.size = size;
	images.push_back(info);
	needs_redraw = true;
}
*/

// Добавить изображение для отображения
void NTerminalDisplay::addImage(const std::vector<std::string>& image,
								int x, int y,
								ColorPair color,
								ImageSize size) {
	std::lock_guard<std::mutex> lock(images_mutex);

	//NTImage img(this, "img", image, x, y, color, size);
	NTImage img(static_cast<NTObject*>(this), "img", image, x, y, color, size);

	images.push_back(img);
	needs_redraw = true;
}

/*
// Добавить изображение произвольного размера
void NTerminalDisplay::addImageArbitrarySize(const std::vector<std::string>& image, 
												int x, int y, ColorPair color) {
	std::lock_guard<std::mutex> lock(images_mutex);
	ImageInfo info;
	info.image = image;
	info.x = x;
	info.y = y;
	info.color = color;
	info.size = SIZE_16x16; // Placeholder, ignored in drawing
	images.push_back(info);
	needs_redraw = true;
}
*/

// Добавить изображение произвольного размера
void NTerminalDisplay::addImageArbitrarySize(const std::vector<std::string>& image,
												int x, int y, ColorPair color) {
	std::lock_guard<std::mutex> lock(images_mutex);

	//NTImage img(this, "img", image, x, y, color, SIZE_16x16);
	NTImage img(static_cast<NTObject*>(this), "img", image, x, y, color, SIZE_16x16);

	images.push_back(img);
	needs_redraw = true;
}

// Очистить все изображения
void NTerminalDisplay::clearImages() {
	std::lock_guard<std::mutex> lock(images_mutex);
	images.clear();
	needs_redraw = true;
}

// Установить пользовательские цвета (текст/фон) в стандартной палитре
void NTerminalDisplay::setCustomColor(short text_color, short bg_color) {
	std::lock_guard<std::mutex> lock(colors_mutex);
	init_pair(CUSTOM, text_color, bg_color);
}

// Установить RGB-цвет текста и фона (если поддерживается)
bool NTerminalDisplay::setRgbColor(short r_text, short g_text, short b_text,
                     short r_bg, short g_bg, short b_bg) {
	if (!supports_rgb) return false;
	
	std::lock_guard<std::mutex> lock(colors_mutex);
	
	// Создаем новый цвет в палитре
	init_color(100, r_text * 1000 / 255, g_text * 1000 / 255, b_text * 1000 / 255);
	init_color(101, r_bg * 1000 / 255, g_bg * 1000 / 255, b_bg * 1000 / 255);
	
	// Связываем цветовую пару
	init_pair(CUSTOM, 100, 101);
	
	return true;
}

// Залить весь терминал цветом фона (стандартные цвета)
void NTerminalDisplay::fillBackground(short bg_color) {
	std::lock_guard<std::mutex> lock(colors_mutex);
	this->bg_color = bg_color;
	bkgd(COLOR_PAIR(DEFAULT) | ' ');
	init_pair(DEFAULT, COLOR_WHITE, bg_color);
	needs_redraw = true;
}

// Залить весь терминал RGB-цветом фона (если поддерживается)
bool NTerminalDisplay::fillBackgroundRgb(short r, short g, short b) {
	if (!supports_rgb) return false;
	
	std::lock_guard<std::mutex> lock(colors_mutex);
	
	// Создаем новый цвет фона
	init_color(102, r * 1000 / 255, g * 1000 / 255, b * 1000 / 255);

	// Обновляем пару DEFAULT
	init_pair(DEFAULT, COLOR_WHITE, 102);
	bkgd(COLOR_PAIR(DEFAULT) | ' ');
	
	needs_redraw = true;
	return true;
}

// Проверить, поддерживается ли RGB
bool NTerminalDisplay::isRgbSupported() const {
	return supports_rgb;
}

//
void NTerminalDisplay::initNcurses() {
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
	init_pair(DEFAULT, COLOR_WHITE, bg_color);
	init_pair(RED_TEXT, COLOR_RED, bg_color);
	init_pair(GREEN_TEXT, COLOR_GREEN, bg_color);
	init_pair(BLUE_TEXT, COLOR_BLUE, bg_color);
	init_pair(YELLOW_TEXT, COLOR_YELLOW, bg_color);
	init_pair(CYAN_TEXT, COLOR_CYAN, bg_color);
	init_pair(MAGENTA_TEXT, COLOR_MAGENTA, bg_color);
	init_pair(WHITE_TEXT, COLOR_WHITE, bg_color);
	init_pair(CUSTOM, COLOR_WHITE, bg_color);
}

// Очистка ресурсов ncurses
void NTerminalDisplay::cleanupNcurses(){
	endwin();
}

//
void NTerminalDisplay::start() {
	running = true;
	worker_thread = std::thread(&NTerminalDisplay::worker, this);
}

//
void NTerminalDisplay::stop() {
	running = false;
	cv.notify_all();
	if (worker_thread.joinable()) {
		worker_thread.join();
	}
	endwin();
}

//
void NTerminalDisplay::worker() {
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
                needs_redraw = true;
            }

            // Отрисовка изображений
            if (needs_redraw) {
                drawImages();
                needs_redraw = false;
            }

            // Ожидание событий
            std::unique_lock<std::mutex> lock(images_mutex);
            cv.wait_for(lock, std::chrono::milliseconds(100));
        }

        endwin();
}

/*
//
void NTerminalDisplay::drawImages() {
        std::lock_guard<std::mutex> lock(images_mutex);
        
        clear();
        
        // Установка фона
        bkgd(COLOR_PAIR(DEFAULT) | ' ');
        
        for (const auto& img : images) {
            // Установка цвета
            attron(COLOR_PAIR(img.color));
            
            // Отрисовка изображения (теперь без ограничений по размеру)
            for (size_t y = 0; y < img.image.size() && (img.y + static_cast<int>(y)) < term_height; y++) {
                if (img.y + static_cast<int>(y) < 0) continue;
                
                const std::string& line = img.image[y];
                for (size_t x = 0; x < line.size() && (img.x + static_cast<int>(x)) < term_width; x++) {
                    if (img.x + static_cast<int>(x) < 0) continue;
                    
                    mvaddch(img.y + static_cast<int>(y), img.x + static_cast<int>(x), line[x]);
                }
            }
            
            // Сброс цвета
            attroff(COLOR_PAIR(img.color));
        }
        
        refresh();
}
*/

void NTerminalDisplay::drawImages() {
	for (const auto& img : images) {
		attron(COLOR_PAIR(img.color()));

		for (size_t y = 0; y < img.image().size() && (img.y() + static_cast<int>(y)) < term_height; y++) {
			if (img.y() + static_cast<int>(y) < 0) continue;

			const std::string& line = img.image()[y];
			for (size_t x = 0; x < line.size() && (img.x() + static_cast<int>(x)) < term_width; x++) {
				if (img.x() + static_cast<int>(x) < 0) continue;
				mvaddch(img.y() + static_cast<int>(y), img.x() + static_cast<int>(x), line[x]);
			}
		}

		attroff(COLOR_PAIR(img.color()));
	}

	refresh();
}

// Обработчик сигнала изменения размера терминала
void NTerminalDisplay::handleResize(int sig){
}
//};
