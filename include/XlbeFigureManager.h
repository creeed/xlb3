#ifndef __XLBE_FIGURE_MANAGER_H__
#define __XLBE_FIGURE_MANAGER_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//���ߣ����ֱ�
//QQ: 597389076
//mail: creednew2000@163.com

//���������������Ͷ��� ��ɾ��лл��

///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XlbePrereqs.h"
#include "XlbeSingleton.h"
#include "XlbeResourceManager.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

class Figure;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Figure_Manager : public Resource_Manager, public Singleton<Figure_Manager>
{
public:
    Figure_Manager();
    ~Figure_Manager();

	static Figure_Manager* singleton();

    Figure* get_figure(const std::string& str);

protected:
	virtual Resource *create_resource_impl(const std::string &xml_file, const std::string &resource_group) ;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif