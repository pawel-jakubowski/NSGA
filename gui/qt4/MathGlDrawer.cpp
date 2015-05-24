#include "MathGlDrawer.h"
#include <mgl2/surf.h>
#include <QMessageBox>
#include <iostream>
#include <iomanip>

MathGlDrawer::MathGlDrawer()
{
}

void MathGlDrawer::initData(doublesMatrix results)
{
    f1.Create(results[0].size());
    f2.Create(results[0].size());

    for(unsigned i = 0; i != results[0].size(); i++)
    {
        f1.SetVal(results[0][i],i);
        f2.SetVal(results[1][i],i);
        std::cout << "f1 : " << std::setw(20) << std::left << results[0][i]
                  << "f2 : " << std::setw(20) << std::left << results[1][i] << std::endl;
    }
}

int MathGlDrawer::Draw(mglGraph* gr)
{
    gr->Title("NSGA-II");
    gr->Box();
    gr->SetRanges(f1,f2);
    gr->Axis();
    gr->Plot(f1,f2," o");
    gr->Label('y',"f2",0);
    gr->Label('x',"f1",0);

    return 0;
}
