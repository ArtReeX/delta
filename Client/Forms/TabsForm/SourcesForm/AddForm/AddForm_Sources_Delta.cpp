//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AddForm_Sources_Delta.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAddFormSources *AddFormSources;
//---------------------------------------------------------------------------
__fastcall TAddFormSources::TAddFormSources(TComponent* Owner)
	: TForm(Owner)
{
}


//---------------------------------------------------------//
//------------- ОБРАБОТЧИКИ СОБЫТИЙ ЭЛЕМЕНТОВ -------------//
//---------------------------------------------------------//

//-- ФУНКЦИЯ ОБРАБОТКИ ПО НАЖАТИЮ НА КНОПКУ "Add" --//
void __fastcall TAddFormSources::AddButton_OneClick(TObject *Sender)
{
    //-- проверка правильности введённых данных --//
	if(NameEdit->Text.IsEmpty() || GetterEdit->Text.IsEmpty())
		ShowMessage("Required fields are not filled.");
	else
	{
		//-- ФОРМИРОВАНИЕ СТРОКИ ДОБАВЛЕНИЯ С СТАНДАРТНЫМИ ПАРАМЕТРАМИ --//
		UnicodeString param = "\"name\":\"" + MainForm->Encoder->EncodeString( NameEdit->Text, IndyTextEncoding_UTF8() ) + "\"," +
							  "\"getter\":\"" + MainForm->Encoder->EncodeString( GetterEdit->Text, IndyTextEncoding_UTF8() ) + "\"";


		//-- ФОРМИРОВАНИЕ СТРОКИ ДОБАВЛЕНИЯ С ДОПОЛНИТЕЛЬНЫМИ ПАРАМЕТРАМИ --//
		//-- ************************************ --//
		if(!UrlEdit->Text.IsEmpty())
		{
			param = param + ",\"url\":\"" + MainForm->Encoder->EncodeString( UrlEdit->Text, IndyTextEncoding_UTF8() ) + "\"";
		}
		//-- ************************************ --//

		//-- ************************************ --//
		if(!DataUrlEdit->Text.IsEmpty())
		{
			param = param + ",\"dataurl\":\"" + MainForm->Encoder->EncodeString( DataUrlEdit->Text, IndyTextEncoding_UTF8() ) + "\"";
		}
		//-- ************************************ --//

		//-- ************************************ --//
		if(EnabledCheck->Checked)
			param = param + ",\"enabled\":1";
		else
			param = param + ",\"enabled\":0";
		//-- ************************************ --//

		//-- ************************************ --//
		if(!NotesEdit->Text.IsEmpty())
		{
			param = param + ",\"notes\":\"" + MainForm->Encoder->EncodeString( NotesEdit->Text, IndyTextEncoding_UTF8() ) + "\"";
		}
		//-- ************************************ --//



		//-- отправка запроса добавления на сервер --//
		MainForm->engine->Send("addSource", param, "CheckAddSource");

		//-- закрытие формы добавления --//
		Close();
	}
}

