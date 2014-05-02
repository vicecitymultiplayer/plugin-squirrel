// ha. hahahahahah. ahahahahahahahahahaha
#ifdef WIN32
	#pragma warning( disable : 4244 )
#endif

// Structure definitions
#pragma once
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