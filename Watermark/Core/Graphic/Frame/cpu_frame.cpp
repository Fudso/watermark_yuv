#include "cpu_frame.h"
#include "cpu_frame.h"
#include "pixel_format.h"
#include <stdexcept>

Core::CPUFrame::CPUFrame(size_t width, size_t height, Core::PixelFormat pixelFormat)
	: _width(width)
	, _height(height)
	, _pixelFormat(pixelFormat)
{
}

Core::CPUFrame::~CPUFrame()
{
}

size_t Core::CPUFrame::Width() const
{
	return _width;
}

size_t Core::CPUFrame::Height() const
{
	return _height;
}

size_t Core::CPUFrame::PixelDepth() const
{
	return BitsPerPixel(_pixelFormat);
}

Core::PixelFormat Core::CPUFrame::PixelFormat() const
{
	return _pixelFormat;
}

const unsigned char* const Core::CPUFrame::RawData() const
{
	return _data.data();
}

void Core::CPUFrame::LoadData(std::vector<unsigned char>&& buffer)
{
	_data = std::move(buffer);
}

void Core::CPUFrame::Merge(IFrame* frame)
{
	if (_pixelFormat != frame->PixelFormat())
	{
		throw std::runtime_error("CPUFrame: Incorrect pixel format. Merge operation not available");
	}

	if (_width < frame->Width() || _height < frame->Height())
	{
		throw std::runtime_error("CPUFrame:  hight/width must be less than original frame. Merge operation not available");
	}

	switch (_pixelFormat)
	{
	case PixelFormat::YUV420:
		MergeYUV420Frame(frame);
		break;

	default:
		throw std::runtime_error("CPUFrame:  Merge operation is not implemented");
	}

}

size_t Core::CPUFrame::DataByteSize() const
{
	return _data.size();
}

void Core::CPUFrame::MergeYUV420Frame(IFrame* frame)
{
	size_t originalFrameSize = _width * _height;
	size_t originalChromaSize = originalFrameSize / 4;

	unsigned char* originalYPlane = _data.data();
	unsigned char* originalUPlane = originalYPlane + originalFrameSize;
	unsigned char* originalVPlane = originalUPlane + originalChromaSize;
	
	size_t overlayFrameSize = frame->Width() * frame->Height();
	size_t overlayChromaSize = overlayFrameSize / 4;

	const unsigned char* const overlayYPlane = frame->RawData();
	const unsigned char* const overlayUPlane = overlayYPlane + overlayFrameSize;
	const unsigned char* const overlayVPlane = overlayUPlane + overlayChromaSize;

	for (int i = 0; i < frame->Height(); i++) {
		for (int j = 0; j < frame->Width(); j++) {
			originalYPlane[i * _width + j] = overlayYPlane[i * frame->Width() + j] / 2;
		}
	}

	for (int i = 0; i < frame->Height() / 2; i++) {
		for (int j = 0; j < frame->Width() / 2; j++) {
			originalUPlane[i * _width / 2 + j] = overlayUPlane[i * frame->Width() / 2 + j];
			originalVPlane[i * _width / 2 + j] = overlayVPlane[i * frame->Width() / 2 + j];
		}
	}
}
