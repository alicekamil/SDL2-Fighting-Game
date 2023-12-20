#pragma once

class InputScheme
{
public:
    InputScheme(int up, int down, int left, int right, int punch)
        : up(up),
          down(down),
          left(left),
          right(right),
            punch(punch)
    {
        
    }
    int up;
    int down;
    int left;
    int right;
    int punch;
};
