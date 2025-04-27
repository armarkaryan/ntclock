#include <iostream>
#include <sys/ioctl.h>
#include <mutex>
#include <chrono>
#include <ctime>
#include <thread>

#include "ntobject.h"
#include "digits_8x8.h"
#include "digits_16x16.h"
#include "ntdisplay.h"

int _hour = 0;
int _min = 0;
int _sec = 0;
std::mutex localtime_mutex;  // Мьютекс для синхронизации доступа к времени

void printTimeSym(const NTDisplay &display, NTImage &sym, const struct nt::Image &img, int pos)
{
	int screenWidth = display.width();
	int screenHeight = display.height();

	int symWidth = img.width;
	int symHeight = img.height;

	int pos_x = (screenWidth - 8*symWidth)/2 + img.width*pos;
	int pos_y = (screenHeight - symHeight)/2;

	sym.setPosition(pos_x, pos_y);
	sym.setImage(img.img);
	sym.setColorPair(nt::RED_TEXT);
}

int main(int argc, char* argv[])
{
	NTDisplay display;

	if(!display.isRgbSupported()) {
		display.fillBackground(COLOR_BLUE);
		std::cerr << "RGB Not supported." << std::endl;
		sleep(3);
		return EXIT_FAILURE;
	}

	// Создание и добавление изображений
	NTImage hh_hi(&display, "hh_hi", digits_8x8[0].img, 0, 0, nt::ColorPair::CUSTOM);
	NTImage hh_lo(&display, "hh_lo", digits_8x8[1].img, 0, 0, nt::ColorPair::CUSTOM);
	NTImage colon_h(&display, "colon_h", image_colon.img, 0, 0, nt::ColorPair::WHITE_TEXT);
	NTImage mm_hi(&display, "mm_hi", digits_8x8[2].img, 0, 0, nt::ColorPair::WHITE_TEXT);
	NTImage mm_lo(&display, "mm_lo", digits_8x8[3].img, 0, 0, nt::ColorPair::WHITE_TEXT);
	NTImage colon_m(&display, "colon_m", image_colon.img, 0, 0, nt::ColorPair::WHITE_TEXT);
	NTImage ss_hi(&display, "ss_hi", digits_8x8[4].img, 0, 0, nt::ColorPair::WHITE_TEXT);
	NTImage ss_lo(&display, "ss_lo", digits_8x8[5].img, 0, 0, nt::ColorPair::WHITE_TEXT);

	display.addImage(hh_hi);
	display.addImage(hh_lo);
	display.addImage(colon_h);
	display.addImage(mm_hi);
	display.addImage(mm_lo);
	display.addImage(colon_m);
	display.addImage(ss_hi);
	display.addImage(ss_lo);

	display.fillBackgroundRgb(50, 50, 100);
	display.setRgbColor(255, 255, 0, 50, 50, 100);

	int ch;
	while ((ch = getch()) != ' ') {
		const auto now = std::chrono::system_clock::now();
		const std::time_t now_time = std::chrono::system_clock::to_time_t(now);
		std::tm now_tm;

		{
			std::lock_guard<std::mutex> lock(localtime_mutex);
			// Используем локальное время вместо GMT с фиксированным смещением
			now_tm = *std::localtime(&now_time);
		}

		_hour = now_tm.tm_hour;
		_min = now_tm.tm_min;
		_sec = now_tm.tm_sec;

		// Print hours
		printTimeSym(display, hh_hi, digits_8x8[(_hour/10)], 0);
		printTimeSym(display, hh_lo, digits_8x8[(_hour%10)], 1);

		// Print ":"
		printTimeSym(display, colon_h, image_colon, 2);

		// Print minutes
		printTimeSym(display, mm_hi, digits_8x8[_min/10], 3);
		printTimeSym(display, mm_lo, digits_8x8[_min%10], 4);

		// Print ":"
		printTimeSym(display, colon_m, image_colon, 5);

		// Print seconds
		printTimeSym(display, ss_hi, digits_8x8[_sec/10], 6);
		printTimeSym(display, ss_lo, digits_8x8[_sec%10], 7);

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::cout << "Program finished." << std::endl;
	return EXIT_SUCCESS;
}
