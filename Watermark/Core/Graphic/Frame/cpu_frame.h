#ifndef CORE_GRAPHIC_FRAME_CPU_FRAME_H
#define CORE_GRAPHIC_FRAME_CPU_FRAME_H

#include "Core/Graphic/Frame/frame_interface.h"

namespace Core
{


	class CPUFrame : public IFrame
	{
	public:
		CPUFrame(size_t width, size_t height, Core::PixelFormat pixelFormat);

		~CPUFrame();

		size_t Width() const override;
		size_t Height() const override;

		size_t PixelDepth() const override;

		Core::PixelFormat PixelFormat() const override;

		const unsigned char* const RawData() const override;

		void LoadData(std::vector<unsigned char>&& buffer) override;

		void Merge(IFrame* frame) override;

		size_t DataByteSize() const override;

	private:
		void MergeYUV420Frame(IFrame* frame);

	private:
		size_t _width;
		size_t _height;
		Core::PixelFormat _pixelFormat;

		std::vector<unsigned char> _data;
	};

}
#endif
