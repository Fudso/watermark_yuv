#ifndef CORE_GRAPHIC_FRAME_FILE_FRAME_PROVIDER_H
#define CORE_GRAPHIC_FRAME_FILE_FRAME_PROVIDER_H

#include "frame_provider_interface.h"

namespace Core
{
	class IDecoder;

	class FileFrameProvider : public IFrameProvider
	{
	public:
		FileFrameProvider(const std::shared_ptr<IDecoder>& decoder);

		std::shared_ptr<IFrame> GetFrame(size_t index) const override;
		size_t FrameCount() const override;

		PixelFormat FramePixelFormat() const override;

	private:
		std::shared_ptr<IDecoder> _decoder;
	};

}
#endif
