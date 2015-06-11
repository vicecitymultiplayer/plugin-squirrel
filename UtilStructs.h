#pragma once
#include <string>

typedef enum
{
	ENTITY_PLAYER = 0,
	ENTITY_VEHICLE,
	ENTITY_PICKUP,
	ENTITY_OBJECT,
	ENTITY_CHECKPOINT,
	ENTITY_SPHERE
} Entity;

typedef enum
{
	PLRVECTOR_POS = 0,
	PLRVECTOR_SPEED
} PlayerVectorFlags;

typedef enum
{
	VEHVECTOR_POS = 0,
	VEHVECTOR_SPAWNPOS,
	VEHVECTOR_ANGLE,
	VEHVECTOR_SPAWNANGLE,
	VEHVECTOR_SPEED,
	VEHVECTOR_RELSPEED,
	VEHVECTOR_TURNSPEED,
	VEHVECTOR_RELTURNSPEED
} VehicleVectorFlags;

typedef enum
{
	OBJVECTOR_POS = 0,
	OBJVECTOR_ROTATION
} ObjectVectorFlags;

typedef enum
{
	VEHQUAT_ANGLE = 0,
	VEHQUAT_SPAWNANGLE
} VehicleQuatFlags;

class Vector
{
	public:
		Vector( float x, float y, float z ) { this->x = x; this->y = y; this->z = z; }
		Vector( int x, int y, int z ) { this->x = x; this->y = y; this->z = z; }
		Vector() { this->x = 0.0f; this->y = 0.0f; this->z = 0.0f; }
		float x;
		float y;
		float z;

		float Length(void) const;
		float Distance(const Vector &v) const;
		float Dot(const Vector &v);
		Vector& Normalize(void);

		bool operator ==(const Vector &v) const;
		Vector operator -(void) const;
		Vector operator +(const Vector &v) const;
		Vector operator -(const Vector &v) const;
		Vector operator *(const float f) const;
		Vector operator /(const float f) const;
		Vector& operator =(const Vector &v);
		Vector& operator =(const float f);

        int Cmp(const Vector &v) const;
		const std::string ToString();
};

class EntityVector : public Vector
{
	private:
		int m_nEntityId, m_nEntityType, m_nFlags;

	public:
		EntityVector(int nEntityId, int nEntityType, int nFlags, float x, float y, float z)
		{
			m_nEntityId = nEntityId;
			m_nEntityType = nEntityType;
			m_nFlags = nFlags;

			this->x = x;
			this->y = y;
			this->z = z;
		}

		EntityVector(int nEntityId, int nEntityType, int nFlags, int x, int y, int z)
		{
			m_nEntityId = nEntityId;
			m_nEntityType = nEntityType;
			m_nFlags = nFlags;

			this->x = x;
			this->y = y;
			this->z = z;
		}

		EntityVector()
		{
			m_nEntityId = -1;
			m_nEntityType = -1;
			m_nFlags = -1;

			this->x = 0.0f;
			this->y = 0.0f;
			this->z = 0.0f;
		}

		EntityVector operator -(void) const;
		EntityVector operator -(const Vector &v) const;
		EntityVector operator +(const Vector &v) const;
		EntityVector operator *(const float f) const;
		EntityVector operator /(const float f) const;

		// It would seem like this would cause a race condition but we only run in one thread
		// and the functions that would return an EntityVector create different Vectors
		// when they run anyway.
		float GetX() { return this->x; }
		float GetY() { return this->y; }
		float GetZ() { return this->z; }

		void SetX(float x);
		void SetY(float y);
		void SetZ(float z);
};

class Quaternion
{
	public:
		Quaternion( float x, float y, float z, float w ) { this->w = w; this->x = x; this->y = y; this->z = z; }
		Quaternion( int x, int y, int z, int w ) { this->w = w; this->x = x; this->y = y; this->z = z; }
		Quaternion() { this->w = 0.0f; this->x = 0.0f; this->y = 0.0f; this->z = 0.0f; }
		float w;
		float x;
		float y;
		float z;

		bool operator ==(const Quaternion &q) const;
		Quaternion operator -(void) const;
		Quaternion operator +(const Quaternion &q) const;
		Quaternion operator -(const Quaternion &q) const;
		Quaternion operator *(const float f) const;
		Quaternion operator /(const float f) const;
		Quaternion& operator =(const Quaternion &q);
		Quaternion& operator =(const float q);

        int Cmp(const Quaternion &q) const;
		const std::string ToString();
};

