#ifndef CORE_GRAPHIC_FRAME_CONVERTOR_COLOR_CONVERTOR_CPU_BRG24_TO_YUV420_H
#define CORE_GRAPHIC_FRAME_CONVERTOR_COLOR_CONVERTOR_CPU_BRG24_TO_YUV420_H

#include "color_convertor_interface.h"

namespace Core
{
	class CPUBRG24ToYUV420Convertor : public IColorConvertor
	{
	public:
		virtual std::shared_ptr<IFrame> Convert(const std::shared_ptr<IFrame>& srcFrame) const override;

	};
}


#endif
