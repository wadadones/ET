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
#include "Phase/GaragePhase/GaragePhase.hpp"
#include "Phase/StairPhase/StairPhase.hpp"
#include "Phase/StairPhase2/StairPhase2.hpp"
#include "Phase/StairPhase3/StairPhase3.hpp"
#include "Phase/BeforeStair/BeforeStair.hpp"
#include "Phase/ImmediatePhase/ImmediatePhase.hpp"


//インスタンス作成
EV3 ev3;
Balancer balancer;
Schedule schedule;
Operator ope(&ev3, &balancer, &schedule);
StartPhase st("StartPhase", &balancer, 104);

/*---- stable tuning -----*/
StraightPhase sp1("StraightPhase", &balancer, 50, 70, 1000, 0);
StraightPhase sp3("StraightPhase", &balancer, 70, 70, 2800, 0); //2000 //3000

CurvePhase cp1("CurvePhase", &balancer, 60, 60, 6400, 0, 0, 1.5, 20.0); //2600

CurvePhase cp2("CurvePhase", &balancer, 70, 70, 9400, 0, 0, 1.2, 14.0); //3800

CurvePhase cp3("CurvePhase", &balancer, 55, 55, 11200, 0, 0, 2.0, 20.0);
CurvePhase cp4("CurvePhase", &balancer, 60, 60, 12200, 0, 0, 1.3, 15.0);

StraightPhase spEnd("StraightPhase", &balancer, 70, 70, 14200, 0); //2000
/*------------------------*/

//Stair
AfterGoal ags("AfterGoal", &balancer, 50, 20, 5600, 0, -2, 1.2, 15.0, 3, 92, 3000);
AfterGoal ags2("AfterGoal", &balancer, 20, 0, 1000, 0, -2, 1.2, 15.0, 92, 92, 0);

ImmediatePhase ip("ImmediatePhase", &balancer, 12, 600, 92);

GaragePhase gp2("GaragePhase", &balancer, 30, 30, 114514, 0, 0, 1.7, 0, 92, 3200, 3200, 250);
BeforeStair bs("BeforeStair", &balancer, 85);
StairPhase stair("StairPhase", &balancer);
StairPhase2 stair2("StairPhase", &balancer);
StairPhase3 stair3("StairPhase", &balancer);

//空のスケジュールにPhaseインスタンスをプッシュ
void createSchedule()
{
  schedule.pushPhase(&st);
  schedule.pushPhase(&sp1);
  schedule.pushPhase(&sp3);
  schedule.pushPhase(&cp1);
  schedule.pushPhase(&cp2);
  schedule.pushPhase(&cp3);
  schedule.pushPhase(&cp4);
  schedule.pushPhase(&spEnd);

  schedule.pushPhase(&ags);
  schedule.pushPhase(&ags2);

  schedule.pushPhase(&ip);

  schedule.pushPhase(&gp2);
  schedule.pushPhase(&bs);
  schedule.pushPhase(&stair);
  schedule.pushPhase(&stair2);
  schedule.pushPhase(&stair3);
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
