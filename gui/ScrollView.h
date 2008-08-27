#ifndef __SCROLLVIEW_H
#define __SCROLLVIEW_H

#include "GUI.h"
#include "Slider.h"

class ScrollView : public GUI
{
   friend class GUI;
   friend class Table; // Allow table to add children
   friend class TabWidget;
   public:
      ScrollView(GUI*, TextureManager*);
      ~ScrollView();
      bool FloatsInWidget(float, float);
      float scrollbarwidth;
      void ScrollToBottom();
      
   protected:
      float vpoffsetx, vpoffsety;
      float canvasx, canvasy;
      float scrollamount;
      bool drag;
      SliderPtr vertbar;
      SliderPtr horizbar;
      
      void RecalculateSize();
      void RenderWidget();
      void PostRender();
      virtual void CustomProcessEvent(SDL_Event*);
      virtual void MouseMotion(SDL_Event*);
      virtual void LeftDown(SDL_Event*);
      virtual void WheelDown(SDL_Event*);
      virtual void WheelUp(SDL_Event*);
      virtual void KeyDown(SDL_Event*);
      virtual void GlobalLeftClick(SDL_Event*);
      virtual void ReadNodeExtra(DOMNode*, GUI*);
};

typedef shared_ptr<ScrollView> ScrollViewPtr;

#endif