class EntityQuaternion : public Quaternion
{
private:
	int m_nEntityId, m_nEntityType, m_nFlags;

public:
	EntityQuaternion(int nEntityId, int nEntityType, int nFlags, float x, float y, float z, float w)
	{
		m_nEntityId = nEntityId;
		m_nEntityType = nEntityType;
		m_nFlags = nFlags;

		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	EntityQuaternion(int nEntityId, int nEntityType, int nFlags, int x, int y, int z, int w)
	{
		m_nEntityId = nEntityId;
		m_nEntityType = nEntityType;
		m_nFlags = nFlags;

		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	EntityQuaternion()
	{
		m_nEntityId = -1;
		m_nEntityType = -1;
		m_nFlags = -1;

		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->w = 0.0f;
	}

	EntityQuaternion operator -(void) const;
	EntityQuaternion operator -(const Quaternion &v) const;
	EntityQuaternion operator +(const Quaternion &v) const;
	EntityQuaternion operator *(const float f) const;
	EntityQuaternion operator /(const float f) const;

	float GetX() { return this->x; }
	float GetY() { return this->y; }
	float GetZ() { return this->z; }
	float GetW() { return this->w; }

	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	void SetW(float w);
};

class RGBa
{
	public:
		RGBa( int r, int g, int b, int a ) { this->r = r; this->g = g; this->b = b; this->a = a; }
		RGBa() { this->r = 0; this->g = 0; this->b = 0; this->a = 0; }

		int r;
		int g;
		int b;
		int a;

		unsigned int toUInt();
};

class cRGB
{
	public:
		cRGB( int r, int g, int b ) { this->r = r; this->g = g; this->b = b; }
		cRGB() { this->r = 0; this->g = 0; this->b = 0; }

		int r;
		int g;
		int b;

		unsigned int toUInt();
};

class EntityRGB : public cRGB
{
	private:
		int m_nEntityId, m_nEntityType, m_nFlags;

	public:
		EntityRGB(int nEntityId, int nEntityType, int nFlags, int r, int g, int b)
		{
			m_nEntityId = nEntityId;
			m_nEntityType = nEntityType;
			m_nFlags = nFlags;

			this->r = r;
			this->g = g;
			this->b = b;
		}

		EntityRGB()
		{
			m_nEntityId = -1;
			m_nEntityType = -1;
			m_nFlags = -1;

			this->r = 0;
			this->g = 0;
			this->b = 0;
		}

		int GetR() { return this->r; }
		int GetG() { return this->g; }
		int GetB() { return this->b; }

		void SetR(int r);
		void SetG(int g);
		void SetB(int b);
};

class ARGB
{
	public:
		ARGB( int a, int r, int g, int b ) { this->r = r; this->g = g; this->b = b; this->a = a; }
		ARGB() { this->a = 0; this->r = 0; this->g = 0; this->b = 0; }

		int a;
		int r;
		int g;
		int b;

		unsigned int toUInt();
};

class Bounds
{
	public:
		Bounds( float maxX, float minX, float maxY, float minY )
		{
			this->maxX = maxX;
			this->minX = minX;
			this->maxY = maxY;
			this->minY = minY;
		}

		Bounds( int maxX, int minX, int maxY, int minY )
		{
			this->maxX = maxX;
			this->minX = minX;
			this->maxY = maxY;
			this->minY = minY;
		}

		Bounds()
		{
			this->maxX = 0.0f;
			this->minX = 0.0f;
			this->maxY = 0.0f;
			this->minY = 0.0f;
		}

		float maxX;
		float minX;
		float maxY;
		float minY;
};

class WastedSettings
{
	public:
		WastedSettings
		(
			int deathTime,
			int fadeTime,
			float fadeInSpeed,
			float fadeOutSpeed,
			cRGB fadeColour,
			int corpseFadeDelay,
			int corpseFadeTime
		)
		{
			this->deathTime       = deathTime;
			this->fadeTime        = fadeTime;
			this->fadeInSpeed     = fadeInSpeed;
			this->fadeOutSpeed    = fadeOutSpeed;
			this->fadeColour      = fadeColour;
			this->corpseFadeDelay = corpseFadeDelay;
			this->corpseFadeTime  = corpseFadeTime;
		}

		WastedSettings()
		{
			this->deathTime = 0;
			this->fadeTime = 0;
			this->fadeInSpeed = 0.0f;
			this->fadeOutSpeed = 0.0f;
			this->fadeColour = cRGB(0, 0, 0);
			this->corpseFadeDelay = 0;
			this->corpseFadeTime = 0;
		}

		int deathTime;
		int fadeTime;
		float fadeInSpeed;
		float fadeOutSpeed;
		cRGB fadeColour;
		int corpseFadeDelay;
		int corpseFadeTime;
};

void RegisterStructures();
