#include "T_Render.h"

void T_Render::RenderUpdate(HDC hdc)
{
    HDC memDC= CreateCompatibleDC(hdc);
    //HBITMAP hbitmap= CreateCompatibleBitmap(memDC,screenWidth,screenHeight);
    HBITMAP tempBitmap= (HBITMAP)SelectObject(memDC,backgroundBitmap);
    //绘制天空/地
    BitBlt(hdc,0,0,screenWidth,screenHeight,memDC,0,0,SRCCOPY);
    //绘制墙体
    HBITMAP wallBitmap= CreateCompatibleBitmap(hdc,screenWidth,screenHeight);
    int midHeight=screenHeight/2;
    if(camera==nullptr){
        T_GameObjectManager& gm = *T_Scene::activeScene->gameObjectManager;
        for(auto& gameObj:gm.gameObjectArray){
            for(auto& component:gameObj->componentArray){
                if(component->GetComponentName()=="camera"){
                    camera=dynamic_pointer_cast<Camera>(component);
                    break;
                }
            }
            if(camera!=nullptr) break;
        }
    }
    T_Vector3 playerPos=camera->gameObject.transform.position;
    T_Vector3 playerRot=camera->gameObject.transform.rotation;
    for(int lineNum=0;lineNum<screenWidth;++lineNum){
        T_Vector3 touchPos=playerPos;
        wallDepth[lineNum]=MAX_VISIT_LENGHT+1;
        float nowX=playerRot.x-camera->cameraFov/2+lineNum*camera->cameraFov/screenWidth;
        float cosX= cosf(nowX);
        float sinX= sinf(nowX);
        for(float add=LENGHT_SINGLE_VISIT_STEP;add<MAX_VISIT_LENGHT;add+=LENGHT_SINGLE_VISIT_STEP){
            touchPos.x+=cosX*LENGHT_SINGLE_VISIT_STEP;
            touchPos.z+=sinX*LENGHT_SINGLE_VISIT_STEP;
            Rast rast=map.getBlockTypeAt(touchPos);
            if(rast.graphIndex!=0){
                wallDepth[lineNum]=add;
                float lenToWall=add*cosf(nowX-playerRot.x)/3;
                float ratio=1/lenToWall;
                T_Graph::PaintRegion(T_Map::mapWallSprite[rast.graphIndex].GetBmpHandle(),
                                     hdc,
                                     lineNum,midHeight-T_Map::TEXTURE_HEIGHT*ratio/2,
                                     rast.x*T_Map::TEXTURE_WIDTH,0,
                                     1,T_Map::TEXTURE_HEIGHT,
                                     ratio);
                break;
            }
        }
    }

    // 绘制精灵


    SelectObject(memDC,tempBitmap);
    DeleteObject(memDC);
    DeleteObject(tempBitmap);
}

void T_Render::Init(int width, int height) {
    SetRenderVar(width,height);
    HDC memDC= CreateCompatibleDC(GetDC(T_Engine::pEngine->m_hWnd));
    wallDepth=std::vector<float>(width);
    //如果使用内存设备上下文会变成单色Bitmap
    backgroundBitmap= CreateCompatibleBitmap(GetDC(T_Engine::pEngine->m_hWnd),width,height);

    HBITMAP tempBmp=(HBITMAP) SelectObject(memDC,backgroundBitmap);

    int skyBlockHeight=height/(SKY_LEVEL*2)+1;

    for(int level=0;level<SKY_LEVEL;++level){
        HBRUSH brush= CreateSolidBrush(RGB(
                                               (GetRValue(SKY_COLOR_UP)*(SKY_LEVEL-level)+ GetRValue(SKY_COLOR_DOWN)*level)/SKY_LEVEL,
                                               (GetGValue(SKY_COLOR_UP)*(SKY_LEVEL-level)+ GetGValue(SKY_COLOR_DOWN)*level)/SKY_LEVEL,
                                               (GetBValue(SKY_COLOR_UP)*(SKY_LEVEL-level)+ GetBValue(SKY_COLOR_DOWN)*level)/SKY_LEVEL
                                       ));
        RECT rect={0,level*skyBlockHeight,width,(level+1)*skyBlockHeight};
        FillRect(memDC,&rect,brush);
        DeleteObject(brush);
    }
    HBRUSH brush= CreateSolidBrush(GROUND);
    RECT rect={0,height/2,width,height};
    FillRect(memDC,&rect,brush);
    DeleteObject(brush);
    SelectObject(memDC,tempBmp);
    DeleteObject(memDC);
    DeleteObject(tempBmp);
}


void T_Render::SetRenderVar(int width, int height) {
    this->screenWidth=width;
    this->screenHeight=height;
}

T_Render::T_Render(T_Map& tmap):map(tmap) {
    Init(T_Engine::pEngine->wndWidth,T_Engine::pEngine->wndHeight);
}

Camera::Camera(T_GameObject& tGameObject): T_Component(tGameObject) {

}
