//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AddForm_Lines_Delta.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAddFormLines *AddFormLines;
//---------------------------------------------------------------------------
__fastcall TAddFormLines::TAddFormLines(TComponent* Owner)
	: TForm(Owner)
{
}


//---------------------------------------------------------//
//------------ ����������� ����������� ������� ------------//
//---------------------------------------------------------//

//-- ������� ������ ����� --//
void __fastcall TAddFormLines::FormShow(TObject *Sender)
{
    //-- ��������� ���������� ��������� ������ ���� ����������, ����� � ������� ������ --//
	AllSourcesCheck->Checked = false;
	AllCurrencysCheck->Checked = false;
	AllBasesCheck->Checked = false;

	//-- ������� ���� � ����������� --//
	SourcesCheckList->Clear();

	//-- ����������� ���������� ���� ����������� --//

	for(MSource::iterator map_iterator_source = MainForm->engine->Data()->map_sources.begin(); map_iterator_source != MainForm->engine->Data()->map_sources.end(); map_iterator_source ++)
	{
		SourcesCheckList->Items->Add( map_iterator_source->second.name );
	}




	//-- ������� ���� � �������� --//
	CurrencysCheckList->Clear();

	//-- ����������� ���������� ���� �������� --//

	for(MCurrency::iterator map_iterator_currency = MainForm->engine->Data()->map_currencys.begin(); map_iterator_currency != MainForm->engine->Data()->map_currencys.end(); map_iterator_currency ++)
	{
		CurrencysCheckList->Items->Add( map_iterator_currency->second.name );
	}


	//-- ������� ���� � �������� �������� --//
	BasesCheckList->Clear();
}



//---------------------------------------------------------//
//------------- ����������� ������� ��������� -------------//
//---------------------------------------------------------//

//-- ������� ��������� �� ������� �� ������ "Add" --//
void __fastcall TAddFormLines::AddButton_OneClick(TObject *Sender)
{

	//-- ��������� ������ --//
	UnicodeString error = "Required fields are not filled.";

	
	
	//-- �������� ������������ ���Ĩ���� ������ --//

	//-- �������� ���� ����� --//
	if(NameEdit->Text.IsEmpty())
	{
        ShowMessage(error);
		return;
	}

	//-- �������� �� ����� �� ����� ������ ��������� --//
	int sources_count=0;
	for(; sources_count != SourcesCheckList->Items->Count; sources_count ++)
	{
		if(SourcesCheckList->Checked[sources_count])
			break;
	}
	if(sources_count == SourcesCheckList->Items->Count)
	{
		ShowMessage(error);
		return;
	}

	//-- �������� �� ����� �� ����� ����� ������ --//
	int currencys_count=0;
	for(; currencys_count != CurrencysCheckList->Items->Count; currencys_count ++)
	{
		if(CurrencysCheckList->Checked[currencys_count])
			break;
	}
	if(currencys_count == CurrencysCheckList->Items->Count)
	{
		ShowMessage(error);
		return;
	}



	
	//--************* ���� ���� ��������� ����� ************** --//





	//-- ������������ ������ ���������� � ������������ ����������� --//

	//-- ��� --//
	UnicodeString param = "\"name\":\"" + MainForm->Encoder->EncodeString( NameEdit->Text, IndyTextEncoding_UTF8() ) + "\"";



	//-- ��������� --//
	param = param + ",\"sources\":\[";
	//-- ************************************ --//
	for(int j=0; j != SourcesCheckList->GetCount(); j ++)
	{
		if(SourcesCheckList->Checked[j])
		{
			MSource::iterator iterator_source;

			//-- ����� ID ��������� �� ����� --//
			for(iterator_source = MainForm->engine->Data()->map_sources.begin(); iterator_source != MainForm->engine->Data()->map_sources.end(); iterator_source ++)
			{
				if(iterator_source->second.name == SourcesCheckList->Items->Strings[j])
					break;
			}

			param = param + "\"" + iterator_source->first + "\",";
		}
	}
    //-- �������� ������ ������� --//
	param.Delete(param.Length(),1);
	param = param + "]";
	//-- ************************************ --//




	//-- ������ --//
	//-- ************************************ --//
	param = param + ",\"currencys\":\[";

	for(int j=0; j != CurrencysCheckList->GetCount(); j ++)
	{
		if(CurrencysCheckList->Checked[j])
		{
			MCurrency::iterator iterator_currency;

			//-- ����� ID ������ �� ����� --//
			for(iterator_currency = MainForm->engine->Data()->map_currencys.begin(); iterator_currency != MainForm->engine->Data()->map_currencys.end(); iterator_currency ++)
			{
				if(iterator_currency->second.name == CurrencysCheckList->Items->Strings[j])
					break;
			}

			param = param + "\"" + iterator_currency->first + "\",";
		}
	}
	//-- �������� ������ ������� --//
	param.Delete(param.Length(),1);

	param = param + "]";
	//-- ************************************ --//


	//-- ������� ������ --//
	//-- ************************************ --//
	int bases_count=0;
	for(; bases_count != BasesCheckList->Items->Count; bases_count ++)
	{
		if(BasesCheckList->Checked[bases_count])
			break;
	}
	if(bases_count != BasesCheckList->Items->Count)
	{
		param = param + ",\"base\":\[";

		for(int j=0; j != BasesCheckList->GetCount(); j ++)
		{
			if(BasesCheckList->Checked[j])
			{
				MCurrency::iterator iterator_currency;

				//-- ����� ID ������ �� ����� --//
				for(iterator_currency = MainForm->engine->Data()->map_currencys.begin(); iterator_currency != MainForm->engine->Data()->map_currencys.end(); iterator_currency ++)
				{
					if(iterator_currency->second.name == BasesCheckList->Items->Strings[j])
						break;
				}

				param = param + "\"" + iterator_currency->first + "\",";
			}
		}
		//-- �������� ������ ������� --//
		param.Delete(param.Length(),1);

		param = param + "]";
	}
	//-- ************************************ --//


	//-- ������ --//
    //-- ************************************ --//
	if(EnabledCheck->Checked)
		param = param + ",\"enabled\":1";
	else
		param = param + ",\"enabled\":0";
	//-- ************************************ --//


	//-- ������� --//
    //-- ************************************ --//
	if(!NotesMemo->Text.IsEmpty())
	{
		param = param + ",\"notes\":\"" + MainForm->Encoder->EncodeString( NotesMemo->Text, IndyTextEncoding_UTF8() ) + "\"";
	}
	//-- ************************************ --//


	//-- �������� ������� ���������� �� ������ --//
	MainForm->engine->Send("addLine", param, "CheckAddLine");

	//-- �������� ����� ���������� --//
	Close();
}




