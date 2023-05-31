#ifndef CORE_GRAPHIC_FRAME_FRAME_INTERFACE_H
#define CORE_GRAPHIC_FRAME_FRAME_INTERFACE_H

#include <vector>

namespace Core
{
	enum class PixelFormat;

	class IFrame
	{
	public:
		virtual ~IFrame() = default;

		virtual size_t Width() const = 0;
		virtual size_t Height() const = 0;

		virtual size_t PixelDepth() const = 0;
	 
		virtual PixelFormat PixelFormat() const = 0;

		virtual const unsigned char* const RawData() const = 0;

		virtual void LoadData(std::vector<unsigned char>&& buffer) = 0;

		virtual size_t DataByteSize() const = 0;

		virtual void Merge(IFrame* frame) = 0;
	};

}
#endif
