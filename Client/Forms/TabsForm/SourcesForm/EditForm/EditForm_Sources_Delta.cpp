//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "EditForm_Sources_Delta.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEditFormSources *EditFormSources;
//---------------------------------------------------------------------------
__fastcall TEditFormSources::TEditFormSources(TComponent* Owner)
	: TForm(Owner)
{
}



//---------------------------------------------------------//
//------------ ОБРАБОТЧИКИ СТАНДАРТНЫХ СОБЫТИЙ ------------//
//---------------------------------------------------------//

//-- ФУНКЦИЯ ПОКАЗА ФОРМЫ --//
void __fastcall TEditFormSources::FormShow(TObject *Sender)
{
	//-- поиск по ID --//

	MSource::iterator map_iterator = MainForm->engine->Data()->map_sources.find( MainForm->Sources_StringGrid->Cells[0][MainForm->Sources_StringGrid->Row].ToInt() );


	//-- изначальное заполнение полей ввода --//
	NameEdit->Text = map_iterator->second.name;

	UrlEdit->Text = map_iterator->second.url;

	DataUrlEdit->Text = map_iterator->second.dataurl;

	GetterEdit->Text = map_iterator->second.getter;

	EnabledCheck->Checked = map_iterator->second.enabled.ToInt();

	NotesEdit->Text = map_iterator->second.notes;

}



//---------------------------------------------------------//
//------------- ОБРАБОТЧИКИ СОБЫТИЙ ЭЛЕМЕНТОВ -------------//
//---------------------------------------------------------//


//-- ФУНКЦИЯ НАЖАТИЯ НА КНОПКУ "Save" --//
void __fastcall TEditFormSources::SaveButton_OneClick(TObject *Sender)
{

	//-- поиск по ID --//

	MSource::iterator map_iterator = MainForm->engine->Data()->map_sources.find( MainForm->Sources_StringGrid->Cells[0][MainForm->Sources_StringGrid->Row].ToInt() );


	//-- ФОРМИРОВАНИЕ СТРОКИ ИЗМЕНЕНИЯ С СТАНДАРТНЫМИ ПАРАМЕТРАМИ --//
	UnicodeString param = "\"id\":\"" + UnicodeString( map_iterator->first ) + "\"";


	//-- ФОРМИРОВАНИЕ СТРОКИ ИЗМЕНЕНИЯ С ДОПОЛНИТЕЛЬНЫМИ ПАРАМЕТРАМИ --//
    //-- ************************************ --//
	if(!NameEdit->Text.IsEmpty() && NameEdit->Text != map_iterator->second.name)
	{
		param = param + ",\"name\":\"" + MainForm->Encoder->EncodeString( NameEdit->Text, IndyTextEncoding_UTF8() ) + "\"";
	}
	//-- ************************************ --//

	//-- ************************************ --//
	if(!UrlEdit->Text.IsEmpty() && UrlEdit->Text != map_iterator->second.url)
	{
		param = param + ",\"url\":\"" + MainForm->Encoder->EncodeString( UrlEdit->Text, IndyTextEncoding_UTF8() ) + "\"";
	}
	//-- ************************************ --//

	//-- ************************************ --//
	if(!DataUrlEdit->Text.IsEmpty() && DataUrlEdit->Text != map_iterator->second.dataurl)
	{
		param = param + ",\"dataurl\":\"" + MainForm->Encoder->EncodeString( DataUrlEdit->Text, IndyTextEncoding_UTF8() ) + "\"";
	}
	//-- ************************************ --//

	//-- ************************************ --//
	if(!GetterEdit->Text.IsEmpty() && GetterEdit->Text != map_iterator->second.getter)
	{
		param = param + ",\"getter\":\"" + MainForm->Encoder->EncodeString( GetterEdit->Text, IndyTextEncoding_UTF8() ) + "\"";
	}
	//-- ************************************ --//

	//-- ************************************ --//
	if(EnabledCheck->Checked != map_iterator->second.enabled)
	{
        if(EnabledCheck->Checked)
			param = param + ",\"enabled\":1";
		else
			param = param + ",\"enabled\":0";
	}
	//-- ************************************ --//

	//-- ************************************ --//
	if(NotesEdit->Text != map_iterator->second.notes)
	{
		if(NotesEdit->Text.IsEmpty())
			NotesEdit->Text = " ";

		param = param + ",\"notes\":\"" + MainForm->Encoder->EncodeString( NotesEdit->Text, IndyTextEncoding_UTF8() ) + "\"";
	}
	//-- ************************************ --//



	//-- отправка запроса добавления на сервер --//
	MainForm->engine->Send("editSource", param, "CheckEditSource");

	//-- закрытие формы добавления --//
	Close();

}

