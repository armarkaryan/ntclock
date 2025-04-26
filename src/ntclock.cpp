#include <iostream>
#include "ntobject.h"
#include "digits_8x8.h"
#include "digits_16x16.h"
#include "ntdisplay.h"

#include <sys/ioctl.h>

//#include "ntlayoutmanager.h"

int _hour = 98;
int _min = 76;
int _sec = 54;
NTDisplay display;
//
void printTimeSym(const NTDisplay &display, NTImage &sym, const struct nt::Image &img, int pos)
{
	//
	int screenWidth = display.width();
	int screenHeight = display.height();

	int symWidth = img.width;
	int symHeight = img.height;

	int pos_x = (screenWidth - 8*symWidth)/2 + img.width*pos;
	int pos_y = (screenHeight - symHeight)/2;

	sym.setPosition(pos_x, pos_y);
	sym.setImage(img.img);
}

namespace {
	//
	//UClockWidget *cw_Clock = new UClockWidget();
	// Protect cw_Clock
	std::mutex clock_mutex;

	// Thread control flag
	std::atomic<bool> running{true};

	//
	void handle_winch(int sig) {
/*
		std::lock_guard<std::mutex> lock(clock_mutex);
		struct winsize w;
		ioctl(0, TIOCGWINSZ, &w);
		int true_height = w.ws_row;
		int true_width = w.ws_col;
		resizeterm(true_height, true_width);
		clear();
		refresh();
*/
/*
		init_pair(2, COLOR_RED, COLOR_BLACK);
		attron(COLOR_PAIR(2));
		mvprintw(x, 0, "Terminal resized to %dx%d", true_height, true_width);
		if(x<50)x++;else x=0;
		//cw_Clock.init();
		clear();
		refresh();
*/
	}

	//
	void timer_thread() {
		static std::mutex localtime_mutex;  // For std::gmtime

		while (running.load()) {
			const auto now = std::chrono::system_clock::now();
			const std::time_t now_time = std::chrono::system_clock::to_time_t(now);

			std::tm now_tm;

			//
			{
				std::lock_guard<std::mutex> lock(localtime_mutex);
				// Для конкретного часового пояса (например, +3 часа)
				const int timezone_offset = 3 * 3600; // 3 часа в секундах
				std::time_t adjusted_time = now_time + timezone_offset;
				now_tm = *std::gmtime(&adjusted_time);
			}

			//
			{
				std::lock_guard<std::mutex> lock(clock_mutex);
				_hour = now_tm.tm_hour;
				_min = now_tm.tm_min;
				_sec = now_tm.tm_sec;
			}

			//
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
		}
	}
} // namespace

int main(int argc, char* argv[]) {

	//NTDisplay display;

	// Создание и добавление изображений
	NTImage hh_hi(&display, "hh_hi", digits_8x8[0].img, 0, 0, nt::ColorPair::MAGENTA_TEXT);
	NTImage hh_lo(&display, "hh_lo", digits_8x8[1].img, 0, 0, nt::ColorPair::MAGENTA_TEXT);
	NTImage colon_h(&display, "colon_h", image_colon.img, 0, 0, nt::ColorPair::MAGENTA_TEXT);
	NTImage mm_hi(&display, "mm_hi", digits_8x8[2].img, 0, 0, nt::ColorPair::MAGENTA_TEXT);
	NTImage mm_lo(&display, "mm_lo", digits_8x8[3].img, 0, 0, nt::ColorPair::MAGENTA_TEXT);
	NTImage colon_m(&display, "colon_m", image_colon.img, 0, 0, nt::ColorPair::MAGENTA_TEXT);
	NTImage ss_hi(&display, "ss_hi", digits_8x8[4].img, 0, 0, nt::ColorPair::MAGENTA_TEXT);
	NTImage ss_lo(&display, "ss_lo", digits_8x8[5].img, 0, 0, nt::ColorPair::MAGENTA_TEXT);

	display.addImage(hh_hi);
	display.addImage(hh_lo);
	display.addImage(colon_h);
	display.addImage(mm_hi);
	display.addImage(mm_lo);
	display.addImage(colon_m);
	display.addImage(ss_hi);
	display.addImage(ss_lo);

	// Start timer thread
	std::thread worker;

	// Set signal handler (SIGWINCH)
	signal(SIGWINCH, handle_winch);

	try {
		worker = std::thread(timer_thread);
	} catch (const std::exception& e) {
		running = false;
		std::cerr << "Error creating thread: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	if (display.isRgbSupported()) {
		display.fillBackgroundRgb(30, 30, 100);
		display.setRgbColor(255, 165, 0, 30, 30, 100);

		// Wait for Space key to exit
		int ch;
		while ((ch = getch()) != ' ') {

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

			sleep(1);
		}
	} else {
		display.fillBackground(COLOR_BLUE);
		sleep(1);
	}

	// Stop thread and wait for finished
	running = false;
	if (worker.joinable()) {
		worker.join();
	}

	// Cleanup ncurses
	//clear();
	//refresh();
	//endwin();

	std::cout << "Program finished." << std::endl;

	return EXIT_SUCCESS;

}
