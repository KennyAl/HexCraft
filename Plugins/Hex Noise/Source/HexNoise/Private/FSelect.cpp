
#include "HexNoisePrivatePCH.h"
#include "FSelect.h"


using namespace HexNoise;

FSelect::FSelect()
	:FModule(GetNumSubModules())
{
	BoundMin = 0;
	BoundMax = 1;
}

double FSelect::GetNoise(double X, double Y, double Z) const
{
	double SelectorNoise = SubModules[2]->GetNoise(X, Y, Z);
	if (SelectorNoise >= BoundMin && SelectorNoise <= BoundMax)
	{
		return SubModules[0]->GetNoise(X, Y, Z);
	}
	else
	{
		return SubModules[1]->GetNoise(X, Y, Z);
	}
}

void FSelect::SetBounds(double Min, double Max)
{
#ifdef CHECKS_ENALBED
	assert(Min < Max);
#endif

	BoundMin = Min;
	BoundMax = Max;
}
