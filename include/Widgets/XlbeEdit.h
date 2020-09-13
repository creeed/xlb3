#ifndef __XLBE_EDIT_H__
#define __XLBE_EDIT_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeWindow.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

#define	ES_ENGLISH_AVAILABLE	0x0000		
#define	ES_IME_AVAILABLE		0x0001		
#define	ES_MASK_CHARACTER		0x0002		
#define	ES_SINGLELINE			0x0004		
#define	ES_HAVE_FOCUS			0x0008		//为当前拥有输入焦点的窗口

//////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Edit : public Window
{
public:
	Edit(const std::string &name) ;
	virtual ~Edit() ;

public:
	int get_format() const { return format_; }
	void set_format(int flag) { format_ = flag; }

	int get_limit_text() const { return limit_text_; }
	void set_limit_text(int len) { limit_text_ = len; }

public:
	virtual void update(float ftime, float dt);
	virtual void draw();

	virtual void on_got_focus();
	virtual void on_lost_focus();	

	virtual void on_key_char(int c);
	virtual void on_key_down(Key_Code key);
	virtual void on_mouse_down(const Point &pt, Mouse_ButtonID button_id, int click_count);

public:
	virtual void set_text(const std::string& text) ;

protected:
	int insert_char(int c);
	int	insert_char(char low, char high);

protected:
	int caret_pos_;
	int	caret_line_index_;			//插入符所在的行位置
	int text_pos_;
	int limit_text_;
    uint32_t format_;

	std::string mask_text_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif
