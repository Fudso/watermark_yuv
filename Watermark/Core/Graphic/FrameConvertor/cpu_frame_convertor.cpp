#include "cpu_frame_convertor.h"

#include "Core/Graphic/Frame/pixel_format.h"
#include "Core/Graphic/Frame/frame_interface.h"
#include "cpu_brg24_to_yuv420_convertor.h"

#include <vector>
#include <algorithm>
#include <stdexcept>
	
struct ColorConversionTable
{
	Core::PixelFormat SrcPixelFormat;
	Core::PixelFormat DstPixelFormat;
	std::shared_ptr<Core::IColorConvertor> Convertor;
};

static const std::vector<ColorConversionTable> _availableColorConversionTable =
{
	{Core::PixelFormat::BGR24, Core::PixelFormat::YUV420, std::make_shared<Core::CPUBRG24ToYUV420Convertor>()}
};

std::shared_ptr<Core::IFrame> Core::CPUFrameConvertor::Convert(const std::shared_ptr<Core::IFrame>& srcFrame, Core::PixelFormat dstPixelFormat) const
{
	if (srcFrame == nullptr)
	{
		return nullptr;
	}

	auto convertor = GetColorConvertor(srcFrame->PixelFormat(), dstPixelFormat);

	if (convertor == nullptr)
	{
		throw std::runtime_error("Unsupported color conversion");
	}

	return convertor->Convert(srcFrame);
}

bool Core::CPUFrameConvertor::ConversionAvailable(PixelFormat srcPixelFormat, PixelFormat dstPixelFormat) const
{
	return GetColorConvertor(srcPixelFormat, dstPixelFormat) != nullptr;
}

std::shared_ptr<Core::IColorConvertor> Core::CPUFrameConvertor::GetColorConvertor(PixelFormat srcPixelFormat, PixelFormat dstPixelFormat) const
{
	auto comporator = [=](const ColorConversionTable& table)
	{
		auto t = table.SrcPixelFormat == srcPixelFormat && table.DstPixelFormat == dstPixelFormat;
		return table.SrcPixelFormat == srcPixelFormat && table.DstPixelFormat == dstPixelFormat;
	};

	auto iter = std::find_if(_availableColorConversionTable.begin(), _availableColorConversionTable.end(), comporator);

	if (iter == _availableColorConversionTable.end())
	{
		return nullptr;
	}

	return iter->Convertor;
}
