#ifndef WATERMARK_APPLICATION_H
#define WATERMARK_APPLICATION_H

#include "watermark_process.h"

#include <memory>

namespace Core
{
	template <typename T>
	class ConcurrencyQueue;

	class IFrame;
	class IFrameProvider;
	class IFrameConvertor;
	class IFrameProvider;
	class IEncoder;
	class IFrameConvertor;
}

namespace Watermark
{
	class Message;

	class Application
	{
	public:
		Application(
			const std::shared_ptr<Core::IFrameProvider>& videoFramePovider,
			const std::shared_ptr<Core::IFrameProvider>& waterMarkFramePovider,
			const std::shared_ptr<Core::IFrameConvertor>& frameConvertor,
			const std::shared_ptr<Core::IEncoder>& encoder
		);

		bool Start();

	private:
		bool StartHandlingMessages();
		void EncodeFrame(std::shared_ptr<Core::IFrame>&& frame);

	private:
		std::shared_ptr<Core::ConcurrencyQueue<Message>> _messageQueue;
		std::unique_ptr<WatermarkProcess> _watermarkProcess;
		std::shared_ptr<Core::IEncoder> _encoder;
	};

}
#endif
