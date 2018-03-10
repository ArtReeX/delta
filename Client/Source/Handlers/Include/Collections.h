//-- ******************************************* --//
//-- *************** Collections *************** --//
//-- ******************************************* --//

#ifndef COLLECTIONSH
#define COLLECTIONSH

//-- ����������� ��������������� ������ --//
#include <MapsID.h>


//-- ����������� JSON --//
#include <System.JSON.hpp>

#include "MainForm_Delta.h"


namespace HandlersNS
{


	//-- �������-���������� ������ ����� ������ --//
	void collect(TJSONObject *json_object_parse);

	//-- �������-���������� ����� ����� ������ --//
	void collected(TJSONObject *json_object_parse);

	//-- �������-���������� ����� ������ --//
	void processSource(TJSONObject *json_object_parse);

}


#endif
