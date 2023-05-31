#include "yuv420_decoder.h"

#include "Core/Graphic/Frame/pixel_format.h"
#include "Core/Graphic/Frame/frame_interface.h"
#include "Core/Graphic/Frame/frame_factory.h"

Core::YUV420Decoder::YUV420Decoder(
	const std::string& fileName, 
	size_t width, size_t height,
	const std::shared_ptr<FrameFactory>& frameFactory
)
	: _stream(fileName, std::ios::binary)
	, _width(width)
	, _height(height)
	, _frameFactory(frameFactory)
	, _frameCount(CalculateFrameCount())
{
	if (_stream.IsOpen() == false)
	{
		throw std::runtime_error("YUV420Decoder: Can't open file " + fileName);
	}
}

std::shared_ptr<Core::IFrame> Core::YUV420Decoder::GetFrame(size_t index)
{
	size_t frameSize = FrameSize();
	std::vector<unsigned char> yuvFrameData(frameSize);

	auto& stream = _stream.GetStrem();
	size_t offset = index * frameSize;

	stream.seekg(offset);
	stream.read(reinterpret_cast<char*>(yuvFrameData.data()), frameSize);
	
	auto frame = _frameFactory->CreateFrame(_width, _height, PixelFormat::YUV420);
	frame->LoadData(std::move(yuvFrameData));

	return frame;
}

size_t Core::YUV420Decoder::FrameCount() const
{
	return _frameCount;
}

Core::PixelFormat Core::YUV420Decoder::FramePixelFormat() const
{
	return Core::PixelFormat::YUV420;
}

size_t Core::YUV420Decoder::CalculateFrameCount()
{
	auto& stream = _stream.GetStrem();

	std::streampos fileSize = 0;
	fileSize = stream.tellg();
	stream.seekg(0, std::ios::end);
	fileSize = stream.tellg() - fileSize;
	stream.seekg(0, std::ios::beg);

	return static_cast<size_t>(fileSize) / FrameSize();
}

size_t Core::YUV420Decoder::FrameSize() const
{
	return _width * _height * 3 / 2;
}