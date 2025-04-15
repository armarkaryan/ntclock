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