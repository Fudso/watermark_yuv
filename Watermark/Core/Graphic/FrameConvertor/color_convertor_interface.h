#ifndef CORE_GRAPHIC_FRAME_CONVERTOR_COLOR_CONVERTOR_INTERFACE_H
#define CORE_GRAPHIC_FRAME_CONVERTOR_COLOR_CONVERTOR_INTERFACE_H

#include <memory>

namespace Core
{
	class IFrame;
	enum class PixelFormat;

	class IColorConvertor 
	{
	public:
		virtual std::shared_ptr<IFrame> Convert(const std::shared_ptr<IFrame>& srcFrame) const = 0;

	};
}


#endif
