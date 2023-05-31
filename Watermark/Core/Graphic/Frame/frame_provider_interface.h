#ifndef CORE_GRAPHIC_FRAME_FRAME_PROVIDER_INTERFACE_H
#define CORE_GRAPHIC_FRAME_FRAME_PROVIDER_INTERFACE_H

#include <memory>

namespace Core
{
	class IFrame;
	enum class PixelFormat;

	class IFrameProvider
	{
	public:
		virtual ~IFrameProvider() = default;

		virtual std::shared_ptr<IFrame> GetFrame(size_t index) const = 0;
		virtual size_t FrameCount() const = 0;

		virtual PixelFormat FramePixelFormat() const = 0;
	};

}
#endif
