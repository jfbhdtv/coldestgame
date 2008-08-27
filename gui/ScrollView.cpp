#include "ScrollView.h"

ScrollView::ScrollView(GUI* p, TextureManager* tm) : vpoffsetx(0), vpoffsety(0),
                       scrollbarwidth(20.f), drag(false)
{
   Init(p, tm);
   
   vertbar = SliderPtr(new Slider(this, tm));
   vertbar->visible = true;
   vertbar->orientation = Slider::Vertical;
   horizbar = SliderPtr(new Slider(this, tm));
   horizbar->visible = true;
}


ScrollView::~ScrollView()
{
   //Cleanup();
}


void ScrollView::RenderWidget()
{
   //RenderBase();
   
   vertbar->width = scrollbarwidth;
   vertbar->height = height;
   vertbar->x = width - vertbar->width;
   vertbar->y = 0.f;
   horizbar->width = width;
   horizbar->height = scrollbarwidth;
   horizbar->x = 0.f;
   horizbar->y = height - horizbar->height;
   
   vertbar->Render();
   horizbar->Render();
   
   vpoffsetx = horizbar->value;
   vpoffsety = vertbar->value;
   
   // xoff and yoff are slightly different for scrollviews, the rest of the class expects
   // xoff - vpoffsetx as the value for xoff (same for yoff)
   xoff -= vpoffsetx;
   yoff -= vpoffsety;
   
   // Children are now rendered by the base Render function, we just need to turn on scissoring
   glEnable(GL_SCISSOR_TEST);
   int scissorcoords[4];
   scissorcoords[0] = (int)((x + xoff + vpoffsetx) * wratio);
   scissorcoords[1] = (int)(actualh - (y + yoff + height + vpoffsety) * hratio);
   scissorcoords[2] = (int)((width - scrollbarwidth) * wratio);
   scissorcoords[3] = (int)(height * hratio);
   glScissor(scissorcoords[0], scissorcoords[1], scissorcoords[2], scissorcoords[3]);
}


void ScrollView::PostRender()
{
   // And then turn it off again here
   glDisable(GL_SCISSOR_TEST);
}


void ScrollView::CustomProcessEvent(SDL_Event* event)
{
   RecalculateSize();
   vertbar->ProcessEvent(event);
   horizbar->ProcessEvent(event);
}


void ScrollView::MouseMotion(SDL_Event* event)
{
}


void ScrollView::LeftDown(SDL_Event* event)
{
}

void ScrollView::GlobalLeftClick(SDL_Event* event)
{
}


void ScrollView::WheelDown(SDL_Event* event)
{
   vpoffsety += 50.f;
   yoff -= 50.f;
   if (vpoffsety + height > canvasy)
   {
      yoff += (vpoffsety + height - canvasy);
      vpoffsety = canvasy - height;
   }
   vertbar->value = int(vpoffsety);
}


void ScrollView::WheelUp(SDL_Event* event)
{
   vpoffsety -= 50.f;
   yoff += 50.f;
   if (vpoffsety < 0)
   {
      yoff += vpoffsety;
      vpoffsety = 0;
   }
   vertbar->value = int(vpoffsety);
}


void ScrollView::KeyDown(SDL_Event* event)
{
   switch (event->key.keysym.sym)
   {
      case SDLK_UP:
         vpoffsety -= 5.f;
         yoff += 5.f;
         if (vpoffsety < 0)
         {
            yoff += vpoffsety;
            vpoffsety = 0;
         }
         break;
      case SDLK_DOWN:
         vpoffsety += 5.f;
         yoff -= 5.f;
         if (vpoffsety + height > canvasy)
         {
            yoff += (vpoffsety + height - canvasy);
            vpoffsety = canvasy - height;
         }
         break;
      default:
         break;
   }
}


void ScrollView::RecalculateSize()
{
   canvasx = width;
   canvasy = height;
   guiiter i;
   for (i = children.begin(); i != children.end(); ++i)
   {
      GUIPtr iptr = *i;
      if (iptr->x + iptr->width > canvasx) canvasx = iptr->x + iptr->width;
      if (iptr->y + iptr->height > canvasy) canvasy = iptr->y + iptr->height;
   }
   if (canvasx - 1e-4f > width)
   {
      horizbar->visible = true;
      horizbar->forceslidersize = width * (width / canvasx);
      horizbar->SetRange(0, int(canvasx - width) + 1);
   }
   else
      horizbar->visible = false;
   if (canvasy - 1e-4f > height)
   {
      vertbar->visible = true;
      vertbar->forceslidersize = height * (height / canvasy);
      vertbar->SetRange(0, int(canvasy - height) + 1);
   }
   else
      vertbar->visible = false;
}


bool ScrollView::FloatsInWidget(float xcoord, float ycoord)
{
   if (xcoord > ((x + xoff + vpoffsetx) * wratio) &&
       xcoord < ((x + xoff + width + vpoffsetx) * wratio) &&
       ycoord > ((y + yoff + vpoffsety) * hratio) &&
       ycoord < ((y + yoff + height + vpoffsety) * hratio))
      return true;
   return false;
}


void ScrollView::ScrollToBottom()
{
   RecalculateSize();
   vpoffsety = canvasy - height;
}


void ScrollView::ReadNodeExtra(DOMNode* current, GUI* parentw)
{
   vertbar->textures = ReadTextures(current, "v");
   horizbar->textures = ReadTextures(current, "h");
}
