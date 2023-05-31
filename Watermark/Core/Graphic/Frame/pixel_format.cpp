#include "pixel_format.h"

size_t Core::BitsPerPixel(PixelFormat pixelFormat)
{
	switch (pixelFormat)
	{
	case PixelFormat::BGR24:
		return 24;

	case PixelFormat::YUV420:
		return 12;

	default:
		break;
	}
}