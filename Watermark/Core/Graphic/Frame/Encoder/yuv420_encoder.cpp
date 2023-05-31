#include "yuv420_encoder.h"

#include "Core/Graphic/Frame/pixel_format.h"
#include "Core/Graphic/Frame/frame_interface.h"

Core::YUVEncoder::YUVEncoder(const std::string fileName)
	: _stream(fileName, std::ios::binary)
{
	if (_stream.IsOpen() == false)
	{
		throw std::runtime_error("YUVEncoder: Can't open file " + fileName);
	}
}

void Core::YUVEncoder::EncodeFrame(std::shared_ptr<Core::IFrame>&& frame)
{
	auto& stream = _stream.GetStrem();
	stream.write(reinterpret_cast<const char*>(frame->RawData()), frame->DataByteSize());
}
