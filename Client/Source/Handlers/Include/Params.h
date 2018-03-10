//-- ******************************************* --//
//-- ****************** Params ***************** --//
//-- ******************************************* --//

#ifndef PARAMSH
#define PARAMSH

//-- ОНДЙКЧВЕМХЕ ХДЕМРХТХЙЮРНПНБ ДЮММШУ --//
#include <MapsID.h>


//-- ОНДЙКЧВЕМХЕ JSON --//
#include <System.JSON.hpp>

#include "MainForm_Delta.h"
#include "DebugForm_Delta.h"

namespace HandlersNS
{

	//-- тсмйжхъ-напюанрвхй онксвемхъ оюпюлерпнб --//
	void getParams(TJSONObject *json_object_parse);

	//-- тсмйжхъ-напюанрвхй пегскэрюрю хглемемхъ оюпюлерпю --//
	void CheckEditParams(TJSONObject *json_object_parse);

	//-- тсмйжхъ-напюанрвхй хглемемхъ оюпюлерпю --//
	void editParams(TJSONObject *json_object_parse);

}



#endif
