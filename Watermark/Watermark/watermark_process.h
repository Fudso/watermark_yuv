#ifndef WATERMARK_WATERMARK_PROCESS_H
#define WATERMARK_WATERMARK_PROCESS_H

#include <memory>
#include <thread>

namespace Core
{
	template <typename T>
	class ConcurrencyQueue;

	class IFrameProvider;
	class IFrameConvertor;
	class IFrame;
}

namespace Watermark
{
	class Message;
	enum class MessageType;

	class WatermarkProcess
	{
	public:
		WatermarkProcess(
			const std::shared_ptr<Core::ConcurrencyQueue<Message>>& messageQueue,
			const std::shared_ptr<Core::IFrameProvider>& videoFramePovider,
			const std::shared_ptr<Core::IFrameProvider>& waterMarkFramePovider,
			const std::shared_ptr<Core::IFrameConvertor>& frameConvertor
		);

		~WatermarkProcess();

		void Start();

	private:
		void PutWatermarkWrapper();
		void PutWatermark();
		void ConvertFrame(std::shared_ptr<Core::IFrame>& watermarkFrame) const;
		void SendMessage(MessageType messageType, const std::shared_ptr<Core::IFrame>& processedFrame);

	private:
		const std::shared_ptr<Core::ConcurrencyQueue<Message>> _messageQueue;
		std::shared_ptr<Core::IFrameProvider> _videoFramePovider;
		std::shared_ptr<Core::IFrameProvider> _waterMarkFramePovider;
		std::shared_ptr<Core::IFrameConvertor> _frameConvertor;

		std::thread _watermarkProcess;
	};

}
#endif
