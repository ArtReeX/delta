//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "EditForm_Currencys_Delta.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEditFormCurrencys *EditFormCurrencys;
//---------------------------------------------------------------------------
__fastcall TEditFormCurrencys::TEditFormCurrencys(TComponent* Owner)
	: TForm(Owner)
{
}



//---------------------------------------------------------//
//------------ ����������� ����������� ������� ------------//
//---------------------------------------------------------//

//-- ������� ������ ����� --//
void __fastcall TEditFormCurrencys::FormShow(TObject *Sender)
{
	//-- ����� ID --//
	MCurrency::iterator map_iterator = MainForm->engine->Data()->map_currencys.find( MainForm->Currencys_StringGrid->Cells[0][MainForm->Currencys_StringGrid->Row].ToInt() );


	//-- ����������� ���������� ����� ����� --//
	NameEdit->Text = map_iterator->second.name;

	ShortEdit->Text = map_iterator->second.shortn;

	FeeEdit->Text = MainForm->engine->FloatWithDots( map_iterator->second.fee );

	MinSumEdit->Text = map_iterator->second.minSum;

	BaseCheck->Checked = map_iterator->second.base.ToInt();

	EnabledCheck->Checked = map_iterator->second.enabled.ToInt();

	NotesEdit->Text = map_iterator->second.notes;

}



//---------------------------------------------------------//
//------------- ����������� ������� ��������� -------------//
//---------------------------------------------------------//


//-- ������� ������� �� ������ "Save" --//
void __fastcall TEditFormCurrencys::SaveButton_OneClick(TObject *Sender)
{

    //-- ����� ID --//
	MCurrency::iterator map_iterator = MainForm->engine->Data()->map_currencys.find( MainForm->Currencys_StringGrid->Cells[0][MainForm->Currencys_StringGrid->Row].ToInt() );



	//-- ������������ ������ ��������� � ������������ ����������� --//
	UnicodeString param = "\"id\":\"" + UnicodeString( map_iterator->first ) + "\"";



	//-- ������������ ������ ��������� � ��������������� ����������� --//
	//-- ************************************ --//
	if(!NameEdit->Text.IsEmpty() && NameEdit->Text != map_iterator->second.name)
	{
		param = param + ",\"name\":\"" + MainForm->Encoder->EncodeString( NameEdit->Text, IndyTextEncoding_UTF8() ) + "\"";
	}
	//-- ************************************ --//

	//-- ************************************ --//
	if(!ShortEdit->Text.IsEmpty() && ShortEdit->Text != map_iterator->second.shortn)
	{
		param = param + ",\"short\":\"" + MainForm->Encoder->EncodeString( ShortEdit->Text, IndyTextEncoding_UTF8() ) + "\"";
	}
	//-- ************************************ --//

	//-- ************************************ --//
	if(!FeeEdit->Text.IsEmpty() && MainForm->engine->FloatWithDots( FeeEdit->Text ) != map_iterator->second.fee)
	{
		param = param + ",\"fee\":" + MainForm->engine->FloatWithDots( FeeEdit->Text );
	}
	//-- ************************************ --//

	//-- ************************************ --//
	if(!MinSumEdit->Text.IsEmpty() && MinSumEdit->Text != map_iterator->second.minSum)
	{
		param = param + ",\"minSum\":" + MinSumEdit->Text.ToInt();
	}
	//-- ************************************ --//

	//-- ************************************ --//
	if(BaseCheck->Checked != map_iterator->second.base)
	{
		if(BaseCheck->Checked)
			param = param + ",\"base\":1";
		else
			param = param + ",\"base\":0";
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



	//-- �������� ������� ���������� �� ������ --//
	MainForm->engine->Send("editCurrency", param, "CheckEditCurrency");

	//-- �������� ����� ���������� --//
	Close();

}

