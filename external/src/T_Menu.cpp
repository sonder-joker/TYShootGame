//*******************************************************************
// TinyEngine引擎  
// 作者: 万立中(WanLizhong)
// 博客: www.wanlizhong.com 
// 日期: 2013-08-02
// 更新: 2020-12-20
// 版权所有 2007-2021 万立中
// (C) 2007-2021 WanLizhong All Rights Reserved
//*******************************************************************

#include "T_Menu.h"

T_Menu::T_Menu() {
    m_index = -1;
    key_index = 0;
    isItemFocused = false;
    bkImageAlpha = 255;

    //m_MoveSound = NULL;
    //m_ClickSound = NULL;

    //+++++++++++++++++++++
    wnd_width = WIN_WIDTH;
    wnd_height = WIN_HEIGHT;
    bkgX = 0;
    bkgY = 0;
    btnAlphaLevel = 255;
    backColor = NULL;
    //+++++++++++++++++++++
}

T_Menu::~T_Menu(void) {
    DestroyAll();
}

/*
void T_Menu::SetMoveSound(AudioDXBuffer* ms_buffer)
{
	m_MoveSound = ms_buffer;
}

void T_Menu::SetClickSound(AudioDXBuffer* mc_buffer)
{
	m_ClickSound = mc_buffer;
}
*/

//设置菜单背景图片
void T_Menu::SetMenuBkg(wstring img_path, int x, int y, int alphaLevel) {
    if (img_path.length() > 0) {
        gm_menuBkg.LoadImageFile(img_path.c_str());
        bkImageAlpha = alphaLevel;
        bkgX = x;
        bkgY = y;
    }
}

void T_Menu::SetMenuBkgColor(COLORREF bkgColor, int x, int y, int alphaLevel) {
    backColor = bkgColor;
    bkgX = x;
    bkgY = y;
    bkImageAlpha = alphaLevel;
}

//添加正常菜单图片
void T_Menu::SetBtnBmp(wstring img_path, int btnWidth, int btnHeight, int btnAlpha) {
    if (img_path.length() > 0) {
        BtnDIB.LoadImageFile(img_path.c_str());
        if (BtnDIB.GetBmpHandle() != NULL) {
            menu_info.width = btnWidth;
            menu_info.height = btnHeight;
        }
        btnAlphaLevel = btnAlpha;
    }
}

//添加菜单文字项目
void T_Menu::AddMenuItem(MENUITEM menuItem) {
    gm_menuItems.push_back(menuItem);
    int len = (int) (menuItem.ItemName.length());
    if (MaxMenuItemLen < len)
        MaxMenuItemLen = len;
}

//设置首菜单项的坐标及菜单间隔距离
void T_Menu::SetMenuInfo(MENU_INFO menuInfo) {
    menu_info = menuInfo;
}

//菜单绘制
void T_Menu::DrawMenu(HDC hdc) {
    if (backColor != NULL) {
        T_Graph::PaintBlank(hdc, bkgX, bkgY, wnd_width, wnd_height, backColor, bkImageAlpha);
    }

    if (gm_menuBkg.GetBmpHandle() != NULL) {
        gm_menuBkg.PaintImage(hdc, bkgX, bkgY, wnd_width, wnd_height, bkImageAlpha);
    }

    int w = menu_info.width;
    int h = menu_info.height;

    int FontHeight;
    int px = 0;
    int w_px = w / (MaxMenuItemLen + 1);    //计算每个字所占的像素
    int h_px = (int) ((float) (h / 2.5));
    if (w_px > h_px) {
        px = h_px;
    } else {
        px = w_px;
    }
    FontHeight = (px * 72) / 96;        //根据每个字的像素计算字号

    if (isItemFocused == FALSE) {
        Gdiplus::RectF Rec;
        vector<MENUITEM>::iterator iter;
        for (iter = gm_menuItems.begin(); iter != gm_menuItems.end(); iter++) {
            int x = iter->pos.x;
            int y = iter->pos.y;

            // 绘制按钮图像
            if (&BtnDIB != NULL) {
                BtnDIB.PaintRegion(BtnDIB.GetBmpHandle(), hdc, x, y, 0, 0, w, h, 1, 0, btnAlphaLevel);
            }
            Rec.X = (float) x;
            Rec.Y = (float) y;
            Rec.Width = (float) w;
            Rec.Height = (float) h;

            // 绘制按钮文字
            wstring item = iter->ItemName.c_str();
            T_Graph::PaintText(hdc, Rec, item.c_str(), (REAL) FontHeight, menu_info.fontName,
                               menu_info.normalTextColor, GetFontStyle(), GetAlignment());
        }
    }

    if (isItemFocused == TRUE) {
        int mIndex = 0;
        Gdiplus::RectF Rec;
        vector<MENUITEM>::iterator iter;
        for (iter = gm_menuItems.begin(); iter != gm_menuItems.end(); iter++) {
            int x = iter->pos.x;
            int y = iter->pos.y;

            Rec.X = (float) x;
            Rec.Y = (float) y;
            Rec.Width = (float) w;
            Rec.Height = (float) h;

            if (mIndex != m_index) {
                if (&BtnDIB != NULL) {
                    BtnDIB.PaintRegion(BtnDIB.GetBmpHandle(), hdc, x, y, 0, 0, w, h, 1, 0, btnAlphaLevel);
                }

                wstring item = iter->ItemName.c_str();
                T_Graph::PaintText(hdc, Rec, item.c_str(), (REAL) FontHeight, menu_info.fontName,
                                   menu_info.normalTextColor, GetFontStyle(), GetAlignment());
            }

            if (mIndex == m_index) {
                if (&BtnDIB != NULL) {
                    BtnDIB.PaintRegion(BtnDIB.GetBmpHandle(), hdc, x, y, 0, h, w, h, 1, 0, btnAlphaLevel);
                }

                wstring item = iter->ItemName.c_str();
                T_Graph::PaintText(hdc, Rec, item.c_str(), (REAL) FontHeight, menu_info.fontName,
                                   menu_info.focusTextColor, GetFontStyle(), GetAlignment());
            }

            mIndex = mIndex + 1;
        }
    }
}

