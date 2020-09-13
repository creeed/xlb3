#ifndef __XLBE_SINGLETON_H__
#define __XLBE_SINGLETON_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//���ߣ����ֱ�
//QQ: 597389076
//mail: creednew2000@163.com

//���������������Ͷ��� ��ɾ��лл��

//////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

//////////////////////////////////////////////////////////////////////////////////
template <typename T> 
class  Singleton
{
public:
    Singleton()
    {
        assert( !singleton_ );
        singleton_ = static_cast<T*>(this);
    }

    ~Singleton( )
    { 
        assert( singleton_ );  
        singleton_ = 0;  
    }

    static T* singleton()
    { 
        return (singleton_);
    }

protected:
    static T* singleton_ ;
};

//////////////////////////////////////////////////////////////////////////////////
}

#endif