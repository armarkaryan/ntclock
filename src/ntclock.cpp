#include <iostream>
#include "ntobject.h"
#include "digits_8x8.h"
#include "digits_16x16.h"
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
	//
    NTDisplay display;

	//NTImage nti_hh_hi(&display, "Hour_hi", digits_8x8[8].img, 25, 16, nt::ColorPair::MAGENTA_TEXT, nt::ImageSize::SIZE_8x8);
	NTImage nti_hh_hi(&display, "Hour_hi", digits_8x8[8].img, 25, 16, nt::ColorPair::MAGENTA_TEXT);
	//NTImage nti_hh_lo(&display, "Hour_lo", digits_8x8[9].img, 24, 16, nt::ColorPair::MAGENTA_TEXT, nt::ImageSize::SIZE_8x8);
	NTImage nti_hh_lo(&display, "Hour_lo", digits_8x8[9].img, 24, 16, nt::ColorPair::MAGENTA_TEXT);
	sleep(3);

	if (display.isRgbSupported()) {
        // Заливаем терминал градиентным синим фоном
        display.fillBackgroundRgb(30, 30, 100);

        // Устанавливаем оранжевый текст (RGB) и прозрачный фон
        display.setRgbColor(255, 165, 0,   // Оранжевый (R=255, G=165, B=0)
                            0, 100, 0);       // Чёрный фон (но он прозрачен из-за bkgd)
/*
        display.addImage(digits_8x8[0], 10, 5, NTDisplay::CUSTOM);
        display.addImage(digits_8x8[1], 20, 5, NTDisplay::CUSTOM);
        display.addImageArbitrarySize(custom_image, 5, 5, NTDisplay::GREEN_TEXT);
        display.addImageArbitrarySize(digits_8x8[3], 25, 25, NTDisplay::CUSTOM);
*/
		display.addImageArbitrarySize(digits_8x8[0].img, 10, 5, nt::ColorPair::CUSTOM);
		sleep(3);
		display.addImageArbitrarySize(custom_images[0].img, 5, 5, nt::ColorPair::GREEN_TEXT);
		sleep(3);
		display.addImageArbitrarySize(digits_8x8[1].img, 20, 5, nt::ColorPair::CUSTOM);
		sleep(3);

        nti_hh_hi.setParent(&display); // For test
		//nti_hh_hi.setx(16);
		sleep(3);
        display.addImageArbitrarySize(nti_hh_hi.image(), nti_hh_hi.x(), nti_hh_hi.y(), nti_hh_hi.colorPair());
		sleep(3);
		nti_hh_hi.setx(16);
		sleep(3);
        display.addImageArbitrarySize(nti_hh_lo.image(), nti_hh_lo.x(), nti_hh_lo.y(), nti_hh_lo.colorPair());
        sleep(3);
    } else {
        // Если RGB не поддерживается, используем стандартные цвета
		display.fillBackground(COLOR_BLUE);
		display.addImageArbitrarySize(digits_8x8[0].img, 10, 5, nt::ColorPair::YELLOW_TEXT);
        sleep(3);
    }
    return 0;
}
