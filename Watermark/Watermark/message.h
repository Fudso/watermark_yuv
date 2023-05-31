#ifndef WATERMARK_MESSAGE_H
#define WATERMARK_MESSAGE_H

#include "Core/Graphic/Frame/frame_interface.h"
#include "Core/Graphic/Frame/pixel_format.h"

#include <memory>

namespace Watermark
{
	enum class MessageType
	{
		FrameProcessed,
		FrameProcessingCompleted,
		ErrorOccurred
	};

	class Message
	{
	private:
		MessageType _messageType;
		std::shared_ptr<Core::IFrame> _processedFrame;

	public:
		Message(MessageType messageType, const std::shared_ptr<Core::IFrame>& processedFrame = nullptr)
			: _messageType(messageType)
			, _processedFrame(processedFrame)
		{
		}

		MessageType MessageType() const
		{
			return _messageType;
		}

		std::shared_ptr<Core::IFrame> ProcessedFrame() const
		{
			return _processedFrame;
		}
	};

}
#endif
