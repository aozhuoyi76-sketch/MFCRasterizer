#pragma once
#include "Rasterizer.h"

class CChildView : public CWnd
{
public:
    CChildView();
    virtual ~CChildView();

protected:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnPaint();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    DECLARE_MESSAGE_MAP()

private:
    Rasterizer m_raster;
    Matrix3 m_world;
    float m_angleDeg;
    float m_tx, m_ty;
    float m_sx, m_sy;
    CRect m_client;
    void DrawScene(CDC& dc);
    void UpdateTransform();
};