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

/*
int main(int argc, char*argv[]) {
	//
    NTDisplay display;

	NTImage hh_hi(&display, "hh_hi", digits_8x8[0].img, 0, 0, nt::ColorPair::MAGENTA_TEXT);
	display.addImage(hh_hi);

	NTImage hh_lo(&display, "hh_lo", digits_8x8[1].img, 8, 0, nt::ColorPair::MAGENTA_TEXT);
	display.addImage(hh_lo);

	NTImage mm_hi(&display, "mm_hi", digits_8x8[2].img, 24, 0, nt::ColorPair::MAGENTA_TEXT);
	display.addImage(mm_hi);

	NTImage mm_lo(&display, "mm_lo", digits_8x8[3].img, 32, 0, nt::ColorPair::MAGENTA_TEXT);
	display.addImage(mm_lo);

	NTImage ss_hi(&display, "ss_hi", digits_8x8[4].img, 48, 0, nt::ColorPair::MAGENTA_TEXT);
	display.addImage(ss_hi);

	NTImage ss_lo(&display, "ss_lo", digits_8x8[5].img, 56, 0, nt::ColorPair::MAGENTA_TEXT);
	display.addImage(ss_lo);

	int x = 0;

	if (display.isRgbSupported()) {
		// Заливаем терминал градиентным синим фономntlayoutmanager.h
        display.fillBackgroundRgb(30, 30, 100);

        // Устанавливаем оранжевый текст (RGB) и прозрачный фон
        display.setRgbColor(255, 165, 0,   // Оранжевый (R=255, G=165, B=0)
							30, 30, 100);       // Чёрный фон (но он прозрачен из-за bkgd)

while(1){
		//nti_hh_hi.setParent(&display); // For test
		hh_hi.setx(x);

		if(x < 50)x++;else x=0;
		sleep(1);
}
    } else {
        // Если RGB не поддерживается, используем стандартные цвета
		display.fillBackground(COLOR_BLUE);
		//display.addImage("Image_06", digits_8x8[0].img, 10, 5, nt::ColorPair::YELLOW_TEXT);
		sleep(1);
	}
    return 0;
}
*/

#include "ntlayoutmanager.h"

int main(int argc, char* argv[]) {
	NTDisplay display;
	NTLayoutManager layout(&display, "clock_layout");

	layout.setLayoutType(NTLayoutManager::LayoutType::HORIZONTAL);
	layout.setSpacing(1); // Space between digits

	// Create digit images
	NTImage hh_hi(&display, "hh_hi", digits_8x8[0].img, 0, 0, nt::ColorPair::MAGENTA_TEXT);
	NTImage hh_lo(&display, "hh_lo", digits_8x8[1].img, 0, 0, nt::ColorPair::MAGENTA_TEXT);
	NTImage mm_hi(&display, "mm_hi", digits_8x8[2].img, 0, 0, nt::ColorPair::MAGENTA_TEXT);
	NTImage mm_lo(&display, "mm_lo", digits_8x8[3].img, 0, 0, nt::ColorPair::MAGENTA_TEXT);
	NTImage ss_hi(&display, "ss_hi", digits_8x8[4].img, 0, 0, nt::ColorPair::MAGENTA_TEXT);
	NTImage ss_lo(&display, "ss_lo", digits_8x8[5].img, 0, 0, nt::ColorPair::MAGENTA_TEXT);

	// Add images to layout manager
	layout.addImage(&hh_hi);
	layout.addImage(&hh_lo);
	layout.addImage(&mm_hi);
	layout.addImage(&mm_lo);
	layout.addImage(&ss_hi);
	layout.addImage(&ss_lo);

	// Add images to display
	display.addImage(hh_hi);
	display.addImage(hh_lo);
	display.addImage(mm_hi);
	display.addImage(mm_lo);
	display.addImage(ss_hi);
	display.addImage(ss_lo);

	// Update layout and center it
	layout.updateLayout(display.width(), display.height());
	//layout.updateLayout(50, 50);
	//layout.centerInContainer(display.width(), display.height());

	if (display.isRgbSupported()) {
		display.fillBackgroundRgb(50, 50, 100);
		display.setRgbColor(255, 165, 0, 30, 30, 100);

		unsigned int x = 0;
		while(1) {
			// Your update logic here
			//nti_hh_hi.setParent(&display); // For test
			hh_hi.setx(x);hh_lo.setx(display.width()-8-x);
			if(x < display.width()-8)x++;else x=0;

			sleep(1);
		}
	} else {
		display.fillBackground(COLOR_BLUE);
		sleep(1);
	}

	return 0;
}
