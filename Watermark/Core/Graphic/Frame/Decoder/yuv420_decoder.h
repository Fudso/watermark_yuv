#ifndef CORE_GRAPHIC_FRAME_FRAME_DECODER_YUV420_DECODER_H
#define CORE_GRAPHIC_FRAME_FRAME_DECODER_YUV420_DECODER_H

#include "decoder_interface.h"
#include "Core/Utilities/stream_guard.h"

#include <string>
#include <memory>

namespace Core
{
	class FrameFactory;

	class YUV420Decoder : public IDecoder
	{
	public:
		YUV420Decoder(
			const std::string& fileName, size_t width, size_t height,
			const std::shared_ptr<FrameFactory>& frameFactory
		);

		std::shared_ptr<IFrame> GetFrame(size_t index) override;
		size_t FrameCount() const override;

		PixelFormat FramePixelFormat() const;

	private:
		size_t CalculateFrameCount();
		size_t FrameSize() const;

	private:
		StreamGuard<std::ifstream> _stream;
		size_t _width;
		size_t _height;
		std::shared_ptr<FrameFactory> _frameFactory;
		size_t _frameCount;
	};

}
#endif
