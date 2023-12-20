#include "Bounds.h"

bool Bounds::CollidesWith(Bounds other)
{
    if (x + w >= other.x &&       // r1 right edge past r2 left
      x <= other.x + other.w &&   // r1 left edge past r2 right
      y + h >= other.y &&         // r1 top edge past r2 bottom
      y <= other.y + other.h)     // r1 bottom edge past r2 top
    {    
        return true;
    }
    return false;
}
