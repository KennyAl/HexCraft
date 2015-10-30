
#pragma once

#include "FModule.h"

namespace HexNoise
{

	class HEXNOISE_API FSelect : public FModule
	{

	public:

		FSelect();

		virtual double GetNoise(double X, double Y = 0.0, double Z = 0.0) const override;

		virtual int32 GetNumSubModules() const override
		{
			return 3;
		}

		inline void SetBounds(double Min, double Max);

	private:

		/** The bounds(~inclusive) in which the output of the selector module needs to be, to return the noise value of the first module */
		double BoundMin;
		double BoundMax;
	};
}

