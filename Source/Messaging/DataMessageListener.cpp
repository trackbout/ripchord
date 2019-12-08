#include "DataMessageListener.h"
#include "DataMessageManager.h"

//==============================================================================
DataMessageListener::DataMessageListener()
{
}

DataMessageListener::~DataMessageListener()
{
    DataMessageManager::getInstanceWithoutCreating()->removeListener(this);
}
