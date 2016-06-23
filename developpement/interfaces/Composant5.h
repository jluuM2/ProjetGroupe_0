#pragma once
#ifndef COMPOSANT5_H
#define COMPOSANT5_H

#ifdef COMPOSANT5_EXPORTS
#define COMPOSANT5_INTERFACE __declspec(dllexport)
#else
#define COMPOSANT5_INTERFACE __declspec(dllimport)
#endif // COMPOSANT5_EXPORTS

#include "Bloc.h"

namespace cp5 {
	class Composant5 {
	public:
		static COMPOSANT5_INTERFACE bool nomFonctionComposant5(Bloc bloc);
	};
}
#endif