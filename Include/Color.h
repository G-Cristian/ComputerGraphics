#ifndef _COLOR_H_
#define _COLOR_H_

namespace K9 {
	typedef unsigned int Color32;
	typedef unsigned char uchar;

	inline Color32 setColor32(uchar red, uchar green, uchar blue, uchar alpha) {
		return (((Color32)(alpha)) << 24) | (((Color32)(blue)) << 16) | (((Color32)(green)) << 8) | (((Color32)(red)));
	}

	inline uchar getAlphaColor32(Color32 color) {
		return (uchar)((color & 0xFF000000) >> 24);
	}

	inline uchar getBlueColor32(Color32 color) {
		return (uchar)((color & 0x00FF0000) >> 16);
	}

	inline uchar getGreenColor32(Color32 color) {
		return (uchar)((color & 0x0000FF00) >> 8);
	}

	inline uchar getRedColor32(Color32 color) {
		return (uchar)((color & 0x000000FF));
	}
}

#endif // !_COLOR_H_
