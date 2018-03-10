//-- ******************************************* --//
//-- **************** Currencys **************** --//
//-- ******************************************* --//

#ifndef CURRENCYSH
#define CURRENCYSH

//-- ����������� ��������������� ������ --//
#include <MapsID.h>


//-- ����������� JSON --//
#include <System.JSON.hpp>

#include "MainForm_Delta.h"


namespace HandlersNS
{


	//-- �������-���������� ��������� ����� --//
	void getCurrencys(TJSONObject *json_object_parse);

	//-- �������-���������� ���������� ���������� ������ --//
	void CheckAddCurrency(TJSONObject *json_object_parse);

	//-- �������-���������� ���������� ��������� ������ --//
	void CheckEditCurrency(TJSONObject *json_object_parse);

	//-- �������-���������� ���������� �������� ������ --//
	void CheckDeleteCurrency(TJSONObject *json_object_parse);

	//-- �������-���������� ��������� ������ --//
	void editCurrency(TJSONObject *json_object_parse);

	//-- �������-���������� ���������� ������ --//
	void addCurrency(TJSONObject *json_object_parse);

	//-- �������-���������� �������� ������ --//
	void deleteCurrency(TJSONObject *json_object_parse);

}


#endif
