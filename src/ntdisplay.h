#ifndef NTDISPLAY_H
#define NTDISPLAY_H

#include <vector>
#include <string>
#include <mutex>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <ncurses.h>
#include <unistd.h>
#include <signal.h>

#include "digits_8x8.h"

class TerminalImageDisplay {
public:
    // Цветовые пары (текст/фон)
    enum ColorPair {
        DEFAULT = 1,    // Стандартная цветовая пара (обычно белый на черном)
        RED_TEXT,       // Красный текст
        GREEN_TEXT,     // Зеленый текст  
        BLUE_TEXT,      // Синий текст
        YELLOW_TEXT,    // Желтый текст
        CYAN_TEXT,      // Бирюзовый текст
        MAGENTA_TEXT,   // Пурпурный текст
        WHITE_TEXT,     // Белый текст
        CUSTOM          // Пользовательские цвета
    };

    // Поддерживаемые размеры изображений
    enum ImageSize {
        SIZE_4x4,      // 4 строки, 4 символа в ширину
        SIZE_8x4,       // 8 строк, 4 символа
        SIZE_4x8,       // 4 строки, 8 символов  
        SIZE_8x8,       // 8x8 символов (по умолчанию)
        SIZE_8x16,      // 8 строк, 16 символов
        SIZE_16x8,      // 16 строк, 8 символов
        SIZE_16x16      // 16x16 символов
    };

	// Конструктор/деструктор
	TerminalImageDisplay();  // Инициализирует библиотеку ncurses
	~TerminalImageDisplay(); // Освобождает ресурсы ncurses и останавливает поток

	// Добавить изображение для отображения
	void addImage(const std::vector<std::string>& image, 
					int x, int y,
					ColorPair color = DEFAULT,
					ImageSize size = SIZE_8x8);
					// image - вектор строк, где каждая строка представляет линию изображения
					// x, y - позиция верхнего левого угла
					// color - цветовая схема
					// size - стандартный размер изображения

	// Добавить изображение произвольного размера
	// Аналогично addImage, но без ограничений по размеру
	void addImageArbitrarySize(const std::vector<std::string>& image, 
									int x, int y,
									ColorPair color = DEFAULT);
									
	// Очистить все изображения
	// Удаляет все добавленные изображения
	void clearImages();

	// Установить пользовательские цвета (текст/фон) в стандартной палитре
	// text_color - цвет текста (номер цвета ncurses)
	// bg_color - цвет фона (номер цвета ncurses)
	void setCustomColor(short text_color, short bg_color);

	// Установить RGB-цвет текста и фона (если поддерживается)
	bool setRgbColor(short r_text, short g_text, short b_text,
						short r_bg, short g_bg, short b_bg);
						// Возвращает true если RGB цвета поддерживаются
						// r,g,b значения от 0 до 1000 (ncurses)

	// Залить весь терминал цветом фона (стандартные цвета)
	void fillBackground(short bg_color);  // Заливка стандартным цветом
	
	// Залить весь терминал RGB-цветом фона (если поддерживается)
	bool fillBackgroundRgb(short r, short g, short b);
						// Возвращает true если операция успешна
	
	// Проверить, поддерживается ли RGB
	bool isRgbSupported() const;  // Проверка поддержки RGB цветов
	
private:
	// Структура для хранения информации об изображении
	struct ImageInfo {
		std::vector<std::string> image;  // Само изображение
		int x;                          // Позиция X
		int y;                          // Позиция Y
		ColorPair color;                // Цветовая схема
		ImageSize size;                 // Размер изображения
	};

	std::vector<ImageInfo> images;      // Вектор всех изображений
	std::mutex images_mutex;           // Мьютекс для доступа к images
	std::mutex colors_mutex;           // Мьютекс для работы с цветами
	std::atomic<bool> running;         // Флаг работы потока отрисовки
	std::atomic<bool> needs_redraw;    // Флаг необходимости перерисовки
	std::atomic<int> term_width;       // Текущая ширина терминала
	std::atomic<int> term_height;      // Текущая высота терминала
	std::thread worker_thread;         // Поток отрисовки
	std::condition_variable cv;        // Условная переменная для синхронизации
	short bg_color;                    // Текущий цвет фона
	bool supports_rgb;                 // Флаг поддержки RGB
	
	// Инициализация библиотеки ncurses
	void initNcurses();
	
	// Очистка ресурсов ncurses
	void cleanupNcurses();
	
	// Запуск потока отрисовки
	void start();
	
	// Остановка потока отрисовки
	void stop();
	
	// Основной цикл потока отрисовки
	void worker();
	
	// Отрисовка всех изображений
	void drawImages();

	// Обработчик сигнала изменения размера терминала
	static void handleResize(int sig);
};

#endif // NTDISPLAY_H