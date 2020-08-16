template <class T>
class cCallback
{
public:
	typedef void (T::*TCallBackIntFunction)(int t);
	void SetCallBack(T* pCallBackClass, TCallBackIntFunction pCallBackFunction)
	{
		if (pCallBackFunction && pCallBackClass)
		{
			m_pCallBackFunction = pCallBackFunction;
			m_pCallBackClass = pCallBackClass;
		}
	}
	void StartCallBackFunction(int t)
	{
		(m_pCallBackClass->*m_pCallBackFunction)(t);
	}
private:
	TCallBackIntFunction m_pCallBackFunction;
	T* m_pCallBackClass;
};