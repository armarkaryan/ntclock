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
#include "ntdisplay.h"

int main() {

	NTerminalDisplay display;

    if (display.isRgbSupported()) {
        // Заливаем терминал градиентным синим фоном
        display.fillBackgroundRgb(30, 30, 100);

        // Устанавливаем оранжевый текст (RGB) и прозрачный фон
        display.setRgbColor(255, 165, 0,   // Оранжевый (R=255, G=165, B=0)
                            0, 0, 0);       // Чёрный фон (но он прозрачен из-за bkgd)

        display.addImage(digit_0, 10, 5, NTerminalDisplay::CUSTOM);
display.addImageArbitrarySize(custom_image, 5, 5, NTerminalDisplay::GREEN_TEXT);

        sleep(3);
    } else {
        // Если RGB не поддерживается, используем стандартные цвета
        display.fillBackground(COLOR_BLUE);
        display.addImage(digit_0, 10, 5, NTerminalDisplay::YELLOW_TEXT);
        sleep(3);
    }

    return 0;
}