//根据当前鼠标坐标计算菜单项索引号
int T_Menu::GetMenuIndex(int x, int y) {
    int Index = -1;
    POINT pt;
    pt.x = x;
    pt.y = y;
    int w = menu_info.width;
    int h = menu_info.height;
    RECT rec;

    int iCount = 0;
    vector<MENUITEM>::iterator iter;
    for (iter = gm_menuItems.begin(); iter != gm_menuItems.end(); iter++) {
        rec.left = iter->pos.x;
        rec.top = iter->pos.y;
        rec.right = rec.left + w;
        rec.bottom = rec.top + h;

        if (PtInRect(&rec, pt)) {
            return iCount;
        }
        iCount++;
    }
    return Index;
}

StringAlignment T_Menu::GetAlignment() {
    StringAlignment sAlign;
    if (menu_info.align == 0) {
        sAlign = StringAlignmentNear;
    }
    if (menu_info.align == 1) {
        sAlign = StringAlignmentCenter;
    }
    if (menu_info.align == 2) {
        sAlign = StringAlignmentFar;
    }
    return sAlign;
}

FontStyle T_Menu::GetFontStyle() {
    FontStyle fStyle;
    if (menu_info.isBold == true) {
        fStyle = FontStyleBold;
    } else {
        fStyle = FontStyleRegular;
    }
    return fStyle;
}

//菜单鼠标点击事件处理
int T_Menu::MenuMouseClick(int x, int y) {
    m_index = GetMenuIndex(x, y);
    if (m_index >= 0) {
        /*
        if(m_MoveSound && m_ClickSound)
        {
            m_MoveSound->Restore();
            m_ClickSound->Restore();
            m_ClickSound->Play(false);
        }
        */
    }
    return m_index;
}

//菜单鼠标移动事件处理
void T_Menu::MenuMouseMove(int x, int y) {
    lastIndex = m_index;//记录前一次的索引值
    m_index = GetMenuIndex(x, y);
    if (m_index >= 0) {
        isItemFocused = true;
        //保证鼠标移过按钮只播放一次声音
        if (lastIndex != m_index) {
            /*
            if(m_MoveSound && m_ClickSound)
            {
                m_ClickSound->Restore();
                m_MoveSound->Restore();
                m_MoveSound->Play(false);
            }
            */
        }
    } else {
        isItemFocused = false;
    }
}

int T_Menu::MenuKeyDown(WPARAM key) {
    if (key == VK_UP || key == VK_LEFT) {
        m_index = m_index - 1;
        if (m_index < 0) {
            m_index = (int) (gm_menuItems.size() - 1);
        }

        isItemFocused = true;
        /*
        if(m_MoveSound && m_ClickSound)
        {
            m_ClickSound->Restore();
            m_MoveSound->Restore();
            m_MoveSound->Play(false);
        }
        */
    }
    if (key == VK_DOWN || key == VK_RIGHT) {
        m_index = m_index + 1;
        if (m_index > (int) (gm_menuItems.size() - 1)) {
            m_index = 0;
        }

        isItemFocused = true;
        /*
        if(m_MoveSound && m_ClickSound)
        {
            m_ClickSound->Restore();
            m_MoveSound->Restore();
            m_MoveSound->Play(false);
        }
        */
    }
    return m_index;
}

void T_Menu::DestroyAll() {
    // 删除菜单背景
    if (gm_menuBkg.GetBmpHandle() != NULL) {
        gm_menuBkg.Destroy();
    }
    // 删除按钮图片
    if (BtnDIB.GetBmpHandle() != NULL) {
        BtnDIB.Destroy();
    }
    gm_menuItems.clear();
    vector<MENUITEM> emptyVec;
    gm_menuItems.swap(emptyVec);
}
