#include "Core/Graphic/FrameConvertor/cpu_frame_convertor.h"
#include "Core/Graphic/Frame/Decoder/bmp_decoder.h"
#include "Core/Graphic/Frame/Decoder/yuv420_decoder.h"
#include "Core/Graphic/Frame/Encoder/yuv420_encoder.h"
#include "Core/Graphic/Frame/cpu_frame_factory.h"
#include "Core/Graphic/Frame/file_frame_provider.h"

#include "config.h"

#include "Watermark/application.h"

#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>


int main()
{
	const std::string dataPath = std::string(DATA_PATH);
	const std::string yuvVideoFileName = std::string(INPUT_VIDEO);
	const std::string bmpFileName = std::string(WATERMARK_BMP);
	const std::string outputVideoFileName = std::string(OUTPUT_VIDEO);

	const size_t originalVideoWidth = YUV_VIDEO_WIDTH;
	const size_t originalVideoHeight = YUV_VIDEO_HEIGHT;

	std::shared_ptr<Core::FrameFactory> frameFactory = std::make_shared<Core::CPUFrameFactory>();
	std::shared_ptr<Core::IDecoder> yuvDecoder;
	std::shared_ptr<Core::IDecoder> bmpDecoder;
	std::shared_ptr<Core::IEncoder> encoder;

	try
	{
		yuvDecoder = std::make_shared<Core::YUV420Decoder>(
			yuvVideoFileName, originalVideoWidth, originalVideoHeight, frameFactory);

		bmpDecoder = std::make_shared<Core::BMPDecoder>(
			bmpFileName, frameFactory);

		encoder = std::make_shared<Core::YUVEncoder>(outputVideoFileName);
	}
	catch (const std::exception& exept)
	{
		std::cerr << exept.what();
		return EXIT_FAILURE;
	}

	std::shared_ptr<Core::IFrameProvider> videoFrameProvider = 
		std::make_shared<Core::FileFrameProvider>(yuvDecoder);

	std::shared_ptr<Core::IFrameProvider> bngFrameProvider =
		std::make_shared<Core::FileFrameProvider>(bmpDecoder);

	std::shared_ptr<Core::IFrameConvertor> frameConvertor = 
		std::make_shared<Core::CPUFrameConvertor>();

	Watermark::Application app(videoFrameProvider, bngFrameProvider, frameConvertor, encoder);
	
	bool result = app.Start();

	return result ? EXIT_SUCCESS : EXIT_FAILURE;
}
