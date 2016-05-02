#include "CCore.h"
#include "main.h"
#include "CStream.h"

uint8_t CStream::inputStreamData[STREAM_MAX_SIZE];
size_t CStream::inputStreamSize;
size_t CStream::inputStreamPosition;
bool CStream::inputStreamError;

uint8_t CStream::outputStreamData[STREAM_MAX_SIZE];
size_t CStream::outputStreamEnd;
size_t CStream::outputStreamPosition;
bool CStream::outputStreamError;

void CStream::StartWrite(void) {
	outputStreamPosition = 0;
	outputStreamEnd = 0;
	outputStreamError = false;
}

void CStream::SetWritePosition(int position) {
	if (position < 0 || position > outputStreamEnd) {
		position = outputStreamEnd;
	}

	outputStreamPosition = position;
}

int CStream::GetWritePosition(void) {
	return (int)outputStreamPosition;
}

int CStream::GetWriteSize(void) {
	return (int)outputStreamEnd;
}

bool CStream::HasWriteError(void) {
	return outputStreamError;
}

void CStream::WriteByte(int value) {
	uint8_t data = (uint8_t)value;

	Write(&data, sizeof(data));
}

void CStream::WriteInt(int value) {
	Write(&value, sizeof(value));
}

void CStream::WriteFloat(float value) {
	Write(&value, sizeof(value));
}

void CStream::WriteString(SQChar* value) {
	if (value == nullptr) {
		return;
	}

	size_t size = strlen(value);
	uint16_t length = size > UINT16_MAX ? UINT16_MAX : (uint16_t)size;

	if (CanWrite(sizeof(length))) {
		if (!CanWrite(length)) {
			length = sizeof(outputStreamData) - outputStreamPosition;

			outputStreamError = true;
		}

		uint16_t lengthBE = ((length >> 8) & 0xFF) | ((length & 0xFF) << 8);

		Write(&lengthBE, sizeof(lengthBE));
		Write(value, length);
	}
}

bool CStream::CanWrite(size_t size) {
	return size <= sizeof(outputStreamData) - outputStreamPosition;
}

void CStream::Write(const void* value, size_t size) {
	if (CanWrite(size)) {
		memcpy(&outputStreamData[outputStreamPosition], value, size);
		outputStreamPosition += size;

		if (outputStreamPosition > outputStreamEnd) {
			outputStreamEnd = outputStreamPosition;
		}
	}
	else {
		outputStreamError = true;
	}
}

void CStream::SendStream(CPlayer* player) {
	functions->SendClientScriptData(player != nullptr ? player->GetID() : -1, outputStreamData, outputStreamEnd);

	outputStreamPosition = 0;
	outputStreamEnd = 0;
	outputStreamError = false;
}

void CStream::LoadInput(const void* data, size_t size) {
	inputStreamSize = size > sizeof(inputStreamData) ? sizeof(inputStreamData) : size;
	inputStreamPosition = 0;
	inputStreamError = false;

	memcpy(inputStreamData, data, inputStreamSize);
}

void CStream::SetReadPosition(int position) {
	if (position < 0 || position > inputStreamPosition) {
		position = inputStreamSize;
	}

	inputStreamPosition = position;
}

int CStream::GetReadPosition(void) {
	return (int)inputStreamPosition;
}

int CStream::GetReadSize(void) {
	return (int)inputStreamSize;
}

bool CStream::HasReadError(void) {
	return inputStreamError;
}

int CStream::ReadByte(void) {
	if (inputStreamPosition + sizeof(uint8_t) > inputStreamSize) {
		inputStreamError = true;
		return 0;
	}

	return inputStreamData[inputStreamPosition++];
}

int CStream::ReadInt(void) {
	if (inputStreamPosition + sizeof(int) > inputStreamSize) {
		inputStreamError = true;
		return 0;
	}

	int result = *(int*)&inputStreamData[inputStreamPosition];
	inputStreamPosition += sizeof(int);
	return result;
}

float CStream::ReadFloat(void) {
	if (inputStreamPosition + sizeof(float) > inputStreamSize) {
		inputStreamError = true;
		return 0.0f;
	}

	float result = *(float*)&inputStreamData[inputStreamPosition];
	inputStreamPosition += sizeof(float);
	return result;
}

uint16_t CStream::ReadBEInt16(void) {
	if (inputStreamPosition + sizeof(uint16_t) > inputStreamSize) {
		inputStreamError = true;
		return 0;
	}

	uint16_t result = *(int16_t*)&inputStreamData[inputStreamPosition];
	inputStreamPosition += sizeof(uint16_t);
	return ((result >> 8) & 0xFF) | ((result & 0xFF) << 8);
}

SQChar* CStream::ReadString(void) {
	static char result[4096];

	uint16_t length = ReadBEInt16();

	if (inputStreamPosition + length > inputStreamSize) {
		length = inputStreamSize - inputStreamPosition;
		inputStreamError = true;
	}

	length = length > 4095 ? 4095 : length;

	memcpy(result, &inputStreamData[inputStreamPosition], length);
	result[length] = '\0';

	inputStreamPosition += length;

	return result;
}

void CStream::RegisterStream(void) {
	Class<CStream> c(v, "Stream");

	c
		.StaticFunc(_SC("StartWrite"), &CStream::StartWrite)
		.StaticFunc(_SC("SetWritePosition"), &CStream::SetWritePosition)
		.StaticFunc(_SC("GetWritePosition"), &CStream::GetWritePosition)
		.StaticFunc(_SC("GetWriteSize"), &CStream::GetWriteSize)
		.StaticFunc(_SC("HasWriteError"), &CStream::HasWriteError)
		.StaticFunc(_SC("WriteByte"), &CStream::WriteByte)
		.StaticFunc(_SC("WriteInt"), &CStream::WriteInt)
		.StaticFunc(_SC("WriteFloat"), &CStream::WriteFloat)
		.StaticFunc(_SC("WriteString"), &CStream::WriteString)
		.StaticFunc(_SC("SendStream"), &CStream::SendStream)
		.StaticFunc(_SC("SetReadPosition"), &CStream::SetReadPosition)
		.StaticFunc(_SC("GetReadPosition"), &CStream::GetReadPosition)
		.StaticFunc(_SC("GetReadSize"), &CStream::GetReadSize)
		.StaticFunc(_SC("HasReadError"), &CStream::HasReadError)
		.StaticFunc(_SC("ReadByte"), &CStream::ReadByte)
		.StaticFunc(_SC("ReadInt"), &CStream::ReadInt)
		.StaticFunc(_SC("ReadFloat"), &CStream::ReadFloat)
		.StaticFunc(_SC("ReadString"), &CStream::ReadString);
		

	RootTable(v).Bind(_SC("Stream"), c);
}
