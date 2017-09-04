
#ifndef __BARRAGE_QTTS_H__
#define __BARRAGE_QTTS_H__

#include "stdafx.h"

class barrage_qtts
{
public:
	barrage_qtts();
	~barrage_qtts();

	//µÇÂ½
	int Login();

	int text_to_speech(const char* src_text, const char*  des_path, const char* params);

	void Logout();
};


#endif // __BARRAGE_QTTS_H__

