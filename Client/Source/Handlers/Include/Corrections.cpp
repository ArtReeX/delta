//-- ******************************************* --//
//-- *************** Corrections *************** --//
//-- ******************************************* --//

#include <vcl.h>

//-- подключение заголовочного файла --//
#include "Corrections.h"



namespace HandlersNS
{


	//-- ‘”Ќ ÷»я-ќЅ–јЅќ“„»  ѕќЋ”„≈Ќ»я  ќ––≈ ÷»… --//
	void getCorrections(TJSONObject *json_object_parse)
	{
        //-- обьекты дл€ работы с JSON --//
		TJSONObject *json_object;
		TJSONArray 	*json_array;

		//-- получение массива с источниками --//
		if(json_object_parse->Get("param"))
		{
			json_object = dynamic_cast<TJSONObject*>( json_object_parse->Get("param")->JsonValue );


			if( json_object->Get("corrections") )
			{
				json_array =  dynamic_cast<TJSONArray*>( json_object->Get("corrections")->JsonValue );

				//-- очистка идентификаторов --//
				MainForm->engine->Data()->map_corrections.clear();

				//-- очистка таблиц --//
				MainForm->ClearStringGrid( MainForm->Corrections_StringGrid );


				//-- парсинг массива с коррекци€ми --//
				for(int i=0; i != json_array->Size(); i++)
				{
					json_object = dynamic_cast<TJSONObject*>( json_array->Get(i) );

					SCorrection corrections;

					//-- добавление об€зательных значений в таблицу --//
					corrections.sourceId = json_object->GetValue("sourceId")->Value();

					corrections.currOut = json_object->GetValue("currOut")->Value();

					corrections.currIn = json_object->GetValue("currIn")->Value();

					corrections.fee = json_object->GetValue("fee")->Value();

					corrections.enabled = json_object->GetValue("enabled")->Value();

					//-- добавление необ€зательных значений в таблицу --//
					if( json_object->GetValue("notes") )
						corrections.notes = MainForm->Decoder->DecodeString( json_object->GetValue("notes")->Value(), IndyTextEncoding_UTF8() );


					//-- запись идентификатора --//
					MainForm->engine->Data()->map_corrections.insert( std::make_pair( json_object->GetValue("id")->Value().ToInt(), corrections ));
				}


				//-- сортировка по заданому типу --//
				MainForm->engine->SortCorrections(MainForm->engine->Config()->SortCorrections, MainForm->engine->Config()->SortCorrectionsInd);

                //-- обновление таблицы --//
				MainForm->UpdateCorrections(MainForm->Corrections_StringGrid->Row, true);
			}
		}
	}



	//-- ‘”Ќ ÷»я-ќЅ–јЅќ“„»  –≈«”Ћ№“ј“ј ƒќЅј¬Ћ≈Ќ»я  ќ––≈ ÷»» --//
	void CheckAddCorrection(TJSONObject *json_object_parse)
	{

		//-- обьект дл€ работы с JSON --//
		TJSONObject *json_object;

		//-- получение результата изменени€ источника --//
		json_object = dynamic_cast<TJSONObject*>( json_object_parse->Get("param")->JsonValue );

		//-- если изменение прошло успешно --//
		if(json_object->GetValue("result")->Value().ToInt() == 0)
		{
			//ShowMessage("Adding completed successfully.");
		}
		else
		{
			if(json_object->GetValue("result")->Value().ToInt() == 1)
			{
				ShowMessage("Correction with the same combination of fields SourceID, CurrOut, CurrLn already exists.");
			}
		}
	}



	//-- ‘”Ќ ÷»я-ќЅ–јЅќ“„»  –≈«”Ћ№“ј“ј »«ћ≈Ќ≈Ќ»я  ќ––≈ ÷»» --//
	void CheckEditCorrection(TJSONObject *json_object_parse)
	{

		//-- обьект дл€ работы с JSON --//
		TJSONObject *json_object;

		//-- получение результата изменени€ источника --//
		json_object = dynamic_cast<TJSONObject*>( json_object_parse->Get("param")->JsonValue );

		//-- если изменение прошло успешно --//
		if(json_object->GetValue("result")->Value().ToInt() == 0)
		{
			//ShowMessage("Change is successful.");
		}
		else
		{
			if(json_object->GetValue("result")->Value().ToInt() == 1)
			{
				ShowMessage("Correction with the same combination of fields Source ID, CurrOut, CurrLn already exists.");
			}
			else
			{
				if(json_object->GetValue("result")->Value().ToInt() == 2)
				{
					ShowMessage("Wrong ID.");
				}
			}
		}
	}



	//-- ‘”Ќ ÷»я-ќЅ–јЅќ“„»  –≈«”Ћ№“ј“ј ”ƒјЋ≈Ќ»я  ќ––≈ ÷»» --//
	void CheckDeleteCorrection(TJSONObject *json_object_parse)
	{

		//-- обьект дл€ работы с JSON --//
		TJSONObject *json_object;

		//-- получение результата изменени€ источника --//
		json_object = dynamic_cast<TJSONObject*>( json_object_parse->Get("param")->JsonValue );

		//-- если изменение прошло успешно --//
		if(json_object->GetValue("result")->Value().ToInt() == 0)
		{
			//ShowMessage("Removal completed successfully.");
		}
		else
		{
			if(json_object->GetValue("result")->Value().ToInt() == 1)
			{
				ShowMessage("Wrong value of the ID field.");
			}
		}
	}





	//-- ‘”Ќ ÷»я-ќЅ–јЅќ“„»  »«ћ≈Ќ≈Ќ»я  ќ––≈ ÷»» --//
	void editCorrection(TJSONObject *json_object_parse)
	{

	}




	//-- ‘”Ќ ÷»я-ќЅ–јЅќ“„»  ƒќЅј¬Ћ≈Ќ»я  ќ––≈ ÷»» --//
	void addCorrection(TJSONObject *json_object_parse)
	{

	}




	//-- ‘”Ќ ÷»я-ќЅ–јЅќ“„»  ”ƒјЋ≈Ќ»я  ќ––≈ ÷»» --//
	void deleteCorrection(TJSONObject *json_object_parse)
	{

	}

}



