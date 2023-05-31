#ifndef CORE_GRAPHIC_FRAME_CONVERTOR_FRAME_CONVERTOR_INTERFACE_H
#define CORE_GRAPHIC_FRAME_CONVERTOR_FRAME_CONVERTOR_INTERFACE_H

#include <memory>

namespace Core
{
	class IFrame;
	enum class PixelFormat;

	class IFrameConvertor
	{
	public:
		virtual ~IFrameConvertor() = default;
		virtual std::shared_ptr<IFrame> Convert(const std::shared_ptr<IFrame>& srcFrame, PixelFormat pixelFormat) const = 0;
		virtual bool ConversionAvailable(PixelFormat srcPixelFormat, PixelFormat dstPixelFormat) const = 0;
	};
}


#endif