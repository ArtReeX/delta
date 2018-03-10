//-- ******************************************* --//
//-- ****************** Params ***************** --//
//-- ******************************************* --//

#ifndef PARAMSH
#define PARAMSH

//-- ����������� ��������������� ������ --//
#include <MapsID.h>


//-- ����������� JSON --//
#include <System.JSON.hpp>

#include "MainForm_Delta.h"
#include "DebugForm_Delta.h"

namespace HandlersNS
{

	//-- �������-���������� ��������� ���������� --//
	void getParams(TJSONObject *json_object_parse);

	//-- �������-���������� ���������� ��������� ��������� --//
	void CheckEditParams(TJSONObject *json_object_parse);

	//-- �������-���������� ��������� ��������� --//
	void editParams(TJSONObject *json_object_parse);

}



#endif
