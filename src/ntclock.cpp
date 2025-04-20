#include <iostream>
#include "ntobject.h"
#include "digits_8x8.h"
#include "ntdisplay.h"
/*
// Horizontal render
void hview(){
    //
    int screenRows = height();
    int screenCols = width();

    int digHeight = 8;
    int digWidth = 8;

    // Print hours

    int hh_hi_pos_y = (screenRows-8)/2 + digHeight*0;
    int hh_hi_pos_x = (screenCols-8*8)/2 + digWidth*0;
    printDig(hh_hi_pos_y, hh_hi_pos_x, (int)(_hour / 10), false);

    int hh_lo_pos_y = (screenRows-8)/2 + digHeight*0;
    int hh_lo_pos_x = (screenCols-8*8)/2 + 8;
    printDig(hh_lo_pos_y, hh_lo_pos_x, (int)(_hour % 10), false);

    // Print ":"

    int mm_hi_pos_y = (screenRows-8)/2 + digHeight*0;
    int mm_hi_pos_x = (screenCols-8*8)/2 + 24;

    int mm_lo_pos_y = (screenRows-8)/2 + digHeight*0;
    int mm_lo_pos_x = (screenCols-8*8)/2 + 32;

    // ":"

    int ss_hi_pos_y = (screenRows-8)/2 + digHeight*0;
    int ss_hi_pos_x = (screenCols-8*8)/2 + 48;

    int ss_lo_pos_y = (screenRows-8)/2 + digHeight*0;
    int ss_lo_pos_x = (screenCols-8*8)/2 + 56;


    // Print minutes
    printDig(mm_hi_pos_y, mm_hi_pos_x, (int)(_min / 10), false);
    printDig(mm_lo_pos_y, mm_lo_pos_x, (int)(_min % 10), false);

    // Print seconds
    printDig(ss_hi_pos_y, ss_hi_pos_x, (int)(_sec / 10), false);
    printDig(ss_lo_pos_y, ss_lo_pos_x, (int)(_sec % 10), false);
    // ncurses refresh screen
    refresh();
}
*/


int main(int argc, char*argv[]) {
/*
    NTObject no0(0, "0");
    std::cout << "no0" << " " << no0.name() << std::endl;
    NTObject no1(&no0, "1");  // Правильно: указатель + строка
    std::cout << "no1.parent().name(): " << no1.parent()->name() << std::endl;
    NTObject no2(&no1, "2");  // Правильно: указатель + строка
    std::cout << "no2.parent().name(): " << no2.parent()->name() << std::endl;
    sleep(5);
*/
    NTDisplay display;

	//NTImage nti_hh_hi(display, "Hour_hi");
	//NTImage nti_hh_lo(display, "Hour_lo");

    if (display.isRgbSupported()) {
        // Заливаем терминал градиентным синим фоном
        display.fillBackgroundRgb(30, 30, 100);

        // Устанавливаем оранжевый текст (RGB) и прозрачный фон
        display.setRgbColor(255, 165, 0,   // Оранжевый (R=255, G=165, B=0)
                            0, 0, 0);       // Чёрный фон (но он прозрачен из-за bkgd)
/*
        display.addImage(digits_8x8[0], 10, 5, NTDisplay::CUSTOM);
        display.addImage(digits_8x8[1], 20, 5, NTDisplay::CUSTOM);
        display.addImageArbitrarySize(custom_image, 5, 5, NTDisplay::GREEN_TEXT);
        display.addImageArbitrarySize(digits_8x8[3], 25, 25, NTDisplay::CUSTOM);
*/
		display.addImageArbitrarySize(digits_8x8[0], 10, 5, CUSTOM);
		display.addImageArbitrarySize(custom_image, 5, 5, GREEN_TEXT);
		display.addImageArbitrarySize(digits_8x8[1], 20, 5, CUSTOM);

		display.addImageArbitrarySize(digits_8x8[3], 25, 25, CUSTOM);
        sleep(3);
    } else {
        // Если RGB не поддерживается, используем стандартные цвета
        display.fillBackground(COLOR_BLUE);
        //display.addImage(digit_0, 10, 5, NTDisplay::YELLOW_TEXT);
        display.addImageArbitrarySize(digits_8x8[0], 10, 5, YELLOW_TEXT);
        sleep(3);
    }
    return 0;
}
