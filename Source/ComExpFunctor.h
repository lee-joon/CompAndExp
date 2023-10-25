/*
  ==============================================================================

    ComExpFunctor.h
    Created: 20 Jun 2023 1:12:08am
    Author:  JUNLEE

  ==============================================================================
*/

#pragma once

class CompExpFunctor {

public:
	float operator()(float Comp, float Exp)
	{
		if (0 > Comp)
		{
			return (Comp < Exp ? Comp : Exp);
		}
		else
		{
			return (0 < Exp ? 0 : Exp) * -1;
		}
	}
};
