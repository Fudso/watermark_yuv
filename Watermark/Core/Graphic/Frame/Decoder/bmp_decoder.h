#ifndef CORE_GRAPHIC_FRAME_FRAME_DECODER_BNG_DECODER_H
#define CORE_GRAPHIC_FRAME_FRAME_DECODER_BNG_DECODER_H

#include "decoder_interface.h"
#include "Core/Utilities/stream_guard.h"

#include <string>
#include <memory>

namespace Core
{
	class FrameFactory;

	class BMPDecoder : public IDecoder
	{
	public:
		BMPDecoder(const std::string& fileName, const std::shared_ptr<FrameFactory>& frameFactory);

		std::shared_ptr<IFrame> GetFrame(size_t index) override;
		size_t FrameCount() const override;

		PixelFormat FramePixelFormat() const;

	private:
		std::shared_ptr<IFrame> DecodeFrame();

	private:
		StreamGuard<std::ifstream> _stream;
		std::shared_ptr<FrameFactory> _frameFactory;
		std::shared_ptr<IFrame> _frame;
	};

}
#endif
