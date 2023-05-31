#include "file_frame_provider.h"

#include "Core/Graphic/Frame/pixel_format.h"
#include "Core/Graphic/Frame/frame_interface.h"

#include "Core/Graphic/Frame/Decoder/decoder_interface.h"
#include <stdexcept>

Core::FileFrameProvider::FileFrameProvider(const std::shared_ptr<IDecoder>& decoder)
	: _decoder(decoder)
{
}

std::shared_ptr<Core::IFrame> Core::FileFrameProvider::GetFrame(size_t index) const
{
	if (index >= FrameCount())
	{
		throw std::out_of_range("FileFrameProvider: index out of range");
	}

	return _decoder->GetFrame(index);
}

size_t Core::FileFrameProvider::FrameCount() const
{
	return _decoder->FrameCount();
}

Core::PixelFormat Core::FileFrameProvider::FramePixelFormat() const
{
	return _decoder->FramePixelFormat();
}
