#include "CCore.h"
#include "main.h"
#include "CStream.h"

uint8_t CStream::inputStreamData[STREAM_MAX_SIZE];
size_t CStream::inputStreamSize;
size_t CStream::inputStreamPosition;

uint8_t CStream::outputStreamData[STREAM_MAX_SIZE];
size_t CStream::outputStreamPosition;

void CStream::StartStream(void) {
	outputStreamPosition = 0;
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
	uint16_t lengthBE = ((length >> 8) & 0xFF) | ((length & 0xFF) << 8);

	Write(&lengthBE, sizeof(lengthBE));
	Write(value, length);
}

void CStream::Write(const void* value, size_t size) {
	if (size <= sizeof(outputStreamData) - outputStreamPosition) {
		memcpy(&outputStreamData[outputStreamPosition], value, size);
		outputStreamPosition += size;
	}
}

void CStream::SendStream(CPlayer* player) {
	functions->SendClientScriptData(player != nullptr ? player->GetID() : -1, outputStreamData, outputStreamPosition);

	outputStreamPosition = 0;
}

void CStream::LoadInput(const void* data, size_t size) {
	inputStreamSize = size > sizeof(inputStreamData) ? sizeof(inputStreamData) : size;
	inputStreamPosition = 0;

	memcpy(inputStreamData, data, inputStreamSize);
}

int CStream::ReadByte(void) {
	if (inputStreamPosition + sizeof(uint8_t) > inputStreamSize) {
		return 0;
	}

	return inputStreamData[inputStreamPosition++];
}

int CStream::ReadInt(void) {
	if (inputStreamPosition + sizeof(int) > inputStreamSize) {
		return 0;
	}

	int result = *(int*)&inputStreamData[inputStreamPosition];
	inputStreamPosition += sizeof(int);
	return result;
}

float CStream::ReadFloat(void) {
	if (inputStreamPosition + sizeof(float) > inputStreamSize) {
		return 0.0f;
	}

	float result = *(float*)&inputStreamData[inputStreamPosition];
	inputStreamPosition += sizeof(float);
	return result;
}

uint16_t CStream::ReadBEInt16(void) {
	if (inputStreamPosition + sizeof(uint16_t) > inputStreamSize) {
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
		return "";
	}

	length = length > 4095 ? 4095 : length;

	memcpy(result, &inputStreamData[inputStreamPosition], length);
	result[length] = '\0';

	return result;
}

void CStream::RegisterStream(void) {
	Class<CStream> c(v, "Stream");

	c
		.StaticFunc(_SC("StartStream"), &CStream::StartStream)
		.StaticFunc(_SC("WriteByte"), &CStream::WriteByte)
		.StaticFunc(_SC("WriteInt"), &CStream::WriteInt)
		.StaticFunc(_SC("WriteFloat"), &CStream::WriteFloat)
		.StaticFunc(_SC("WriteString"), &CStream::WriteString)
		.StaticFunc(_SC("ReadByte"), &CStream::ReadByte)
		.StaticFunc(_SC("ReadInt"), &CStream::ReadInt)
		.StaticFunc(_SC("ReadFloat"), &CStream::ReadFloat)
		.StaticFunc(_SC("ReadString"), &CStream::ReadString)
		.StaticFunc(_SC("SendStream"), &CStream::SendStream);

	RootTable(v).Bind(_SC("Stream"), c);
}
