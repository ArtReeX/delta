//-----------------------------------------------------------//
//----------------- �������������� ������ -------------------//
//---------------------------(H)-----------------------------//

#ifndef TIMECOLLECTH
#define TIMECOLLECTH

//-- �������� ������ � ��������� ����� ������ --//
struct STimeCollect
{
	//-- ����� ������ ����� ������ --//
	unsigned int StartCollectDD = 00;
	unsigned int StartCollectMM = 00;
	unsigned int StartCollectYY = 00;
	unsigned int StartCollectHH = 00;
	unsigned int StartCollectNN = 00;
	unsigned int StartCollectSS = 00;

	//-- ����� ����� ����� ������ --//
	unsigned int EndCollectDD = 00;
	unsigned int EndCollectMM = 00;
	unsigned int EndCollectYY = 00;
	unsigned int EndCollectHH = 00;
	unsigned int EndCollectNN = 00;
	unsigned int EndCollectSS = 00;
};

#endif
