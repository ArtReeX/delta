//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "EditForm_Corrections_Delta.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEditFormCorrections *EditFormCorrections;
//---------------------------------------------------------------------------
__fastcall TEditFormCorrections::TEditFormCorrections(TComponent* Owner)
	: TForm(Owner)
{
}


//---------------------------------------------------------//
//------------ ����������� ����������� ������� ------------//
//---------------------------------------------------------//

//-- ������� ������ ����� --//
void __fastcall TEditFormCorrections::FormShow(TObject *Sender)
{
    //-- ����� ID --//
	MCorrection::iterator map_iterator = MainForm->engine->Data()->map_corrections.find( MainForm->Corrections_StringGrid->Cells[0][MainForm->Corrections_StringGrid->Row].ToInt() );



	//-- ������� ���� � ����������� --//
	SourceListBox->Clear();

	//-- ����������� ���������� ���� ����������� --//

	for(MSource::iterator map_iterator_source = MainForm->engine->Data()->map_sources.begin(); map_iterator_source != MainForm->engine->Data()->map_sources.end(); map_iterator_source ++)
	{
		SourceListBox->Items->Add( map_iterator_source->second.name );
	}

	//-- ����������� ��������� ��������� --//

	for(int i=0; i != SourceListBox->Items->Count; i ++)
	{


		if(MainForm->engine->Data()->map_sources.find( map_iterator->second.sourceId.ToInt() ) != MainForm->engine->Data()->map_sources.end())
		{
            if(SourceListBox->Items->Strings[i] == MainForm->engine->Data()->map_sources.find( map_iterator->second.sourceId.ToInt() )->second.name)
			{
				SourceListBox->ItemIndex = i;
				break;
			}
        }

	}


	//-- ������� ���� � ���������� �������� --//
	CurrOutListBox->Clear();

	//-- ����������� ���������� ���� ���������� �������� --//

	for(MCurrency::iterator map_iterator_currency = MainForm->engine->Data()->map_currencys.begin(); map_iterator_currency != MainForm->engine->Data()->map_currencys.end(); map_iterator_currency ++)
	{
		CurrOutListBox->Items->Add( map_iterator_currency->second.name );
	}


	//-- ����������� �������� ��������� ������ --//

	for(int i=0; i != CurrOutListBox->Items->Count; i ++)
	{
		if(MainForm->engine->Data()->map_currencys.find( map_iterator->second.currOut.ToInt() ) != MainForm->engine->Data()->map_currencys.end())
		{
			if(CurrOutListBox->Items->Strings[i] == MainForm->engine->Data()->map_currencys.find( map_iterator->second.currOut.ToInt() )->second.name)
		{
			CurrOutListBox->ItemIndex = i;
			break;
		}
        }


	}


	//-- ������� ���� � ��������� �������� --//
	CurrInListBox->Clear();

	//-- ����������� ���������� ���� ��������� �������� --//

	for(MCurrency::iterator map_iterator_currency = MainForm->engine->Data()->map_currencys.begin(); map_iterator_currency != MainForm->engine->Data()->map_currencys.end(); map_iterator_currency ++)
	{
		CurrInListBox->Items->Add( map_iterator_currency->second.name );
	}

	//-- ����������� �������� �������� ������ --//

	for(int i=0; i != CurrInListBox->Items->Count; i ++)
	{
		if(MainForm->engine->Data()->map_currencys.find( map_iterator->second.currIn.ToInt() ) != MainForm->engine->Data()->map_currencys.end())
		{
            if(CurrInListBox->Items->Strings[i] == MainForm->engine->Data()->map_currencys.find( map_iterator->second.currIn.ToInt() )->second.name)
			{
				CurrInListBox->ItemIndex = i;
				break;
			}
		}
	}


	//-- ����������� ���������� ���� �������������� ��������� --//
	FeeEdit->Text = MainForm->engine->FloatWithDots( map_iterator->second.fee );

	//-- ����������� ���������� ���� ����� ����������� --//
	EnabledCheck->Checked = map_iterator->second.enabled.ToInt();

	//-- ����������� ���������� ���� ����������� --//
	NotesEdit->Text = map_iterator->second.notes;
}



