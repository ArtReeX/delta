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
//------------ ОБРАБОТЧИКИ СТАНДАРТНЫХ СОБЫТИЙ ------------//
//---------------------------------------------------------//

//-- ФУНКЦИЯ ПОКАЗА ФОРМЫ --//
void __fastcall TAddFormCorrections::FormShow(TObject *Sender)
{
	//-- очистка поля с источниками --//
	SourceListBox->Clear();

	//-- изначальное заполнение поля источниками --//

	for(MSource::iterator map_iterator_source = MainForm->engine->Data()->map_sources.begin(); map_iterator_source != MainForm->engine->Data()->map_sources.end(); map_iterator_source ++)
	{
		SourceListBox->Items->Add( map_iterator_source->second.name );
	}




	//-- очистка поля с исходящими валютами --//
	CurrOutListBox->Clear();

	//-- изначальное заполнение поля исходящими валютами --//

	for(MCurrency::iterator map_iterator_currency = MainForm->engine->Data()->map_currencys.begin(); map_iterator_currency != MainForm->engine->Data()->map_currencys.end(); map_iterator_currency ++)
	{
		CurrOutListBox->Items->Add( map_iterator_currency->second.name );
	}


	//-- очистка поля с входящими валютами --//
	CurrInListBox->Clear();

	//-- изначальное заполнение поля входящими валютами --//

	for(MCurrency::iterator map_iterator_currency = MainForm->engine->Data()->map_currencys.begin(); map_iterator_currency != MainForm->engine->Data()->map_currencys.end(); map_iterator_currency ++)
	{
		CurrInListBox->Items->Add( map_iterator_currency->second.name );
	}
}



//---------------------------------------------------------//
//------------- ОБРАБОТЧИКИ СОБЫТИЙ ЭЛЕМЕНТОВ -------------//
//---------------------------------------------------------//

//-- ФУНКЦИЯ ОБРАБОТКИ ПО НАЖАТИЮ НА КНОПКУ "Add" --//
void __fastcall TAddFormCorrections::AddButton_OneClick(TObject *Sender)
{
    //-- сообщение ошибки --//
	UnicodeString error = "Required fields are not filled.";



	//-- ПРОВЕРКА ПРАВИЛЬНОСТИ ВВЕДЁННЫХ ДАННЫХ --//

	//-- проверка поля Fee --//
	if(FeeEdit->Text.IsEmpty())
	{
		ShowMessage(error);
		return;
	}

	//-- проверка на выбор одного источника --//
	if(SourceListBox->ItemIndex == -1)
	{
		ShowMessage(error);
		return;
	}

	//-- проверка на выбор одной входящей валюты --//
	if(CurrInListBox->ItemIndex == -1)
	{
		ShowMessage(error);
		return;
	}

	//-- проверка на выбор одной исходящей валюты --//
	if(CurrOutListBox->ItemIndex == -1)
	{
		ShowMessage(error);
		return;
	}



	//--************* ЕСЛИ ПОЛЯ ЗАПОЛНЕНЫ ВЕРНО ************** --//

	//-- ФОРМИРОВАНИЕ СТРОКИ ДОБАВЛЕНИЯ С СТАНДАРТНЫМИ ПАРАМЕТРАМИ --//
	UnicodeString param;

	//-- источник --//
	param = param + "\"sourceId\":";
	//-- ************************************ --//
	MSource::iterator iterator_source;

	//-- поиск ID источника по имени --//
	for(iterator_source = MainForm->engine->Data()->map_sources.begin(); iterator_source != MainForm->engine->Data()->map_sources.end(); iterator_source ++)
	{
		if(iterator_source->second.name == SourceListBox->Items->Strings[ SourceListBox->ItemIndex ])
			break;
	}

	param = param + iterator_source->first;




	//-- входящая валюта --//
	param = param + ",\"currIn\":";
	//-- ************************************ --//
	MCurrency::iterator iterator_currency_in;

	//-- поиск ID источника по имени --//
	for(iterator_currency_in = MainForm->engine->Data()->map_currencys.begin(); iterator_currency_in != MainForm->engine->Data()->map_currencys.end(); iterator_currency_in ++)
	{
		if(iterator_currency_in->second.name == CurrInListBox->Items->Strings[ CurrInListBox->ItemIndex ])
			break;
	}

	param = param + iterator_currency_in->first;
	//-- ************************************ --//



	//-- входящая валюта --//
	param = param + ",\"currOut\":";
	//-- ************************************ --//
	MCurrency::iterator iterator_currency_out;

	//-- поиск ID источника по имени --//
	for(iterator_currency_out = MainForm->engine->Data()->map_currencys.begin(); iterator_currency_out != MainForm->engine->Data()->map_currencys.end(); iterator_currency_out ++)
	{
		if(iterator_currency_out->second.name == CurrOutListBox->Items->Strings[ CurrOutListBox->ItemIndex ])
			break;
	}

	param = param + iterator_currency_out->first;
	//-- ************************************ --//



	//-- дополнительная комиссия --//
	//-- ************************************ --//
	param = param + ",\"fee\":" + MainForm->engine->FloatWithDots( FeeEdit->Text ) ;
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
	if(!NotesEdit->Text.IsEmpty())
	{
		param = param + ",\"notes\":\"" + MainForm->Encoder->EncodeString( NotesEdit->Text, IndyTextEncoding_UTF8() ) + "\"";
	}
	//-- ************************************ --//


    //-- отправка запроса добавления на сервер --//
	MainForm->engine->Send("addCorrection", param, "CheckAddCorrection");

	//-- закрытие формы добавления --//
	Close();
}


