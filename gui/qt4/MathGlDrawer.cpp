#include "MathGlDrawer.h"
#include <mgl2/surf.h>
#include <QMessageBox>

MathGlDrawer::MathGlDrawer()
{
}

void MathGlDrawer::initData(doublesMatrix results)
{
    f1.Create(results[0].size());
    f2.Create(results[0].size());
    g1.Create(results[0].size());
//    g2.Create(results[0].size());
//    g3.Create(results[0].size());
//    g4.Create(results[0].size());
//    g5.Create(results[0].size());


    a.Create(results[0].size());


        for(unsigned i = 0; i != results[0].size(); i++)
        {
            f1.SetVal(results[0][i],i);
            f2.SetVal(results[1][i],i);
        }
}

int MathGlDrawer::Draw(mglGraph* gr)
{
    //initData(results);
    gr->Title("NSGA-II");
    //gr->Rotate(50,60);
    gr->Box();
    gr->SetRanges(f1,f2,a);
    gr->Axis();
    gr->Plot(f1,f2,a);

    return 0;
}
