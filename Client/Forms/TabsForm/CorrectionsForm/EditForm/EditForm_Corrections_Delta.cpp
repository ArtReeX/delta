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
//------------ ОБРАБОТЧИКИ СТАНДАРТНЫХ СОБЫТИЙ ------------//
//---------------------------------------------------------//

//-- ФУНКЦИЯ ПОКАЗА ФОРМЫ --//
void __fastcall TEditFormCorrections::FormShow(TObject *Sender)
{
    //-- поиск ID --//
	MCorrection::iterator map_iterator = MainForm->engine->Data()->map_corrections.find( MainForm->Corrections_StringGrid->Cells[0][MainForm->Corrections_StringGrid->Row].ToInt() );



	//-- очистка поля с источниками --//
	SourceListBox->Clear();

	//-- изначальное заполнение поля источниками --//

	for(MSource::iterator map_iterator_source = MainForm->engine->Data()->map_sources.begin(); map_iterator_source != MainForm->engine->Data()->map_sources.end(); map_iterator_source ++)
	{
		SourceListBox->Items->Add( map_iterator_source->second.name );
	}

	//-- определение активного источника --//

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


	//-- очистка поля с исходящими валютами --//
	CurrOutListBox->Clear();

	//-- изначальное заполнение поля исходящими валютами --//

	for(MCurrency::iterator map_iterator_currency = MainForm->engine->Data()->map_currencys.begin(); map_iterator_currency != MainForm->engine->Data()->map_currencys.end(); map_iterator_currency ++)
	{
		CurrOutListBox->Items->Add( map_iterator_currency->second.name );
	}


	//-- определение активной исходящей валюты --//

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


	//-- очистка поля с входящими валютами --//
	CurrInListBox->Clear();

	//-- изначальное заполнение поля входящими валютами --//

	for(MCurrency::iterator map_iterator_currency = MainForm->engine->Data()->map_currencys.begin(); map_iterator_currency != MainForm->engine->Data()->map_currencys.end(); map_iterator_currency ++)
	{
		CurrInListBox->Items->Add( map_iterator_currency->second.name );
	}

	//-- определение активной входящей валюты --//

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


	//-- изначальное заполнение поля дополнительной комиссией --//
	FeeEdit->Text = MainForm->engine->FloatWithDots( map_iterator->second.fee );

	//-- изначальное заполнение поля учёта направления --//
	EnabledCheck->Checked = map_iterator->second.enabled.ToInt();

	//-- изначальное заполнение поля комментария --//
	NotesEdit->Text = map_iterator->second.notes;
}



//---------------------------------------------------------//
//------------- ОБРАБОТЧИКИ СОБЫТИЙ ЭЛЕМЕНТОВ -------------//
//---------------------------------------------------------//


//-- ФУНКЦИЯ ОБРАБОТКИ ПО НАЖАТИЮ НА КНОПКУ "Edit" --//
void __fastcall TEditFormCorrections::SaveButtonClick(TObject *Sender)
{

	//-- поиск ID --//
	MCorrection::iterator map_iterator = MainForm->engine->Data()->map_corrections.find( MainForm->Corrections_StringGrid->Cells[0][MainForm->Corrections_StringGrid->Row].ToInt() );



	//-- ФОРМИРОВАНИЕ СТРОКИ ИЗМЕНЕНИЯ С СТАНДАРТНЫМИ ПАРАМЕТРАМИ --//
	UnicodeString param;

	//-- ID коррекции --//
	param = param + "\"id\":" + map_iterator->first;

	//-- источник --//
	param = param + ",\"sourceId\":";
	//-- ************************************ --//
	MSource::iterator iterator_source;

	//-- поиск ID источника по имени --//
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




	//-- входящая валюта --//
	param = param + ",\"currIn\":";
	//-- ************************************ --//
	MCurrency::iterator iterator_currency_in;

	//-- поиск ID источника по имени --//
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



	//-- входящая валюта --//
	param = param + ",\"currOut\":";
	//-- ************************************ --//
	MCurrency::iterator iterator_currency_out;

	//-- поиск ID источника по имени --//
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



	//-- дополнительная комиссия --//
	//-- ************************************ --//
	param = param + ",\"fee\":" + MainForm->engine->FloatWithDots( FeeEdit->Text );
	//-- ************************************ --//


    //-- ФОРМИРОВАНИЕ СТРОКИ ДОБАВЛЕНИЯ С ДОПОЛНИТЕЛЬНЫМИ ПАРАМЕТРАМИ --//


	//-- учёт направления --//
    //-- ************************************ --//
	if(EnabledCheck->Checked)
		param = param + ",\"enabled\":1";
	else
		param = param + ",\"enabled\":0";
	//-- ************************************ --//


	//-- комментарий --//
    //-- ************************************ --//
	if(NotesEdit->Text != map_iterator->second.notes)
	{
        if(NotesEdit->Text.IsEmpty())
			NotesEdit->Text = " ";

		param = param + ",\"notes\":\"" + MainForm->Encoder->EncodeString( NotesEdit->Text, IndyTextEncoding_UTF8() ) + "\"";
	}
	//-- ************************************ --//


	//-- отправка запроса изменения на сервер --//
	MainForm->engine->Send("editCorrection", param, "CheckEditCorrection");

	//-- закрытие формы изменения --//
	Close();
}

