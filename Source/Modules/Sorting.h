#pragma once

//==============================================================================
class Forward
{
public:
    //==============================================================================
    static int compareElements (int first, int second)
    {
        return (first < second) ? -1 : ((second < first) ? 1 : 0);
    }
};

//==============================================================================
class Reverse
{
public:
    //==============================================================================
    static int compareElements (int first, int second)
    {
        return (first > second) ? -1 : ((second > first) ? 1 : 0);
    }
};
