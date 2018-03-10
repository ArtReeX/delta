//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AddForm_Corrections_Delta.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAddFormCorrections *AddFormCorrections;
//---------------------------------------------------------------------------
__fastcall TAddFormCorrections::TAddFormCorrections(TComponent* Owner)
	: TForm(Owner)
{
}


//---------------------------------------------------------//
//------------ ����������� ����������� ������� ------------//
//---------------------------------------------------------//

//-- ������� ������ ����� --//
void __fastcall TAddFormCorrections::FormShow(TObject *Sender)
{
	//-- ������� ���� � ����������� --//
	SourceListBox->Clear();

	//-- ����������� ���������� ���� ����������� --//

	for(MSource::iterator map_iterator_source = MainForm->engine->Data()->map_sources.begin(); map_iterator_source != MainForm->engine->Data()->map_sources.end(); map_iterator_source ++)
	{
		SourceListBox->Items->Add( map_iterator_source->second.name );
	}




	//-- ������� ���� � ���������� �������� --//
	CurrOutListBox->Clear();

	//-- ����������� ���������� ���� ���������� �������� --//

	for(MCurrency::iterator map_iterator_currency = MainForm->engine->Data()->map_currencys.begin(); map_iterator_currency != MainForm->engine->Data()->map_currencys.end(); map_iterator_currency ++)
	{
		CurrOutListBox->Items->Add( map_iterator_currency->second.name );
	}


	//-- ������� ���� � ��������� �������� --//
	CurrInListBox->Clear();

	//-- ����������� ���������� ���� ��������� �������� --//

	for(MCurrency::iterator map_iterator_currency = MainForm->engine->Data()->map_currencys.begin(); map_iterator_currency != MainForm->engine->Data()->map_currencys.end(); map_iterator_currency ++)
	{
		CurrInListBox->Items->Add( map_iterator_currency->second.name );
	}
}



//---------------------------------------------------------//
//------------- ����������� ������� ��������� -------------//
//---------------------------------------------------------//

//-- ������� ��������� �� ������� �� ������ "Add" --//
void __fastcall TAddFormCorrections::AddButton_OneClick(TObject *Sender)
{
    //-- ��������� ������ --//
	UnicodeString error = "Required fields are not filled.";



	//-- �������� ������������ ���Ĩ���� ������ --//

	//-- �������� ���� Fee --//
	if(FeeEdit->Text.IsEmpty())
	{
		ShowMessage(error);
		return;
	}

	//-- �������� �� ����� ������ ��������� --//
	if(SourceListBox->ItemIndex == -1)
	{
		ShowMessage(error);
		return;
	}

	//-- �������� �� ����� ����� �������� ������ --//
	if(CurrInListBox->ItemIndex == -1)
	{
		ShowMessage(error);
		return;
	}

	//-- �������� �� ����� ����� ��������� ������ --//
	if(CurrOutListBox->ItemIndex == -1)
	{
		ShowMessage(error);
		return;
	}



	//--************* ���� ���� ��������� ����� ************** --//

	//-- ������������ ������ ���������� � ������������ ����������� --//
	UnicodeString param;

	//-- �������� --//
	param = param + "\"sourceId\":";
	//-- ************************************ --//
	MSource::iterator iterator_source;

	//-- ����� ID ��������� �� ����� --//
	for(iterator_source = MainForm->engine->Data()->map_sources.begin(); iterator_source != MainForm->engine->Data()->map_sources.end(); iterator_source ++)
	{
		if(iterator_source->second.name == SourceListBox->Items->Strings[ SourceListBox->ItemIndex ])
			break;
	}

	param = param + iterator_source->first;




	//-- �������� ������ --//
	param = param + ",\"currIn\":";
	//-- ************************************ --//
	MCurrency::iterator iterator_currency_in;

	//-- ����� ID ��������� �� ����� --//
	for(iterator_currency_in = MainForm->engine->Data()->map_currencys.begin(); iterator_currency_in != MainForm->engine->Data()->map_currencys.end(); iterator_currency_in ++)
	{
		if(iterator_currency_in->second.name == CurrInListBox->Items->Strings[ CurrInListBox->ItemIndex ])
			break;
	}

	param = param + iterator_currency_in->first;
	//-- ************************************ --//



	//-- �������� ������ --//
	param = param + ",\"currOut\":";
	//-- ************************************ --//
	MCurrency::iterator iterator_currency_out;

	//-- ����� ID ��������� �� ����� --//
	for(iterator_currency_out = MainForm->engine->Data()->map_currencys.begin(); iterator_currency_out != MainForm->engine->Data()->map_currencys.end(); iterator_currency_out ++)
	{
		if(iterator_currency_out->second.name == CurrOutListBox->Items->Strings[ CurrOutListBox->ItemIndex ])
			break;
	}

	param = param + iterator_currency_out->first;
	//-- ************************************ --//



	//-- �������������� �������� --//
	//-- ************************************ --//
	param = param + ",\"fee\":" + MainForm->engine->FloatWithDots( FeeEdit->Text ) ;
	//-- ************************************ --//


    //-- ������������ ������ ���������� � ��������������� ����������� --//


	//-- ���� ����������� --//
    //-- ************************************ --//
	if(EnabledCheck->Checked)
		param = param + ",\"enabled\":1";
	else
		param = param + ",\"enabled\":0";
	//-- ************************************ --//


	//-- ����������� --//
    //-- ************************************ --//
	if(!NotesEdit->Text.IsEmpty())
	{
		param = param + ",\"notes\":\"" + MainForm->Encoder->EncodeString( NotesEdit->Text, IndyTextEncoding_UTF8() ) + "\"";
	}
	//-- ************************************ --//


    //-- �������� ������� ���������� �� ������ --//
	MainForm->engine->Send("addCorrection", param, "CheckAddCorrection");

	//-- �������� ����� ���������� --//
	Close();
}


