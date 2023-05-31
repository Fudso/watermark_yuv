#include "watermark_process.h"

#include "Core/ConcurrencyQueue/concurrency_queue.h"
#include "Core/Graphic/Frame/frame_provider_interface.h"
#include "Core/Graphic/FrameConvertor/frame_convertor_interface.h"

#include "message.h"

#include <iostream>
#include <future>

Watermark::WatermarkProcess::WatermarkProcess(
	const std::shared_ptr<Core::ConcurrencyQueue<Message>>& messageQueue,
	const std::shared_ptr<Core::IFrameProvider>& videoFramePovider,
	const std::shared_ptr<Core::IFrameProvider>& waterMarkFramePovider,
	const std::shared_ptr<Core::IFrameConvertor>& frameConvertor
)
	: _messageQueue(messageQueue)
	, _videoFramePovider(videoFramePovider)
	, _waterMarkFramePovider(waterMarkFramePovider)
	, _frameConvertor(frameConvertor)
{
}

Watermark::WatermarkProcess::~WatermarkProcess()
{
	if (_watermarkProcess.joinable())
	{
		_watermarkProcess.join();
	}
}

void Watermark::WatermarkProcess::Start()
{
	_watermarkProcess = std::thread(&WatermarkProcess::PutWatermarkWrapper, this);
}

void Watermark::WatermarkProcess::PutWatermarkWrapper()
{
	try
	{
		PutWatermark();
	}
	catch (const std::exception& exept)
	{
		std::cerr << exept.what() << std::endl;
		SendMessage(MessageType::ErrorOccurred, nullptr);
		return;
	}
}

void Watermark::WatermarkProcess::PutWatermark()
{
	std::shared_ptr<Core::IFrame> watermarkFrame = _waterMarkFramePovider->GetFrame(0u);

	if (watermarkFrame == nullptr)
	{
		throw std::runtime_error("Failed to decode watermark frame");
	}

	ConvertFrame(watermarkFrame);

	for (size_t i = 0u; i < _videoFramePovider->FrameCount(); ++i)
	{
		auto videoFrame = _videoFramePovider->GetFrame(i);
		videoFrame->Merge(watermarkFrame.get());
		SendMessage(MessageType::FrameProcessed, videoFrame);
	}

	SendMessage(MessageType::FrameProcessingCompleted, nullptr);
}

void Watermark::WatermarkProcess::ConvertFrame(std::shared_ptr<Core::IFrame>& watermarkFrame) const
{
	const auto videoPixelFormat = _videoFramePovider->FramePixelFormat();

	if (videoPixelFormat == watermarkFrame->PixelFormat())
	{
		return;
	}

	watermarkFrame = _frameConvertor->Convert(watermarkFrame, videoPixelFormat);
}

void Watermark::WatermarkProcess::SendMessage(
	MessageType messageType, const std::shared_ptr<Core::IFrame>& processedFrame = nullptr)
{
	auto message = Message(messageType, processedFrame);
	_messageQueue->push(std::move(message));
}

