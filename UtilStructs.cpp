#include "main.h"

// Convert a Vector to string
const std::string Vector::ToString()
{
	std::basic_stringstream<SQChar> out;
	out << _SC("(") << this->x << _SC(", ") << this->y << _SC(", ") << this->z << _SC(")");

	return out.str();
}

// Convert a Quaternion to string
const std::string Quaternion::ToString()
{
	std::basic_stringstream<SQChar> out;
	out << _SC("(") << this->x << _SC(", ") << this->y << _SC(", ") << this->z << _SC(", ") << this->w << _SC(")");

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
Vector& Vector::operator =(const float f) { this->x = 0.0f; this->y = 0.0f; this->z = f; return *this; }

bool Quaternion::operator ==(const Quaternion &q) const { return this->w == q.w && this->x == q.x && this->y == q.y && this->z == q.z; }
Quaternion Quaternion::operator -(void) const { return Quaternion(-w, -x, -y, -z); }
Quaternion Quaternion::operator +(const Quaternion &q) const { return Quaternion(this->w + q.w, this->x + q.x, this->y + q.y, this->z + q.z); }
Quaternion Quaternion::operator -(const Quaternion &q) const { return Quaternion(this->w - q.w, this->x - q.x, this->y - q.y, this->z - q.z); }
Quaternion Quaternion::operator *(const float f) const { return Quaternion(this->w * f, this->x * f, this->y * f, this->z * f); }
Quaternion Quaternion::operator /(const float f) const { return Quaternion(this->w / f, this->x / f, this->y / f, this->z / f); }
Quaternion& Quaternion::operator =(const Quaternion &q) { this->w = q.w; this->x = q.x; this->y = q.y; this->z = q.z; return *this; }
Quaternion& Quaternion::operator =(const float q) { this->w = 0.0f; this->x = 0.0f; this->y = 0.0f; this->z = q; return *this; }

unsigned int RGBa::toUInt() { return this->r << 24 | this->g << 16 | this->b << 8 | this->a; }
unsigned int cRGB::toUInt() { return this->r << 16 | this->g << 8 | this->b; }
unsigned int ARGB::toUInt() { return this->a << 24 | this->r << 16 | this->g << 8 | this->b; }

EntityVector EntityVector::operator -(void) const { return EntityVector(this->m_nEntityId, this->m_nEntityType, this->m_nFlags, -x, -y, -z); }
EntityVector EntityVector::operator -(const Vector &v) const { return EntityVector(this->m_nEntityId, this->m_nEntityType, this->m_nFlags, this->x - v.x, this->y - v.y, this->z - v.z); }
EntityVector EntityVector::operator +(const Vector &v) const { return EntityVector(this->m_nEntityId, this->m_nEntityType, this->m_nFlags, this->x + v.x, this->y + v.y, this->z + v.z); }
EntityVector EntityVector::operator *(const float f) const { return EntityVector(this->m_nEntityId, this->m_nEntityType, this->m_nFlags, this->x * f, this->y * f, this->z * f); }
EntityVector EntityVector::operator /(const float f) const { return EntityVector(this->m_nEntityId, this->m_nEntityType, this->m_nFlags, this->x / f, this->y / f, this->z / f); }

void EntityVector::SetX(float fX)
{
	this->x = fX;
	switch (this->m_nEntityType)
	{
		case ENTITY_PLAYER:
			switch (m_nFlags)
			{
				case PLRVECTOR_POS: functions->SetPlayerPos(this->m_nEntityId, fX, this->y, this->z); break;
				case PLRVECTOR_SPEED: functions->SetPlayerSpeed(this->m_nEntityId, fX, this->y, this->z); break;
			}
			break;

		case ENTITY_VEHICLE:
			switch (m_nFlags)
			{
				case VEHVECTOR_POS: functions->SetVehiclePos(this->m_nEntityId, fX, this->y, this->z, 0); break;
				case VEHVECTOR_SPAWNPOS: functions->SetVehicleSpawnPos(this->m_nEntityId, fX, this->y, this->z, 0.0f); break;
				case VEHVECTOR_ANGLE: functions->SetVehicleRotEuler(this->m_nEntityId, fX, this->y, this->z); break;
				case VEHVECTOR_SPAWNANGLE: functions->SetVehicleSpawnRotEuler(this->m_nEntityId, fX, this->y, this->z); break;
				case VEHVECTOR_SPEED: functions->SetVehicleSpeed(this->m_nEntityId, fX, this->y, this->z); break;
				case VEHVECTOR_RELSPEED: functions->SetVehicleRelSpeed(this->m_nEntityId, fX, this->y, this->z); break;
				case VEHVECTOR_TURNSPEED: functions->SetVehicleTurnSpeed(this->m_nEntityId, fX, this->y, this->z); break;
				case VEHVECTOR_RELTURNSPEED: functions->SetVehicleRelTurnSpeed(this->m_nEntityId, fX, this->y, this->z); break;
			}
			break;

		case ENTITY_PICKUP: functions->PickupSetPos(this->m_nEntityId, fX, this->y, this->z); break;
		case ENTITY_OBJECT:
			switch (m_nFlags)
			{
				case OBJVECTOR_POS: functions->SetObjectPos(this->m_nEntityId, fX, this->y, this->z); break;
				case OBJVECTOR_ROTATION: functions->RotObjectToEuler(this->m_nEntityId, fX, this->y, this->z, 0); break;
			}
			break;

		case ENTITY_CHECKPOINT: functions->SetCheckpointPos(this->m_nEntityId, fX, this->y, this->z); break;
		case ENTITY_SPHERE: functions->SetSpherePos(this->m_nEntityId, fX, this->y, this->z); break;
	}
}

void EntityVector::SetY(float fY)
{
	this->y = fY;
	switch (this->m_nEntityType)
	{
		case ENTITY_PLAYER:
			switch (m_nFlags)
			{
				case PLRVECTOR_POS: functions->SetPlayerPos(this->m_nEntityId, this->x, fY, this->z); break;
				case PLRVECTOR_SPEED: functions->SetPlayerSpeed(this->m_nEntityId, this->x, fY, this->z); break;
			}
			break;

		case ENTITY_VEHICLE:
			switch (m_nFlags)
			{
				case VEHVECTOR_POS: functions->SetVehiclePos(this->m_nEntityId, this->x, fY, this->z, 0); break;
				case VEHVECTOR_SPAWNPOS: functions->SetVehicleSpawnPos(this->m_nEntityId, this->x, fY, this->z, 0.0f); break;
				case VEHVECTOR_ANGLE: functions->SetVehicleRotEuler(this->m_nEntityId, this->x, fY, this->z); break;
				case VEHVECTOR_SPAWNANGLE: functions->SetVehicleSpawnRotEuler(this->m_nEntityId, this->x, fY, this->z); break;
				case VEHVECTOR_SPEED: functions->SetVehicleSpeed(this->m_nEntityId, this->x, fY, this->z); break;
				case VEHVECTOR_RELSPEED: functions->SetVehicleRelSpeed(this->m_nEntityId, this->x, fY, this->z); break;
				case VEHVECTOR_TURNSPEED: functions->SetVehicleTurnSpeed(this->m_nEntityId, this->x, fY, this->z); break;
				case VEHVECTOR_RELTURNSPEED: functions->SetVehicleRelTurnSpeed(this->m_nEntityId, this->x, fY, this->z); break;
			}
			break;

		case ENTITY_PICKUP: functions->PickupSetPos(this->m_nEntityId, this->x, fY, this->z); break;
		case ENTITY_OBJECT:
			switch (m_nFlags)
			{
				case OBJVECTOR_POS: functions->SetObjectPos(this->m_nEntityId, this->x, fY, this->z); break;
				case OBJVECTOR_ROTATION: functions->RotObjectToEuler(this->m_nEntityId, this->x, fY, this->z, 0); break;
			}
			break;

		case ENTITY_CHECKPOINT: functions->SetCheckpointPos(this->m_nEntityId, this->x, fY, this->z); break;
		case ENTITY_SPHERE: functions->SetSpherePos(this->m_nEntityId, this->x, fY, this->z); break;
	}
}

void EntityVector::SetZ(float fZ)
{
	this->z = fZ;
	switch (this->m_nEntityType)
	{
		case ENTITY_PLAYER:
			switch (m_nFlags)
			{
				case PLRVECTOR_POS: functions->SetPlayerPos(this->m_nEntityId, this->x, this->y, fZ); break;
				case PLRVECTOR_SPEED: functions->SetPlayerSpeed(this->m_nEntityId, this->x, this->y, fZ); break;
			}
			break;

		case ENTITY_VEHICLE:
			switch (m_nFlags)
			{
				case VEHVECTOR_POS: functions->SetVehiclePos(this->m_nEntityId, this->x, this->y, fZ, 0); break;
				case VEHVECTOR_SPAWNPOS: functions->SetVehicleSpawnPos(this->m_nEntityId, this->x, this->y, fZ, 0.0f); break;
				case VEHVECTOR_ANGLE: functions->SetVehicleRotEuler(this->m_nEntityId, this->x, this->y, fZ); break;
				case VEHVECTOR_SPAWNANGLE: functions->SetVehicleSpawnRotEuler(this->m_nEntityId, this->x, this->y, fZ); break;
				case VEHVECTOR_SPEED: functions->SetVehicleSpeed(this->m_nEntityId, this->x, this->y, fZ); break;
				case VEHVECTOR_RELSPEED: functions->SetVehicleRelSpeed(this->m_nEntityId, this->x, this->y, fZ); break;
				case VEHVECTOR_TURNSPEED: functions->SetVehicleTurnSpeed(this->m_nEntityId, this->x, this->y, fZ); break;
				case VEHVECTOR_RELTURNSPEED: functions->SetVehicleRelTurnSpeed(this->m_nEntityId, this->x, this->y, fZ); break;
			}
			break;

		case ENTITY_PICKUP: functions->PickupSetPos(this->m_nEntityId, this->x, this->y, fZ); break;
		case ENTITY_OBJECT:
			switch (m_nFlags)
			{
				case OBJVECTOR_POS: functions->SetObjectPos(this->m_nEntityId, this->x, this->y, fZ); break;
				case OBJVECTOR_ROTATION: functions->RotObjectToEuler(this->m_nEntityId, this->x, this->y, fZ, 0); break;
			}
			break;

		case ENTITY_CHECKPOINT: functions->SetCheckpointPos(this->m_nEntityId, this->x, this->y, fZ); break;
		case ENTITY_SPHERE: functions->SetSpherePos(this->m_nEntityId, this->x, this->y, fZ); break;
	}
}

EntityQuaternion EntityQuaternion::operator -(void) const { return EntityQuaternion(this->m_nEntityId, this->m_nEntityType, this->m_nFlags, -x, -y, -z, -w); }
EntityQuaternion EntityQuaternion::operator -(const Quaternion &v) const { return EntityQuaternion(this->m_nEntityId, this->m_nEntityType, this->m_nFlags, this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w); }
EntityQuaternion EntityQuaternion::operator +(const Quaternion &v) const { return EntityQuaternion(this->m_nEntityId, this->m_nEntityType, this->m_nFlags, this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w); }
EntityQuaternion EntityQuaternion::operator *(const float f) const { return EntityQuaternion(this->m_nEntityId, this->m_nEntityType, this->m_nFlags, this->x * f, this->y * f, this->z * f, this->w * f); }
EntityQuaternion EntityQuaternion::operator /(const float f) const { return EntityQuaternion(this->m_nEntityId, this->m_nEntityType, this->m_nFlags, this->x / f, this->y / f, this->z / f, this->w / f); }

void EntityQuaternion::SetX(float fX)
{
	this->x = fX;
	switch (this->m_nEntityType)
	{
		case ENTITY_VEHICLE:
			switch (this->m_nFlags)
			{
				case VEHQUAT_ANGLE: functions->SetVehicleRot(this->m_nEntityId, fX, this->y, this->z, this->w); break;
				case VEHQUAT_SPAWNANGLE: functions->SetVehicleSpawnRot(this->m_nEntityId, fX, this->y, this->z, this->w); break;
			}
			break;

		case ENTITY_OBJECT: functions->RotObjectTo(this->m_nEntityId, fX, this->y, this->z, this->w, 0); break;
	}
}

void EntityQuaternion::SetY(float fY)
{
	this->y = fY;
	switch (this->m_nEntityType)
	{
		case ENTITY_VEHICLE:
			switch (this->m_nFlags)
			{
				case VEHQUAT_ANGLE: functions->SetVehicleRot(this->m_nEntityId, this->x, fY, this->z, this->w); break;
				case VEHQUAT_SPAWNANGLE: functions->SetVehicleSpawnRot(this->m_nEntityId, this->x, fY, this->z, this->w); break;
			}
			break;

		case ENTITY_OBJECT: functions->RotObjectTo(this->m_nEntityId, this->x, fY, this->z, this->w, 0); break;
	}
}

void EntityQuaternion::SetZ(float fZ)
{
	this->z = fZ;
	switch (this->m_nEntityType)
	{
		case ENTITY_VEHICLE:
			switch (this->m_nFlags)
			{
				case VEHQUAT_ANGLE: functions->SetVehicleRot(this->m_nEntityId, this->x, this->y, fZ, this->w); break;
				case VEHQUAT_SPAWNANGLE: functions->SetVehicleSpawnRot(this->m_nEntityId, this->x, this->y, fZ, this->w); break;
			}
			break;

		case ENTITY_OBJECT: functions->RotObjectTo(this->m_nEntityId, this->x, this->y, fZ, this->w, 0); break;
	}
}

void EntityQuaternion::SetW(float fW)
{
	this->w = fW;
	switch (this->m_nEntityType)
	{
		case ENTITY_VEHICLE:
			switch (this->m_nFlags)
			{
				case VEHQUAT_ANGLE: functions->SetVehicleRot(this->m_nEntityId, this->x, this->y, this->z, fW); break;
				case VEHQUAT_SPAWNANGLE: functions->SetVehicleSpawnRot(this->m_nEntityId, this->x, this->y, this->z, fW); break;
			}
			break;

		case ENTITY_OBJECT: functions->RotObjectTo(this->m_nEntityId, this->x, this->y, this->z, fW, 0); break;
	}
}

void EntityRGB::SetR(int nR)
{
	this->r = nR;
	switch (this->m_nEntityType)
	{
		case ENTITY_PLAYER: functions->SetPlayerColour(this->m_nEntityId, toUInt()); break;
	}
}

void EntityRGB::SetG(int nG)
{
	this->g = nG;
	switch (this->m_nEntityType)
	{
		case ENTITY_PLAYER: functions->SetPlayerColour(this->m_nEntityId, toUInt()); break;
	}
}

void EntityRGB::SetB(int nB)
{
	this->b = nB;
	switch (this->m_nEntityType)
	{
		case ENTITY_PLAYER: functions->SetPlayerColour(this->m_nEntityId, toUInt()); break;
	}
}

void RegisterStructures()
{
    Sqrat::RootTable().Bind(_SC("Vector"), Sqrat::Class<Vector>(Sqrat::DefaultVM::Get(), _SC("Vector"))
        .Ctor<float, float, float>()

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

        .Func(_SC("_tostring"), &Vector::ToString)
    );

    Sqrat::RootTable().Bind(_SC("Quaternion"), Sqrat::Class<Quaternion>(Sqrat::DefaultVM::Get(), _SC("Quaternion"))
        .Ctor<float, float, float, float>()

        .Var(_SC("w"), &Quaternion::w)
        .Var(_SC("x"), &Quaternion::x)
        .Var(_SC("y"), &Quaternion::y)
        .Var(_SC("z"), &Quaternion::z)

        .Func(_SC("_add"), &Quaternion::operator +)
        .Func(_SC("_mul"), &Quaternion::operator *)
        .Func(_SC("_div"), &Quaternion::operator /)
        .Func<Quaternion(Quaternion::*)(void) const>(_SC("_unm"), &Quaternion::operator -)
        .Func<Quaternion(Quaternion::*)(const Quaternion&) const>(_SC("_sub"), &Quaternion::operator -)

        .Func(_SC("_tostring"), &Quaternion::ToString)
    );


    Sqrat::RootTable().Bind(_SC("RGBa"), Sqrat::Class<RGBa>(Sqrat::DefaultVM::Get(), _SC("RGBa"))
        .Ctor<int, int, int, int>()

        .Var(_SC("r"), &RGBa::r)
        .Var(_SC("g"), &RGBa::g)
        .Var(_SC("b"), &RGBa::b)
        .Var(_SC("a"), &RGBa::a)
    );


    Sqrat::RootTable().Bind(_SC("cRGB"), Sqrat::Class<cRGB>(Sqrat::DefaultVM::Get(), _SC("cRGB"))
        .Ctor<int, int, int>()

        .Var(_SC("r"), &cRGB::r)
        .Var(_SC("g"), &cRGB::g)
        .Var(_SC("b"), &cRGB::b)
    );


    Sqrat::RootTable().Bind(_SC("Bounds"), Sqrat::Class<Bounds>(Sqrat::DefaultVM::Get(), _SC("Bounds"))
        .Ctor<float, float, float, float>()

        .Var(_SC("MaxX"), &Bounds::maxX)
        .Var(_SC("MinX"), &Bounds::minX)
        .Var(_SC("MaxY"), &Bounds::maxY)
        .Var(_SC("MinY"), &Bounds::minY)
    );

    Sqrat::RootTable().Bind(_SC("WastedSettings"), Sqrat::Class<WastedSettings>(Sqrat::DefaultVM::Get(), _SC("WastedSettings"))
        .Ctor<int, int, float, float, cRGB, int, int>()

        .Var(_SC("DeathTime"), &WastedSettings::deathTime)
        .Var(_SC("FadeTime"), &WastedSettings::fadeTime)
        .Var(_SC("FadeInSpeed"), &WastedSettings::fadeInSpeed)
        .Var(_SC("FadeOutSpeed"), &WastedSettings::fadeOutSpeed)
        .Var(_SC("FadeColour"), &WastedSettings::fadeColour)
        .Var(_SC("CorpseFadeDelay"), &WastedSettings::corpseFadeDelay)
        .Var(_SC("CorpseFadeTime"), &WastedSettings::corpseFadeTime)
    );

    Sqrat::RootTable().Bind(_SC("ARGB"), Sqrat::Class<ARGB>(Sqrat::DefaultVM::Get(), _SC("ARGB"))
        .Ctor<int, int, int, int>()

        .Var(_SC("a"), &ARGB::a)
        .Var(_SC("r"), &ARGB::r)
        .Var(_SC("g"), &ARGB::g)
        .Var(_SC("b"), &ARGB::b)
    );

    Sqrat::RootTable().Bind(_SC("EntityVector"), Sqrat::Class<EntityVector>(Sqrat::DefaultVM::Get(), _SC("EntityVector"))
        .Ctor<int, int, int, float, float, float>()

        .Prop(_SC("x"), &EntityVector::GetX, &EntityVector::SetX)
        .Prop(_SC("y"), &EntityVector::GetY, &EntityVector::SetY)
        .Prop(_SC("z"), &EntityVector::GetZ, &EntityVector::SetZ)

        .Func(_SC("Distance"), &EntityVector::Distance)
        .Func(_SC("Dot"), &EntityVector::Dot)
        .Func(_SC("Length"), &EntityVector::Length)
        .Func(_SC("Normalize"), &EntityVector::Normalize)

        .Func(_SC("_add"), &EntityVector::operator +)
        .Func(_SC("_mul"), &EntityVector::operator *)
        .Func(_SC("_div"), &EntityVector::operator /)
        .Func<EntityVector(EntityVector::*)(void) const>(_SC("_unm"), &EntityVector::operator -)
        .Func<EntityVector(EntityVector::*)(const Vector&) const>(_SC("_sub"), &EntityVector::operator -)

        .Func(_SC("_tostring"), &Vector::ToString)
    );

    Sqrat::RootTable().Bind(_SC("EntityQuaternion"), Sqrat::Class<EntityQuaternion>(Sqrat::DefaultVM::Get(), _SC("EntityQuaternion"))
        .Ctor<int, int, int, float, float, float, float>()

        .Prop(_SC("w"), &EntityQuaternion::GetW, &EntityQuaternion::SetW)
        .Prop(_SC("x"), &EntityQuaternion::GetX, &EntityQuaternion::SetX)
        .Prop(_SC("y"), &EntityQuaternion::GetY, &EntityQuaternion::SetY)
        .Prop(_SC("z"), &EntityQuaternion::GetZ, &EntityQuaternion::SetZ)

        .Func(_SC("_add"), &EntityQuaternion::operator +)
        .Func(_SC("_mul"), &EntityQuaternion::operator *)
        .Func(_SC("_div"), &EntityQuaternion::operator /)
        .Func<EntityQuaternion(EntityQuaternion::*)(void) const>(_SC("_unm"), &EntityQuaternion::operator -)
        .Func<EntityQuaternion(EntityQuaternion::*)(const Quaternion&) const>(_SC("_sub"), &EntityQuaternion::operator -)

        .Func(_SC("_tostring"), &EntityQuaternion::ToString)
    );

    Sqrat::RootTable().Bind(_SC("EntityRGB"), Sqrat::Class<EntityRGB>(Sqrat::DefaultVM::Get(), _SC("EntityRGB"))
        .Ctor<int, int, int, int, int, int>()

        .Prop(_SC("r"), &EntityRGB::GetR, &EntityRGB::SetR)
        .Prop(_SC("g"), &EntityRGB::GetG, &EntityRGB::SetG)
        .Prop(_SC("b"), &EntityRGB::GetB, &EntityRGB::SetB)
    );
}
