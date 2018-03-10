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
//------------ ОБРАБОТЧИКИ СТАНДАРТНЫХ СОБЫТИЙ ------------//
//---------------------------------------------------------//

//-- ФУНКЦИЯ ПОКАЗА ФОРМЫ --//
void __fastcall TAddFormLines::FormShow(TObject *Sender)
{
    //-- установка начального состояния выбора всех источников, валют и базовой валюты --//
	AllSourcesCheck->Checked = false;
	AllCurrencysCheck->Checked = false;
	AllBasesCheck->Checked = false;

	//-- очистка поля с источниками --//
	SourcesCheckList->Clear();

	//-- изначальное заполнение поля источниками --//

	for(MSource::iterator map_iterator_source = MainForm->engine->Data()->map_sources.begin(); map_iterator_source != MainForm->engine->Data()->map_sources.end(); map_iterator_source ++)
	{
		SourcesCheckList->Items->Add( map_iterator_source->second.name );
	}




	//-- очистка поля с валютами --//
	CurrencysCheckList->Clear();

	//-- изначальное заполнение поля валютами --//

	for(MCurrency::iterator map_iterator_currency = MainForm->engine->Data()->map_currencys.begin(); map_iterator_currency != MainForm->engine->Data()->map_currencys.end(); map_iterator_currency ++)
	{
		CurrencysCheckList->Items->Add( map_iterator_currency->second.name );
	}


	//-- очистка поля с базовыми валютами --//
	BasesCheckList->Clear();
}



//---------------------------------------------------------//
//------------- ОБРАБОТЧИКИ СОБЫТИЙ ЭЛЕМЕНТОВ -------------//
//---------------------------------------------------------//

//-- ФУНКЦИЯ ОБРАБОТКИ ПО НАЖАТИЮ НА КНОПКУ "Add" --//
void __fastcall TAddFormLines::AddButton_OneClick(TObject *Sender)
{

	//-- сообщение ошибки --//
	UnicodeString error = "Required fields are not filled.";

	
	
	//-- ПРОВЕРКА ПРАВИЛЬНОСТИ ВВЕДЁННЫХ ДАННЫХ --//

	//-- проверка поля имени --//
	if(NameEdit->Text.IsEmpty())
	{
        ShowMessage(error);
		return;
	}

	//-- проверка на выбор не менее одного источника --//
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

	//-- проверка на выбор не менее одной валюты --//
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



	
	//--************* ЕСЛИ ПОЛЯ ЗАПОЛНЕНЫ ВЕРНО ************** --//





	//-- ФОРМИРОВАНИЕ СТРОКИ ДОБАВЛЕНИЯ С СТАНДАРТНЫМИ ПАРАМЕТРАМИ --//

	//-- имя --//
	UnicodeString param = "\"name\":\"" + MainForm->Encoder->EncodeString( NameEdit->Text, IndyTextEncoding_UTF8() ) + "\"";



	//-- источники --//
	param = param + ",\"sources\":\[";
	//-- ************************************ --//
	for(int j=0; j != SourcesCheckList->GetCount(); j ++)
	{
		if(SourcesCheckList->Checked[j])
		{
			MSource::iterator iterator_source;

			//-- поиск ID источника по имени --//
			for(iterator_source = MainForm->engine->Data()->map_sources.begin(); iterator_source != MainForm->engine->Data()->map_sources.end(); iterator_source ++)
			{
				if(iterator_source->second.name == SourcesCheckList->Items->Strings[j])
					break;
			}

			param = param + "\"" + iterator_source->first + "\",";
		}
	}
    //-- удаление лишней запятой --//
	param.Delete(param.Length(),1);
	param = param + "]";
	//-- ************************************ --//




	//-- валюты --//
	//-- ************************************ --//
	param = param + ",\"currencys\":\[";

	for(int j=0; j != CurrencysCheckList->GetCount(); j ++)
	{
		if(CurrencysCheckList->Checked[j])
		{
			MCurrency::iterator iterator_currency;

			//-- поиск ID валюты по имени --//
			for(iterator_currency = MainForm->engine->Data()->map_currencys.begin(); iterator_currency != MainForm->engine->Data()->map_currencys.end(); iterator_currency ++)
			{
				if(iterator_currency->second.name == CurrencysCheckList->Items->Strings[j])
					break;
			}

			param = param + "\"" + iterator_currency->first + "\",";
		}
	}
	//-- удаление лишней запятой --//
	param.Delete(param.Length(),1);

	param = param + "]";
	//-- ************************************ --//


	//-- базовые валюты --//
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

				//-- поиск ID валюты по имени --//
				for(iterator_currency = MainForm->engine->Data()->map_currencys.begin(); iterator_currency != MainForm->engine->Data()->map_currencys.end(); iterator_currency ++)
				{
					if(iterator_currency->second.name == BasesCheckList->Items->Strings[j])
						break;
				}

				param = param + "\"" + iterator_currency->first + "\",";
			}
		}
		//-- удаление лишней запятой --//
		param.Delete(param.Length(),1);

		param = param + "]";
	}
	//-- ************************************ --//


	//-- статус --//
    //-- ************************************ --//
	if(EnabledCheck->Checked)
		param = param + ",\"enabled\":1";
	else
		param = param + ",\"enabled\":0";
	//-- ************************************ --//


	//-- заметки --//
    //-- ************************************ --//
	if(!NotesMemo->Text.IsEmpty())
	{
		param = param + ",\"notes\":\"" + MainForm->Encoder->EncodeString( NotesMemo->Text, IndyTextEncoding_UTF8() ) + "\"";
	}
	//-- ************************************ --//


	//-- отправка запроса добавления на сервер --//
	MainForm->engine->Send("addLine", param, "CheckAddLine");

	//-- закрытие формы добавления --//
	Close();
}




