#include "ChordNameComponent.h"

//==============================================================================
ChordNameComponent::ChordNameComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess)
{
}

ChordNameComponent::~ChordNameComponent()
{
}

//==============================================================================
void ChordNameComponent::resized()
{

}

//==============================================================================
void ChordNameComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        default: { } break;
    };
}
