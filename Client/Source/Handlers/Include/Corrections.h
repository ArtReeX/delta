//-- ******************************************* --//
//-- *************** Corrections *************** --//
//-- ******************************************* --//

#ifndef CORRECTIONSH
#define CORRECTIONSH

//-- ОНДЙКЧВЕМХЕ ХДЕМРХТХЙЮРНПНБ ДЮММШУ --//
#include <MapsID.h>

//-- ОНДЙКЧВЕМХЕ JSON --//
#include <System.JSON.hpp>


#include "MainForm_Delta.h"



namespace HandlersNS
{

	//-- тсмйжхъ-напюанрвхй онксвемхъ йнппейжхи --//
	void getCorrections(TJSONObject *json_object_parse);

	//-- тсмйжхъ-напюанрвхй пегскэрюрю днаюбкемхъ йнппейжхх --//
	void CheckAddCorrection(TJSONObject *json_object_parse);

	//-- тсмйжхъ-напюанрвхй пегскэрюрю хглемемхъ йнппейжхх --//
	void CheckEditCorrection(TJSONObject *json_object_parse);

	//-- тсмйжхъ-напюанрвхй пегскэрюрю сдюкемхъ йнппейжхх --//
	void CheckDeleteCorrection(TJSONObject *json_object_parse);

	//-- тсмйжхъ-напюанрвхй хглемемхъ йнппейжхх --//
	void editCorrection(TJSONObject *json_object_parse);

	//-- тсмйжхъ-напюанрвхй днаюбкемхъ йнппейжхх --//
	void addCorrection(TJSONObject *json_object_parse);

	//-- тсмйжхъ-напюанрвхй сдюкемхъ йнппейжхх --//
	void deleteCorrection(TJSONObject *json_object_parse);

}

#endif
