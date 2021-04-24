#ifndef DATA_CONVERTER_H
#define DATA_CONVERTER_H

#include "../spi/HydraRF/Structure.h"

#include "IncommingCommunicationFormat.h"
#include "OutgoingCommunicationFormat.h"

class DataConverter
{
public:
    static IncommingCommunicationFormat translate(struct sCom* rawRfData);
    static void translate(OutgoingCommunicationFormat* output, AlphaToRemoteCommunicationFormat* convertedOutput);

private:

};

#endif