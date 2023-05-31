#include "bmp_decoder.h"

#include "Core/Graphic/Frame/pixel_format.h"
#include "Core/Graphic/Frame/frame_interface.h"
#include "Core/Graphic/Frame/frame_factory.h"

#include <stdexcept>
#include <deque>

// Magic number for Bitmap .bmp 24 bpp files (24/8 = 3 = rgb colors only)
static const std::uint16_t BITMAP_BUFFER_MAGIC = 0x4D42;

#pragma pack(push, 1)
struct BitmapHeader
{
	/* Bitmap file header structure */
	std::uint16_t magic;              /* Magic number for file always BM which is 0x4D42 */
	std::uint32_t file_size;          /* Size of file */
	std::uint16_t reserved1;          /* Reserved */
	std::uint16_t reserved2;          /* Reserved */
	std::uint32_t offset_bits;        /* Offset to bitmap data */
	/* Bitmap file info structure */
	std::uint32_t size;               /* Size of info header */
	std::int32_t width;               /* Width of image */
	std::int32_t height;              /* Height of image */
	std::uint16_t planes;             /* Number of color planes */
	std::uint16_t bits_per_pixel;     /* Number of bits per pixel */
	std::uint32_t compression;        /* Type of compression to use */
	std::uint32_t size_image;         /* Size of image data */
	std::int32_t x_pixels_per_meter;  /* X pixels per meter */
	std::int32_t y_pixels_per_meter;  /* Y pixels per meter */
	std::uint32_t clr_used;           /* Number of colors used */
	std::uint32_t clr_important;      /* Number of important colors */
};
static_assert(sizeof(BitmapHeader) == 54, "Bitmap header size must be 54 bytes");

Core::BMPDecoder::BMPDecoder(const std::string& fileName, const std::shared_ptr<FrameFactory>& frameFactory)
	: _stream(fileName, std::ios::binary)
	, _frameFactory(frameFactory)
	, _frame(nullptr)
{
	if (_stream.IsOpen() == false)
	{
		throw std::runtime_error("BNGDecoder: Can't open file " + fileName);
	}
}

std::shared_ptr<Core::IFrame> Core::BMPDecoder::GetFrame(size_t index)
{
	if (_frame == nullptr)
	{
		_frame = DecodeFrame();
	}

	return _frame;
}

size_t Core::BMPDecoder::FrameCount() const
{
	return 1;
}

Core::PixelFormat Core::BMPDecoder::FramePixelFormat() const
{
	return Core::PixelFormat::BGR24;
}

// Used this source as example:
//https://github.com/kbuffardi/Bitmap/blob/master/bitmap.cpp
//https://github.com/baderouaich/BitmapPlusPlus/blob/master/include/BitmapPlusPlus.hpp
//
std::shared_ptr<Core::IFrame> Core::BMPDecoder::DecodeFrame()
{
	auto& stream = _stream.GetStrem();
	
	BitmapHeader header;
	stream.read(reinterpret_cast<char*>(&header), sizeof(header));

	if (header.magic != BITMAP_BUFFER_MAGIC)
	{
		throw std::runtime_error("BNGDecoder: Unrecognized file format");
	}

	if (header.bits_per_pixel != 24)
	{
		throw std::runtime_error("BNGDecoder: BMP image is not supported. Only support for 24-bit images");
	}

	if (header.compression != 0)
	{
		throw std::runtime_error("BNGDecoder: BMP image is compressed. Only supports uncompressed images");
	}

	bool flip = true;
	if (header.height < 0)
	{
		flip = false;
		header.height *= std::abs(header.height);
	}

	const size_t width = static_cast<size_t>(header.width);
	const size_t height = static_cast<size_t>(header.height);

	const size_t stride = width * 3 + width % 4;
	const size_t dataSize = stride * height;

	std::vector<unsigned char> data(dataSize);

	unsigned char* dataBuffer = data.data();

	stream.seekg(sizeof(header));
	stream.read(reinterpret_cast<char*>(data.data()), data.size());

	if (flip)
	{
		for (size_t i = 0; i < height / 2; ++i)
		{
			for (size_t j = 0; j < stride; ++j)
			{
				std::swap(data[i * stride + j], data[(height - 1 - i) * stride + j]);
			}
		}
	}

	auto frame = _frameFactory->CreateFrame(width, height, PixelFormat::BGR24);
	frame->LoadData(std::move(data));

	return frame;
}
