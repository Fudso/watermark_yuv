#ifndef CORE_GRAPHIC_FRAME_FRAME_FACTORY_H
#define CORE_GRAPHIC_FRAME_FRAME_FACTORY_H

#include <memory>

namespace Core
{
	class IFrame;
	enum class PixelFormat;

	class FrameFactory
	{
	public:
		virtual ~FrameFactory() = default;

		virtual std::shared_ptr<IFrame> CreateFrame(size_t width, size_t height, PixelFormat pixelFormat) const = 0;
		
	};

}
#endif
