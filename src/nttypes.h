#ifndef NTTYPES_H
#define NTTYPES_H

// Цветовые пары (текст/фон)
enum ColorPair {
	DEFAULT = 1,
	RED_TEXT,
	GREEN_TEXT,
	BLUE_TEXT,
	YELLOW_TEXT,
	CYAN_TEXT,
	MAGENTA_TEXT,
	WHITE_TEXT,
	CUSTOM
};

// Поддерживаемые размеры изображений
enum ImageSize {
	SIZE_4x4,
	SIZE_8x4,
	SIZE_4x8,
	SIZE_8x8,
	SIZE_8x16,
	SIZE_16x8,
	SIZE_16x16
};

// End of header guard
#endif // NTTYPES_H
