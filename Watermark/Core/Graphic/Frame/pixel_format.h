#ifndef CORE_GRAPHIC_FRAME_PIXEL_FORMAT_H
#define CORE_GRAPHIC_FRAME_PIXEL_FORMAT_H

namespace Core
{
	enum class PixelFormat
	{
		BGR24, // 8 8 8
		YUV420 // 8 2 2
	};

	size_t BitsPerPixel(PixelFormat pixelFormat);
}

#endif