//-- ������� ��������� ���� ���������� --//
void __fastcall TAddFormLines::AllSourcesCheck_OneClick(TObject *Sender)
{

	if(AllSourcesCheck->State == true)
	{
		//-- ���� ��� ��������� �� �������� --//

		for(int sources_count=0; sources_count != SourcesCheckList->Items->Count; sources_count ++)
		{
			SourcesCheckList->Checked[sources_count] = true;
		}
	}
	else
	{
		//-- ���� ��� ��������� �������� --//

		for(int sources_count=0; sources_count != SourcesCheckList->Items->Count; sources_count ++)
		{
			SourcesCheckList->Checked[sources_count] = false;
		}
    }
}



//-- ������� ��������� ���� ����� --//
void __fastcall TAddFormLines::AllCurrencysCheck_OneClick(TObject *Sender)
{
	if(AllCurrencysCheck->State == true)
	{
		//-- ���� ��� ������ �� �������� --//

		for(int currencys_count=0; currencys_count != CurrencysCheckList->Items->Count; currencys_count ++)
		{
			CurrencysCheckList->Checked[currencys_count] = true;
		}
	}
	else
	{
		//-- ���� ��� ������ �������� --//

		for(int currencys_count=0; currencys_count != CurrencysCheckList->Items->Count; currencys_count ++)
		{
			CurrencysCheckList->Checked[currencys_count] = false;
		}
	}

	//-- ���������� ������ ������� ����� --//
	UpdateBaseCurrencys();
}



//-- ������� ��������� ���� ������� ����� --//
void __fastcall TAddFormLines::AllBasesCheck_OneClick(TObject *Sender)
{
	if(AllBasesCheck->State == true)
	{
		//-- ���� ��� ������ �� �������� --//

		for(int bases_count=0; bases_count != BasesCheckList->Items->Count; bases_count ++)
		{
			BasesCheckList->Checked[bases_count] = true;
		}
	}
	else
	{
		//-- ���� ��� ������ �������� --//

		for(int bases_count=0; bases_count != BasesCheckList->Items->Count; bases_count ++)
		{
			BasesCheckList->Checked[bases_count] = false;
		}
	}
}




//-- ������� ��������� ��������� ������ ����� --//
void __fastcall TAddFormLines::CurrencysCheckListClickCheck(TObject *Sender)
{
	UpdateBaseCurrencys();
}




//---------------------------------------------------------//
//------------- �������������� ������� ������ -------------//
//---------------------------------------------------------//


//-- ������� ���������� ������� ����� ��� ����������� �� ������ --//
void TAddFormLines::UpdateBaseCurrencys()
{
    //-- ����������� ��������� ��������� �� ������ ������� ����� --//
	std::vector< UnicodeString > activy_bases;

	for(int bases_count=0; bases_count != BasesCheckList->Items->Count; bases_count ++)
	{
		if(BasesCheckList->Checked[bases_count])
			activy_bases.push_back( BasesCheckList->Items->Strings[bases_count] );
	}

	//-- ������� ������� ����� --//
	BasesCheckList->Clear();

	//-- ���������� ������ ��������� ����� �� ������� ����� --//
	for(int currencys_count=0; currencys_count != CurrencysCheckList->Items->Count; currencys_count ++)
	{
		if(CurrencysCheckList->Checked[currencys_count])
			BasesCheckList->Items->Add( CurrencysCheckList->Items->Strings[currencys_count] );
	}

	//-- ����� ���������� �� ����� �������� ������� ����� --//
	for(std::vector< UnicodeString >::iterator iterator_base = activy_bases.begin(); iterator_base != activy_bases.end(); iterator_base ++)
	{
		for(int i=0; i != BasesCheckList->Items->Count; i ++)
		{
			if(BasesCheckList->Items->Strings[i] == *iterator_base)
				BasesCheckList->Checked[i] = true;
		}
	}
}
