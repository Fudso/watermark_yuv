#include "cpu_brg24_to_yuv420_convertor.h"

#include "Core/Graphic/Frame/pixel_format.h"
#include "Core/Graphic/Frame/frame_interface.h"
#include "Core/Graphic/Frame/cpu_frame.h"

#include <vector>

float clamp(float value, float low = 0, float hight = 255)
{
	return std::min(hight, std::max(value, low));
}

std::shared_ptr<Core::IFrame> Core::CPUBRG24ToYUV420Convertor::Convert(const std::shared_ptr<IFrame>& srcFrame) const
{
	const unsigned char* const rgb24 = srcFrame->RawData();
	const size_t width = srcFrame->Width();
	const auto height = srcFrame->Height();

	const auto yuvDataSize = width * height * 3 / 2;
	std::vector<unsigned char> yuvData(yuvDataSize);

	size_t frameSize = width * height;
	size_t chromaSize = frameSize / 4;

	unsigned char* yPlane = yuvData.data();
	unsigned char* uPlane = yPlane + frameSize;
	unsigned char* vPlane = uPlane + chromaSize;

	for (int j = 0; j < height; j++)
	{
		const unsigned char* rgb = rgb24 + width * j * 3;
		for (int i = 0; i < width; i++)
		{
			auto b = static_cast<float>(*rgb++);
			auto g = static_cast<float>(*rgb++);
			auto r = static_cast<float>(*rgb++);

			// Source: https://stackoverflow.com/questions/17892346/how-to-convert-rgb-yuv-rgb-both-ways
			const auto y = static_cast<unsigned char>(
				clamp(0.257f * r + 0.504f * g + 0.098f * b + 16.f));
			const auto u = static_cast<unsigned char>(
				clamp(-0.148f * r - 0.291f * g + 0.439f * b + 128.f));
			const auto v = static_cast<unsigned char>(
				clamp(0.439f * r - 0.368f * g - 0.071f * b + 128.f));
\
			*(yPlane++) = y;
			if (j % 2 == 0 && i % 2 == 0)
			{
				*(uPlane++) = u;
				*(vPlane++) = v;
			}
		}
	}

	std::shared_ptr<CPUFrame> frame = std::make_shared< CPUFrame>(width, height, PixelFormat::YUV420);
	frame->LoadData(std::move(yuvData));

	return frame;
}
