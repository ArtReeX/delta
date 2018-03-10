//-----------------------------------------------------------//
//-------------------- ДВИЖОК ПРОГРАММЫ ---------------------//
//---------------------------(H)-----------------------------//

#ifndef TENGINEH
#define TENGINEH

//-- подключение интеллектуальных указателей --//
#include <memory>

//-- подключение Stap-библиотеки --//
#include <TStapLIB.h>

//-- подключение Win-библиотеки --//
#include <windows.h>

//-- подключение параметров --//
#include "Config.h"

//-- подключение базы данных --//
#include "TData.h"

//-- подключение средств для работы с *ini файлами  --//
#include <IniFiles.hpp>

//-- подключение BASE64 конвертеров для шифрования Логина/Пароля  --//
#include <IdBaseComponent.hpp>
#include <IdCoder.hpp>
#include <IdCoder3to4.hpp>
#include <IdCoderMIME.hpp>



namespace TEngineNS
{

	class TEngine : public TStapLIBNS::TStapLIB, public TDataNS::TData
	{

	private:

		//-- путь к файлу конфигурации --//
		UnicodeString way_to_config_file;

		//-- имя файла конфигурации --//
		UnicodeString name_config_file;

		//-- индикатор необходимости перезапуска при первом создании необходимых файлов --//
		bool need_to_restart;

		//-- BASE64 конвертеры --//
		std::shared_ptr< TIdEncoderMIME > encoder64;
		std::shared_ptr< TIdDecoderMIME > decoder64;

		//-- параметры программы --//
		SConfig config;

		//-- создание хранилища данных --//
		SData data;

		//-- создание обьекта для *ini файла --//
		std::shared_ptr< TIniFile > ini_config;

		//-- шифровщик/дешифровщик текста --//
		UnicodeString XOR_Crypt(UnicodeString In, UnicodeString Pass) const;

	public:


		//-- стандартный конструктор --//
		TEngine();

		//-- стандартный деструктор --//
		~TEngine();

		//-- возврат необходимости перезапуска при первом создании необходимых файлов --//
		bool NeedToRestart() const;

		//-- возврат конфигурации программы --//
		SConfig* Config();

        //-- загрузка параметров программы --//
		void LoadConfig();

		//-- сохранение параметров программы --//
		void SaveConfig();

		//-- функция конвертирования числовой строки с запятой в числовую строку с точкой --//
		UnicodeString FloatWithDots(const UnicodeString FloatNum) const;

	};

};

#endif
