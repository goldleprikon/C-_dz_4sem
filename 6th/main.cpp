#include <iostream>
#include <string>

#include "checkpointdirector.h"



int main()
{
    ObligatoryCheckPointBuilder builder_obl;
    OptionalCheckPointBuilder builder_opt;
    CheckPointDirector director_obl(&builder_obl);
    CheckPointDirector director_opt(&builder_opt);

    // Создание обязательной контрольной точки
    CheckPoint cp1 = director_obl.constructCheckPoint("required CP", 45.0, 30.0, 0);

    // Создание необязательной контрольной точки
    CheckPoint cp2 = director_opt.constructCheckPoint("optional CP", 60.0, 40.0, 1.5);

    std::cout << "list CP:" << std::endl;
    cp1.displayInfo();
    cp2.displayInfo();

    double totalPenalty = 0;
    if (cp1.penaltyTime > 0) {
        totalPenalty += cp1.penaltyTime;
    }
    if (cp2.penaltyTime > 0) {
        totalPenalty += cp2.penaltyTime;
    }

    std::cout << "total penalty: " << totalPenalty << " h" << std::endl;
    return 0;
}