//-- ФУНКЦИЯ ВЫДЕЛЕНИЯ ВСЕХ ИСТОЧНИКОВ --//
void __fastcall TAddFormLines::AllSourcesCheck_OneClick(TObject *Sender)
{

	if(AllSourcesCheck->State == true)
	{
		//-- если все источники не выделены --//

		for(int sources_count=0; sources_count != SourcesCheckList->Items->Count; sources_count ++)
		{
			SourcesCheckList->Checked[sources_count] = true;
		}
	}
	else
	{
		//-- если все источники выделены --//

		for(int sources_count=0; sources_count != SourcesCheckList->Items->Count; sources_count ++)
		{
			SourcesCheckList->Checked[sources_count] = false;
		}
    }
}



//-- ФУНКЦИЯ ВЫДЕЛЕНИЯ ВСЕХ ВАЛЮТ --//
void __fastcall TAddFormLines::AllCurrencysCheck_OneClick(TObject *Sender)
{
	if(AllCurrencysCheck->State == true)
	{
		//-- если все валюты не выделены --//

		for(int currencys_count=0; currencys_count != CurrencysCheckList->Items->Count; currencys_count ++)
		{
			CurrencysCheckList->Checked[currencys_count] = true;
		}
	}
	else
	{
		//-- если все валюты выделены --//

		for(int currencys_count=0; currencys_count != CurrencysCheckList->Items->Count; currencys_count ++)
		{
			CurrencysCheckList->Checked[currencys_count] = false;
		}
	}

	//-- обновление списка базовых валют --//
	UpdateBaseCurrencys();
}



//-- ФУНКЦИЯ ВЫДЕЛЕНИЯ ВСЕХ БАЗОВЫХ ВАЛЮТ --//
void __fastcall TAddFormLines::AllBasesCheck_OneClick(TObject *Sender)
{
	if(AllBasesCheck->State == true)
	{
		//-- если все валюты не выделены --//

		for(int bases_count=0; bases_count != BasesCheckList->Items->Count; bases_count ++)
		{
			BasesCheckList->Checked[bases_count] = true;
		}
	}
	else
	{
		//-- если все валюты выделены --//

		for(int bases_count=0; bases_count != BasesCheckList->Items->Count; bases_count ++)
		{
			BasesCheckList->Checked[bases_count] = false;
		}
	}
}




//-- ФУНКЦИЯ ОБРАБОТКИ ИЗМЕНЕНИЯ ФЛАЖКА ВАЛЮТ --//
void __fastcall TAddFormLines::CurrencysCheckListClickCheck(TObject *Sender)
{
	UpdateBaseCurrencys();
}




//---------------------------------------------------------//
//------------- ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ КЛАССА -------------//
//---------------------------------------------------------//


//-- ФУНКЦИЯ ОБНОВЛЕНИЯ БАЗОВЫХ ВАЛЮТ ДЛЯ ВОЗМОЖНОСТИ ИХ ВЫБОРА --//
void TAddFormLines::UpdateBaseCurrencys()
{
    //-- запоминание помеченых элементов из списка базовых валют --//
	std::vector< UnicodeString > activy_bases;

	for(int bases_count=0; bases_count != BasesCheckList->Items->Count; bases_count ++)
	{
		if(BasesCheckList->Checked[bases_count])
			activy_bases.push_back( BasesCheckList->Items->Strings[bases_count] );
	}

	//-- очистка базовых валют --//
	BasesCheckList->Clear();

	//-- добавление только выбранных валют из вкладки валют --//
	for(int currencys_count=0; currencys_count != CurrencysCheckList->Items->Count; currencys_count ++)
	{
		if(CurrencysCheckList->Checked[currencys_count])
			BasesCheckList->Items->Add( CurrencysCheckList->Items->Strings[currencys_count] );
	}

	//-- выбор отмеченных до этого активных базовых валют --//
	for(std::vector< UnicodeString >::iterator iterator_base = activy_bases.begin(); iterator_base != activy_bases.end(); iterator_base ++)
	{
		for(int i=0; i != BasesCheckList->Items->Count; i ++)
		{
			if(BasesCheckList->Items->Strings[i] == *iterator_base)
				BasesCheckList->Checked[i] = true;
		}
	}
}
