#pragma once

#include "resource.h"

class CMFCRasterizerApp : public CWinApp
{
public:  
    CMFCRasterizerApp();
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    DECLARE_MESSAGE_MAP()
};

extern CMFCRasterizerApp theApp;