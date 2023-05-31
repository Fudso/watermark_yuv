#ifndef CORE_GRAPHIC_FRAME_CPU_FRAME_FACTORY_H
#define CORE_GRAPHIC_FRAME_CPU_FRAME_FACTORY_H

#include "frame_factory.h"
#include "cpu_frame.h"
#include "pixel_format.h"

namespace Core
{
	class CPUFrameFactory : public FrameFactory
	{
	public:
		std::shared_ptr<IFrame> CreateFrame(size_t width, size_t height, PixelFormat pixelFormat) const override
		{
			return std::make_shared<CPUFrame>(width, height, pixelFormat);
		}

	};
}
#endif
