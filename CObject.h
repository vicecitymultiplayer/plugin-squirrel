#include "main.h"

#ifndef object
	class CObject
	{
		public:
			void SetWorld( int world );
			void SetPos( Vector pos );

		public:
			int GetModel();
			int GetAlpha();
			int GetWorld();
			Vector GetPos();
			Quaternion GetRotation();
			Vector GetRotationEuler();
			int GetID();

		public:
			void Delete();
			void MoveTo( Vector pos, int time );
			void MoveBy( Vector offset, int time );
			void RotateTo( Quaternion rotation, int time );
			void RotateBy( Quaternion rotOffset, int time );
			void RotateToEuler( Vector rotation, int time );
			void RotateByEuler( Vector rotOffset, int time );
			void SetAlpha( int alpha, int fadeTime );
			
		public:
			int nObjectId;
	};

	#define object
#endif

void RegisterObject();