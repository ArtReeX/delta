//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AddForm_Currencys_Delta.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAddFormCurrencys *AddFormCurrencys;
//---------------------------------------------------------------------------
__fastcall TAddFormCurrencys::TAddFormCurrencys(TComponent* Owner)
	: TForm(Owner)
{
}



//---------------------------------------------------------//
//------------- ����������� ������� ��������� -------------//
//---------------------------------------------------------//

//-- ������� ��������� �� ������� �� ������ "Add" --//
void __fastcall TAddFormCurrencys::AddButton_OneClick(TObject *Sender)
{
    //-- �������� ������������ �������� ������ --//
	if(NameEdit->Text.IsEmpty() || ShortEdit->Text.IsEmpty())
		ShowMessage("Required fields are not filled.");
	else
	{
		//-- ������������ ������ ���������� � ������������ ����������� --//
		UnicodeString param = "\"name\":\"" + MainForm->Encoder->EncodeString( NameEdit->Text, IndyTextEncoding_UTF8() ) + "\"," +
							  "\"short\":\"" + MainForm->Encoder->EncodeString( ShortEdit->Text, IndyTextEncoding_UTF8() ) + "\"";


		//-- ������������ ������ ���������� � ��������������� ����������� --//
		//-- ************************************ --//
		if(!FeeEdit->Text.IsEmpty())
		{
			param = param + ",\"fee\":" + MainForm->engine->FloatWithDots( FeeEdit->Text );
		}
		//-- ************************************ --//

		//-- ************************************ --//
		if(!MinSumEdit->Text.IsEmpty())
		{
			param = param + ",\"minSum\":" +  MinSumEdit->Text.ToInt();
		}
		//-- ************************************ --//

		//-- ************************************ --//
		if(BaseCheck->Checked)
			param = param + ",\"base\":1";
		else
			param = param + ",\"base\":0";
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



		//-- �������� ������� ���������� �� ������ --//
		MainForm->engine->Send("addCurrency", param, "CheckAddCurrency");

		//-- �������� ����� ���������� --//
		Close();
	}
}

