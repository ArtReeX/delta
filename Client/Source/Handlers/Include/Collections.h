//-- ******************************************* --//
//-- *************** Collections *************** --//
//-- ******************************************* --//

#ifndef COLLECTIONSH
#define COLLECTIONSH

//-- подключение идентификаторов данных --//
#include <MapsID.h>


//-- подключение JSON --//
#include <System.JSON.hpp>

#include "MainForm_Delta.h"


namespace HandlersNS
{


	//-- ФУНКЦИЯ-ОБРАБОТЧИК НАЧАЛА СБОРА ДАННЫХ --//
	void collect(TJSONObject *json_object_parse);

	//-- ФУНКЦИЯ-ОБРАБОТЧИК КОНЦА СБОРА ДАННЫХ --//
	void collected(TJSONObject *json_object_parse);

	//-- ФУНКЦИЯ-ОБРАБОТЧИК СБОРА ДАННЫХ --//
	void processSource(TJSONObject *json_object_parse);

}


#endif
