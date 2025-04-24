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

#include "nttypes.h"
#include "image_custom.h"
#include "digits_8x8.h"
#include "digits_16x16.h"
#include "ntimage.h"

class NTDisplay : public NTObject {
public:
	// Конструктор/деструктор
    NTDisplay(NTObject* parent = nullptr, const std::string& name ="");
    ~NTDisplay(); // Освобождает ресурсы ncurses и останавливает поток

	//
	unsigned int width(){ return term_width; };

	//
	unsigned int height(){ return term_height; };

	// Добавить изображение для отображения
	void addImage(const NTImage &img);

	// Очистить все изображения
	// Удаляет все добавленные изображения
	void clearImages();

	// Установить пользовательские цвета (текст/фон) в стандартной палитре
	// text_color - цвет текста (номер цвета ncurses)
	// bg_color - цвет фона (номер цвета ncurses)
	void setCustomColor(short text_color, short bg_color);

	// Установить RGB-цвет текста и фона (если поддерживается)
	// Возвращает true если RGB цвета поддерживаются
						// r,g,b значения от 0 до 1000 (ncurses)
	bool setRgbColor(short r_text, short g_text, short b_text,
						short r_bg, short g_bg, short b_bg);

	// Залить весь терминал цветом фона (стандартные цвета)
	void fillBackground(short bg_color);  // Заливка стандартным цветом

	// Залить весь терминал RGB-цветом фона (если поддерживается)
	bool fillBackgroundRgb(short r, short g, short b);
						// Возвращает true если операция успешна

	// Проверить, поддерживается ли RGB
	bool isRgbSupported() const;  // Проверка поддержки RGB цветов

private:
	std::vector<const NTImage*> _images;

	std::mutex images_mutex;           // Мьютекс для доступа к images
	std::mutex colors_mutex;           // Мьютекс для работы с цветами
	std::atomic<bool> running;         // Флаг работы потока отрисовки
	std::atomic<bool> _needsRedraw;    // Флаг необходимости перерисовки
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

