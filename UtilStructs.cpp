#include "main.h"

// Convert a Vector to string
const Sqrat::string VectorToString(const Vector* v)
{
	std::basic_stringstream<SQChar> out;
	out << _SC("(") << v->x << _SC(", ") << v->y << _SC(", ") << v->z << _SC(")");

	return out.str();
}

// Convert a Quaternion to string
const Sqrat::string QuaternionToString(const Quaternion* q)
{
	std::basic_stringstream<SQChar> out;
	out << _SC("(") << q->w << _SC(", ") << q->x << _SC(", ") << q->y << _SC(", ") << q->z << _SC(")");

	return out.str();
}

float Vector::Length(void) const { return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)); }
float Vector::Distance(const Vector &v) const { return sqrt(pow(this->x - v.x, 2) + pow(this->y - v.y, 2) + pow(this->z - v.z, 2)); }
float Vector::Dot(const Vector &v) { return (this->x * v.x) + (this->y * v.y) + (this->z * v.z); }
Vector& Vector::Normalize(void)
{
	float invLen = 1.0f / this->Length();
	this->x *= invLen;
	this->y *= invLen;
	this->z *= invLen;
	return *this;
}

bool Vector::operator ==(const Vector &v) const { return this->x == v.x && this->y == v.y && this->z == v.z; }
Vector Vector::operator -(void) const { return Vector(-x, -y, -z); }
Vector Vector::operator +(const Vector &v) const { return Vector(this->x + v.x, this->y + v.y, this->z + v.z); }
Vector Vector::operator -(const Vector &v) const { return Vector(this->x - v.x, this->y - v.y, this->z - v.z); }
Vector Vector::operator *(const float f) const { return Vector(this->x * f, this->y * f, this->z * f); }
Vector Vector::operator /(const float f) const { return Vector(this->x / f, this->y / f, this->z / f); }
Vector& Vector::operator =(const Vector &v) { this->x = v.x; this->y = v.y; this->z = v.z; return *this; }

bool Quaternion::operator ==(const Quaternion &q) const { return this->w == q.w && this->x == q.x && this->y == q.y && this->z == q.z; }
Quaternion Quaternion::operator -(void) const { return Quaternion(-w, -x, -y, -z); }
Quaternion Quaternion::operator +(const Quaternion &q) const { return Quaternion(this->w + q.w, this->x + q.x, this->y + q.y, this->z + q.z); }
Quaternion Quaternion::operator -(const Quaternion &q) const { return Quaternion(this->w - q.w, this->x - q.x, this->y - q.y, this->z - q.z); }
Quaternion Quaternion::operator *(const float f) const { return Quaternion(this->w * f, this->x * f, this->y * f, this->z * f); }
Quaternion Quaternion::operator /(const float f) const { return Quaternion(this->w / f, this->x / f, this->y / f, this->z / f); }
Quaternion& Quaternion::operator =(const Quaternion &q) { this->w = q.w; this->x = q.x; this->y = q.y; this->z = q.z; return *this; }

unsigned int RGBa::toUInt() { return this->r << 24 | this->g << 16 | this->b << 8 | this->a; }
unsigned int cRGB::toUInt() { return this->r << 16 | this->g << 8 | this->b; }
unsigned int ARGB::toUInt() { return this->a << 24 | this->r << 16 | this->g << 8 | this->b; }

void RegisterStructures()
{
	Class<Vector> a;
	Class<Quaternion> b;
	Class<RGBa> c;
	Class<cRGB> d;
	Class<Bounds> e;
	Class<WastedSettings> f;
	Class<ARGB> g;

	a.Ctor<float, float, float>();
	a.Ctor<int, int, int>();

	b.Ctor<float, float, float, float>();
	b.Ctor<int, int, int, int>();

	e.Ctor<float, float, float, float>();
	e.Ctor<int, int, int, int>();

	// Because an unsigned char is crashy
	c.Ctor<int, int, int, int>();
	d.Ctor<int, int, int>();
	f.Ctor<int, int, float, float, cRGB, int, int>();
	g.Ctor<int, int, int, int>();

	a
		.Var(_SC("x"), &Vector::x)
		.Var(_SC("y"), &Vector::y)
		.Var(_SC("z"), &Vector::z)

		.Func(_SC("Distance"), &Vector::Distance)
		.Func(_SC("Dot"), &Vector::Dot)
		.Func(_SC("Length"), &Vector::Length)
		.Func(_SC("Normalize"), &Vector::Normalize)

		.Func(_SC("_add"), &Vector::operator +)
		.Func(_SC("_mul"), &Vector::operator *)
		.Func(_SC("_div"), &Vector::operator /)
		.Func<Vector(Vector::*)(void) const>(_SC("_unm"), &Vector::operator -)
		.Func<Vector(Vector::*)(const Vector&) const>(_SC("_sub"), &Vector::operator -)

		.GlobalFunc(_SC("_tostring"), &VectorToString);

	b
		.Var(_SC("w"), &Quaternion::w)
		.Var(_SC("x"), &Quaternion::x)
		.Var(_SC("y"), &Quaternion::y)
		.Var(_SC("z"), &Quaternion::z)

		.Func(_SC("_add"), &Quaternion::operator +)
		.Func(_SC("_mul"), &Quaternion::operator *)
		.Func(_SC("_div"), &Quaternion::operator /)
		.Func<Quaternion(Quaternion::*)(void) const>(_SC("_unm"), &Quaternion::operator -)
		.Func<Quaternion(Quaternion::*)(const Quaternion&) const>(_SC("_sub"), &Quaternion::operator -)

		.GlobalFunc(_SC("_tostring"), &QuaternionToString);

	c
		.Var(_SC("r"), &RGBa::r)
		.Var(_SC("g"), &RGBa::g)
		.Var(_SC("b"), &RGBa::b)
		.Var(_SC("a"), &RGBa::a);

	d
		.Var(_SC("r"), &cRGB::r)
		.Var(_SC("g"), &cRGB::g)
		.Var(_SC("b"), &cRGB::b);

	e
		.Var(_SC("MaxX"), &Bounds::maxX)
		.Var(_SC("MinX"), &Bounds::minX)
		.Var(_SC("MaxY"), &Bounds::maxY)
		.Var(_SC("MinY"), &Bounds::minY);

	f
		.Var(_SC("DeathTime"), &WastedSettings::deathTime)
		.Var(_SC("FadeTime"), &WastedSettings::fadeTime)
		.Var(_SC("FadeInSpeed"), &WastedSettings::fadeInSpeed)
		.Var(_SC("FadeOutSpeed"), &WastedSettings::fadeOutSpeed)
		.Var(_SC("FadeColour"), &WastedSettings::fadeColour)
		.Var(_SC("CorpseFadeDelay"), &WastedSettings::corpseFadeDelay)
		.Var(_SC("CorpseFadeTime"), &WastedSettings::corpseFadeTime);

	g
		.Var(_SC("a"), &ARGB::a)
		.Var(_SC("r"), &ARGB::r)
		.Var(_SC("g"), &ARGB::g)
		.Var(_SC("b"), &ARGB::b);

	RootTable(v).Bind(_SC("Vector"), a);
	RootTable(v).Bind(_SC("Quaternion"), b);
	RootTable(v).Bind(_SC("RGBA"), c);
	RootTable(v).Bind(_SC("RGB"), d);
	RootTable(v).Bind(_SC("Bounds"), e);
	RootTable(v).Bind(_SC("WastedSettings"), f);
	RootTable(v).Bind(_SC("ARGB"), g);
}