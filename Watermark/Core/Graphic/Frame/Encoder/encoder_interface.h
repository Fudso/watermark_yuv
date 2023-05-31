#ifndef CORE_GRAPHIC_FRAME_ENCODER_ENCODER_INTERFACE_H
#define CORE_GRAPHIC_FRAME_ENCODER_ENCODER_INTERFACE_H

#include <memory>

namespace Core
{
	class IFrame;

	class IEncoder
	{
	public:
		virtual ~IEncoder() = default;

		virtual void EncodeFrame(std::shared_ptr<IFrame>&& frame) = 0;
	};

}
#endif
