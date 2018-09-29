// app.cpp

#include "ev3api.h"
#include "app.hpp"
#include "app_sub.hpp"
#include "EV3/EV3.hpp"
#include "Balancer/balancer.h"
#include "Balancer/BalancerCPP.hpp"
#include "Operator/Operator.hpp"
#include "Schedule/Schedule.hpp"
#include "Phase/Phase.hpp"
#include "Phase/StartPhase/StartPhase.hpp"
#include "Phase/StraightPhase/StraightPhase.hpp"
#include "Phase/CurvePhase/CurvePhase.hpp"
#include "Phase/DetectGoal/DetectGoal.hpp"
#include "Phase/AfterGoal/AfterGoal.hpp"
#include "Phase/DetectNansho/DetectNansho.hpp"
#include "Phase/LookUpGateHandler/LookUpGateHandler.hpp"
#include "Phase/StairPhase/StairPhase.hpp"
#include "Phase/StairPhase2/StairPhase2.hpp"
#include "Phase/StairPhase3/StairPhase3.hpp"
#include "Phase/GaragePhase/GaragePhase.hpp"


//インスタンス作成
EV3 ev3;
Balancer balancer;
Schedule schedule;
Operator ope(&ev3, &balancer, &schedule);
StartPhase st("StartPhase", &balancer, 106);

/*---- stable tuning -----*/
StraightPhase sp1("StraightPhase", &balancer, 50, 70, 1000, 0);
StraightPhase sp3("StraightPhase", &balancer, 70, 70, 2500, 0); //1500

//CurvePhase cp1("CurvePhase", &balancer, 70, 70, 7500, 0, 0, 1.6, 18.0); //4500
CurvePhase cp1("CurvePhase", &balancer, 70, 70, 9000, 0, 0, 1.4, 15.0); //5200
CurvePhase cp2("CurvePhase", &balancer, 60, 60, 10300, 0, 0, 1.8, 20.0); //2600
CurvePhase cp3("CurvePhase", &balancer, 70, 70, 12500, 0, 0, 1.4, 16.0); //1600

StraightPhase spEnd("StraightPhase", &balancer, 70, 70, 14500, 0); //2600
/*------------------------*/
DetectGoal dg("DetectGoal", &balancer,70, 75,1300,0);

AfterGoal ag("AfterGoal", &balancer, 45, 30, 5800, 0, -2, 1.2, 15.0, 3, 3, 3000);
AfterGoal ag2("AfterGoal", &balancer, 30, 30, -1, 0, -2, 1.2, 15.0, 3, 3, 114514);
AfterGoal ag3("AfterGoal", &balancer, 30, 0, 1000, 0, 5, 1.2, 15.0, 3, 93, 0);
AfterGoal ag4("AfterGoal", &balancer, 0, 0, 1000, 0, 5, 1.2, 15.0, 93, 93, 0);
LookUpGateHandler lug("LookUpGateHandler", &balancer);

//GaragePhase gp("GaragePhase", &balancer,30,30,114514,0,0,1.7,0,92);
GaragePhase gp("GaragePhase", &balancer, 30, 30, 114514, 0, 0, 1.7, 0, 92, 5200, 5200, 2000);

//空のスケジュールにPhaseインスタンスをプッシュ
void createSchedule()
{
  schedule.pushPhase(&st);
  schedule.pushPhase(&sp1);
  schedule.pushPhase(&sp3);
  schedule.pushPhase(&cp1);
  schedule.pushPhase(&cp2);
  schedule.pushPhase(&cp3);
  schedule.pushPhase(&spEnd);
//  schedule.pushPhase(&dg);
  schedule.pushPhase(&ag);
  schedule.pushPhase(&ag2);
  schedule.pushPhase(&ag3);
  schedule.pushPhase(&ag4);
  schedule.pushPhase(&lug);
  schedule.pushPhase(&gp);
}

/* メインタスク */
void main_task(intptr_t unused)
{
	//スケジュールを作って
	createSchedule();
	//オペレータを走らせて
	ope.run();
	//おわり
	ext_tsk();
}

/*BlueTooth*タスク*/
void bt_task(intptr_t unused)
{
  while(1)
    {
      uint8_t c = fgetc(ev3.getBT()); /* 受信 */
      switch(c)
        {
        case '1':
          ev3.setBTcmd(1);
          break;
        default:
          break;
        }
      fputc(c, ev3.getBT()); /* エコーバック */
    }
}