//---------------------------------------------------------//
//------------- ����������� ������� ��������� -------------//
//---------------------------------------------------------//


//-- ������� ��������� �� ������� �� ������ "Edit" --//
void __fastcall TEditFormCorrections::SaveButtonClick(TObject *Sender)
{

	//-- ����� ID --//
	MCorrection::iterator map_iterator = MainForm->engine->Data()->map_corrections.find( MainForm->Corrections_StringGrid->Cells[0][MainForm->Corrections_StringGrid->Row].ToInt() );



	//-- ������������ ������ ��������� � ������������ ����������� --//
	UnicodeString param;

	//-- ID ��������� --//
	param = param + "\"id\":" + map_iterator->first;

	//-- �������� --//
	param = param + ",\"sourceId\":";
	//-- ************************************ --//
	MSource::iterator iterator_source;

	//-- ����� ID ��������� �� ����� --//
	for(iterator_source = MainForm->engine->Data()->map_sources.begin(); iterator_source != MainForm->engine->Data()->map_sources.end(); iterator_source ++)
	{
		if(SourceListBox->ItemIndex != -1)
		{
        	if(iterator_source->second.name == SourceListBox->Items->Strings[ SourceListBox->ItemIndex ])
			break;
		}
	}

	if(iterator_source != MainForm->engine->Data()->map_sources.end())
		param = param + iterator_source->first;




	//-- �������� ������ --//
	param = param + ",\"currIn\":";
	//-- ************************************ --//
	MCurrency::iterator iterator_currency_in;

	//-- ����� ID ��������� �� ����� --//
	for(iterator_currency_in = MainForm->engine->Data()->map_currencys.begin(); iterator_currency_in != MainForm->engine->Data()->map_currencys.end(); iterator_currency_in ++)
	{
		if(CurrInListBox->ItemIndex != -1)
		{
            if(iterator_currency_in->second.name == CurrInListBox->Items->Strings[ CurrInListBox->ItemIndex ])
			break;
		}
	}

	if(iterator_currency_in != MainForm->engine->Data()->map_currencys.end())
		param = param + iterator_currency_in->first;
	//-- ************************************ --//



	//-- �������� ������ --//
	param = param + ",\"currOut\":";
	//-- ************************************ --//
	MCurrency::iterator iterator_currency_out;

	//-- ����� ID ��������� �� ����� --//
	for(iterator_currency_out = MainForm->engine->Data()->map_currencys.begin(); iterator_currency_out != MainForm->engine->Data()->map_currencys.end(); iterator_currency_out ++)
	{
		if(CurrOutListBox->ItemIndex != -1)
		{
            if(iterator_currency_out->second.name == CurrOutListBox->Items->Strings[ CurrOutListBox->ItemIndex ])
			break;
		}
	}

	if(iterator_currency_out != MainForm->engine->Data()->map_currencys.end())
		param = param + iterator_currency_out->first;
	//-- ************************************ --//



	//-- �������������� �������� --//
	//-- ************************************ --//
	param = param + ",\"fee\":" + MainForm->engine->FloatWithDots( FeeEdit->Text );
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
	if(NotesEdit->Text != map_iterator->second.notes)
	{
        if(NotesEdit->Text.IsEmpty())
			NotesEdit->Text = " ";

		param = param + ",\"notes\":\"" + MainForm->Encoder->EncodeString( NotesEdit->Text, IndyTextEncoding_UTF8() ) + "\"";
	}
	//-- ************************************ --//


	//-- �������� ������� ��������� �� ������ --//
	MainForm->engine->Send("editCorrection", param, "CheckEditCorrection");

	//-- �������� ����� ��������� --//
	Close();
}

