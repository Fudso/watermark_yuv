#ifndef CORE_GRAPHIC_FRAME_CONVERTOR_CPU_FRAME_CONVERTOR_H
#define CORE_GRAPHIC_FRAME_CONVERTOR_CPU_FRAME_CONVERTOR_H

#include "frame_convertor_interface.h"

namespace Core
{
	class IColorConvertor;

	class CPUFrameConvertor : public IFrameConvertor
	{
	public:
		std::shared_ptr<IFrame> Convert(const std::shared_ptr<IFrame>& srcFrame, PixelFormat dstPixelFormat) const override;
		bool ConversionAvailable(PixelFormat srcPixelFormat, PixelFormat dstPixelFormat) const override;

	private:
		std::shared_ptr<IColorConvertor> GetColorConvertor(PixelFormat srcPixelFormat, PixelFormat dstPixelFormat) const;
	};
}


#endif
