#ifndef DELAY_H
#define DELAY_H

void delay(unsigned ms)
{
    for(unsigned i=0; i<ms; ++i)
    {
        for(volatile unsigned j=0; j<500; ++j);
    }
}

#endif
