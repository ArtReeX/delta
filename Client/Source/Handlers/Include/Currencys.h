//-- ******************************************* --//
//-- **************** Currencys **************** --//
//-- ******************************************* --//

#ifndef CURRENCYSH
#define CURRENCYSH

//-- ОНДЙКЧВЕМХЕ ХДЕМРХТХЙЮРНПНБ ДЮММШУ --//
#include <MapsID.h>


//-- ОНДЙКЧВЕМХЕ JSON --//
#include <System.JSON.hpp>

#include "MainForm_Delta.h"


namespace HandlersNS
{


	//-- тсмйжхъ-напюанрвхй онксвемхъ бюкчр --//
	void getCurrencys(TJSONObject *json_object_parse);

	//-- тсмйжхъ-напюанрвхй пегскэрюрю днаюбкемхъ бюкчрш --//
	void CheckAddCurrency(TJSONObject *json_object_parse);

	//-- тсмйжхъ-напюанрвхй пегскэрюрю хглемемхъ бюкчрш --//
	void CheckEditCurrency(TJSONObject *json_object_parse);

	//-- тсмйжхъ-напюанрвхй пегскэрюрю сдюкемхъ бюкчрш --//
	void CheckDeleteCurrency(TJSONObject *json_object_parse);

	//-- тсмйжхъ-напюанрвхй хглемемхъ бюкчрш --//
	void editCurrency(TJSONObject *json_object_parse);

	//-- тсмйжхъ-напюанрвхй днаюбкемхъ бюкчрш --//
	void addCurrency(TJSONObject *json_object_parse);

	//-- тсмйжхъ-напюанрвхй сдюкемхъ бюкчрш --//
	void deleteCurrency(TJSONObject *json_object_parse);

}


#endif
