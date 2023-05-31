#include "application.h"

#include "Core/ConcurrencyQueue/concurrency_queue.h"
#include "Core/Graphic/Frame/frame_interface.h"
#include "Core/Graphic/Frame/Encoder/encoder_interface.h"
#include "Core/Graphic/Frame/frame_provider_interface.h"

#include "message.h"
#include "watermark_process.h"

#include <iostream>

Watermark::Application::Application(
	const std::shared_ptr<Core::IFrameProvider>& videoFramePovider,
	const std::shared_ptr<Core::IFrameProvider>& waterMarkFramePovider,
	const std::shared_ptr<Core::IFrameConvertor>& frameConvertor,
	const std::shared_ptr<Core::IEncoder>& encoder
)
	: _messageQueue(std::make_shared<Core::ConcurrencyQueue<Message>>())
	, _watermarkProcess(std::make_unique<WatermarkProcess>(
		_messageQueue, videoFramePovider, waterMarkFramePovider, frameConvertor))
	, _encoder(encoder)
{
}

bool Watermark::Application::Start()
{
	_watermarkProcess->Start();

	bool result = StartHandlingMessages();

	return result;
}

bool Watermark::Application::StartHandlingMessages()
{
	while (true) {

		Message currentMessage = _messageQueue->front();
		_messageQueue->pop();

		switch (currentMessage.MessageType())
		{
		case MessageType::FrameProcessed:
			std::cout << "Frame processed" << std::endl;
			EncodeFrame(std::move(currentMessage.ProcessedFrame()));
			break;

		case MessageType::FrameProcessingCompleted:
			std::cout << "Frame processing completed" << std::endl;
			return true;

		case MessageType::ErrorOccurred:
			std::cout << "Error occurred" << std::endl;
			return false;
		}	
	}

	return true;
}

void Watermark::Application::EncodeFrame(std::shared_ptr<Core::IFrame>&& frame)
{
	_encoder->EncodeFrame(std::move(frame));
}
