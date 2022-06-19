#include "Simulator.h"

int main()
{
    srand(time(nullptr));
    Simulator& fireworks(Simulator::getInstance());
    
    fireworks.run();
    
    return 0;
}


