#ifndef DIGITALTIMER_H
#define DIGITALTIMER_H
#include <QLCDNumber>

class DigitalTimer : public QLCDNumber
{
public:
    DigitalTimer();

private slots:
    void showTime();
};

#endif // DIGITALTIMER_H
