#ifndef CORE_GRAPHIC_FRAME_ENCODER_YUV420_ENCODER_H
#define CORE_GRAPHIC_FRAME_ENCODER_YUV420_ENCODER_H

#include "encoder_interface.h"
#include "Core/Utilities/stream_guard.h"

#include <string>

namespace Core
{
	class YUVEncoder : public IEncoder
	{
	public:
		YUVEncoder(const std::string fileName);

		void EncodeFrame(std::shared_ptr<IFrame>&& frame) override;

	private:
		StreamGuard<std::ofstream> _stream;
	};

}
#endif
