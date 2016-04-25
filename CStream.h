#pragma once
#include <stdlib.h>
#include "sqrat.h"

#define STREAM_MAX_SIZE 4096

class CStream {
public:
	static void StartStream(void);
	static void WriteByte(int value);
	static void WriteInt(int value);
	static void WriteFloat(float value);
	static void WriteString(SQChar* value);
	static void Write(const void* value, size_t size);
	static void SendStream(CPlayer* player);

	static void LoadInput(const void* data, size_t size);
	static int ReadByte(void);
	static int ReadInt(void);
	static float ReadFloat(void);
	static SQChar* ReadString(void);

	static void RegisterStream(void);

private:

	static uint16_t ReadBEInt16(void);

	static uint8_t inputStreamData[STREAM_MAX_SIZE];
	static size_t inputStreamSize;
	static size_t inputStreamPosition;

	static uint8_t outputStreamData[STREAM_MAX_SIZE];
	static size_t outputStreamPosition;
};
