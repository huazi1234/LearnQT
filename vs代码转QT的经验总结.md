1.BOOL --->bool  FALSE--false  TRUE ---- true

2. 一些windows自定义的宏 需要重新定义

   如 WORD DWORD BYTE  ULONGLONG，UINT
       TCHAR 
       MAX_PATH
       
       转为qt自定义的一些类型: quint8 quint16,quint32,quint64等
       NULL----------nullptr
3。MFC的类转为 QT类:
   CString  -------QString 
   vector --------- QVector 这个是C++的类，也可以不换
   
   CSysAnsocket 换为 Qtcpsocket Qudpsocket 等
   
   CTime ---》QDateTime  QDate  QTim
   
   SYSTEMTIME等结构需要自己重新定义。
   
4. 去掉try catch ，CExcption等

5. 不能使用HWND等句柄

6. 不能用USE_CONVERSION，W2A，A2W等
