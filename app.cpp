/**
******************************************************************************
** ?��t?��@?��C?��?��?��?�� : app.cpp
**
** ?��T?��v : 2?��֓|?��?��?��U?��q?��?��?��C?��?��?��g?��?��?��[?��X?��?��?��{?��b?��g?��?��TOPPERS/HRP2?��pC++?��T?��?��?��v?��?��?��v?��?��?��O?��?��?��?��
**
** ?��?��?��L : sample_cpp (?��?��?��C?��?��?��g?��?��?��[?��X/?��K?��?��?��?��?��[?��^/?��?��?��?��?��g?��Z?��?��?��T/?��?��?��?��?��[?��g?��X?��^?��[?��g)
******************************************************************************
**/

#include "ev3api.h"
#include "app.h"
#include "balancer.h"
#include "TouchSensor.h"
#include "SonarSensor.h"
#include "ColorSensor.h"
#include "GyroSensor.h"
#include "Motor.h"
#include "Clock.h"
#include "Sensor.h"
#include "driver.h"
#include "lineMonitor.h"
#include "colorMonitor.h"
#include "tracer.h"
#include "calibration.h"
#include "mileage.h"
//#include "basicCourse.h"
#include "armControler.h"
#include "changeEdge.h"
#include "etzumo.h"
#include "straightRunner.h"
#include "Logger.h"
#include "revolver.h"
#include "blockErea.h"
#include "returnLine.h"
#include "basicCourseR.h"



using namespace ev3api;

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

/* Bluetooth */
static int32_t   bt_cmd = 0;      /* Bluetooth?��R?��}?��?��?��h 1:?��?��?��?��?��[?��g?��X?��^?��[?��g */
static FILE     *bt = NULL;      /* Bluetooth?��t?��@?��C?��?��?��n?��?��?��h?��?�� */

/* ?��?��?��L?��̃}?��N?��?��?��͌�/?���?��ɍ�?�����?��ĕύX?��?��?��?��?��K?��v?��?��?��?��?��?��?��܂� */
#define GYRO_OFFSET           0  /* ?��W?��?��?��C?��?��?��Z?��?��?��T?��I?��t?��Z?��b?��g?��l(?��p?��?��?��x0[deg/sec]?��?��) */
//#define LIGHT_WHITE          40  /* ?��?��?��F?��̌�?��Z?��?��?��T?��l */
//#define LIGHT_BLACK           0  /* ?��?��?��F?��̌�?��Z?��?��?��T?��l */
#define SONAR_ALERT_DISTANCE 30  /* ?��?��?��?��?��g?��Z?��?��?��T?��ɂ�?��?��?��?��?��Q?��?��?��?��?��m?��?��?��?��[cm] */
#define ARM_ANGLE_UP          90  /* ?��?��?��S?��?��?��~?��?��?��̊p?��x[?��x] */
#define ARM_ANGLE_DOWN        0  /* ?��o?��?��?��?��?��X?��?��?��s?��?��?��̊p?��x[?��x] */
#define ARM_ANGLE_BLOCK		  65
#define P_GAIN             2.5F  /* ?��?��?��S?��?��?��~?��p?��?��?��[?��^?��?��?��?��?��?��?��?��?��W?��?�� */
#define PWM_ABS_MAX          60  /* ?��?��?��S?��?��?��~?��p?��?��?��[?��^?��?��?��?��PWM?��?��?��΍ő�?��l */
//#define DEVICE_NAME     "ET0"  /* Bluetooth?��?�� hrp2/target/ev3.h BLUETOOTH_LOCAL_NAME?��Őݒ� */
//#define PASS_KEY        "1234" /* ?��p?��X?��L?��[    hrp2/target/ev3.h BLUETOOTH_PIN_CODE?��Őݒ� */
#define CMD_START         '1'    /* ?��?��?��?��?��[?��g?��X?��^?��[?��g?��R?��}?��?��?��h */

/* LCD?��t?��H?��?��?��g?��T?��C?��Y */
#define CALIB_FONT (EV3_FONT_SMALL)
#define CALIB_FONT_WIDTH (6/*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (8/*TODO: magic number*/)

/* ?��֐�?��v?��?��?��g?��^?��C?��v?��錾 */
static int32_t sonar_alert(void);


/* ?��I?��u?��W?��F?��N?��g?��ւ̃|?��C?��?��?��^?��?��?��` */
TouchSensor*    touchSensor;
SonarSensor*    sonarSensor;
ColorSensor*    colorSensor;
GyroSensor*     gyroSensor;
Motor*          leftMotor;
Motor*          rightMotor;
Motor*          armMotor;
Clock*          clock;

static Driver*         driver;
static LineMonitor*    lineMonitor;
static ColorMonitor*   colorMonitor;
static Tracer*         tracer;
static Calibration*    calibration;
static Mileage*        mileage;
static BasicCourseR*    basicCourseR;
static ArmControler*   armControler;
static ChangeEdge*     changeEdge;
static Etzumo*         etzumo;
static StraightRunner* straightRunner;
static Logger*         logger;
static Revolver*       revolver;
static ReturnLine*	   returnLine;
static BlockErea*      blockErea;



bool test_flag = false;
bool debug;
rgb_raw_t test;
int test_time;
int fase;

void tracer_cyc(intptr_t exinf){
	act_tsk(TRACER_TASK);
}

void tracer_task(intptr_t exinf){
	if(ev3_button_is_pressed(LEFT_BUTTON)){
		wup_tsk(MAIN_TASK);
	}else{

		if(test_flag == false){
			test_time = clock->now();
			test_flag = true;
		}
		logger->addData(clock->now() - test_time);

		//logger->addData(gyroSensor->getAnglerVelocity());

		//tracer->setMode(1);
		//tracer->setCommand(30,0);
		//tracer->run();
		//armControler->armControl(ARM_ANGLE_BLOCK);
		//armControler->armControl(ARM_ANGLE_DOWN);
		//etzumo->etzumoRun(0);
		//basicCourse->run();

		/*
		if(clock->now() - test_time < 2000){
		int a = lineMonitor->checkBrightness();
		//straightRunner->setForward(50);
		//straightRunner->straightRun();
		//revolver->setForward(0);
		//debug = revolver->revolve(10000);
		tracer->setCommand(30, 0);
		tracer->run();
		}else straightRunner->stop();
		*/


		//revolver->setForward(0);
		//debug = revolver->toRevolve(3);
		//debug = revolver->revolve(270);
		//int i = mileage->orientation();
		//logger->addData(i);
		//logger->addData(mileage->mileageL());
		//logger->addData(mileage->mileageR());
		//if(debug) logger->addData(10);


		switch(fase){
		case 0:
			if(blockErea->run()){
				fase=2;
			}
			break;

		case 1:
			if(!basicCourseR->run()){
				fase=2;
			}
			break;

		case 2:
			tracer->stop();
			break;
		}

		/*
		if(fase == 0){
			if(blockErea->circleCatch()) fase++;
		}else tracer->stop();
		*/

		/*

		colorMonitor->checkColor(test);

		tracer->setMode(1);

		ev3_speaker_stop();

		if(colorMonitor->colorJudge2(test,0)==0 ) ev3_speaker_play_tone(261.63, 2);
		if(colorMonitor->colorJudge2(test,0)==1 ) ev3_speaker_play_tone(659.25, 2);
		if(colorMonitor->colorJudge2(test,0)==2 ) ev3_speaker_play_tone(1396.91, 2);
		if(colorMonitor->colorJudge2(test,0)==3 ) ev3_speaker_play_tone(1975.53, 2);

		if(colorMonitor->colorJudge(test,0)==10){
			tracer->setCommand(10,0);
			tracer->run();
		}else tracer->stop();

		*/

		logger->send();
	}
	ext_tsk();
}


/* ?��?��?��C?��?��?��^?��X?��N */
void main_task(intptr_t unused)
{
	//int8_t forward;      /* ?��O?��?��?��i?��?��?��?�� */
	//int8_t turn;         /* ?��?��?��?��� */
	//int8_t pwm_L, pwm_R; /* ?��?��?��E?��?��?��[?��^PWM?��o?��?�� */

	/* ?��e?��I?��u?��W?��F?��N?��g?��?���?��E?��?��?��?��?��?��?��?��?��?�� */

	logger      = new Logger();
	touchSensor = new TouchSensor(PORT_1);
	colorSensor = new ColorSensor(PORT_2);
	sonarSensor = new SonarSensor(PORT_3);
	gyroSensor  = new GyroSensor(PORT_4);
	leftMotor   = new Motor(PORT_B);
	rightMotor  = new Motor(PORT_C);
	armMotor    = new Motor(PORT_A);
	clock       = new Clock();
	driver      = new Driver(rightMotor,leftMotor, logger);
	lineMonitor = new LineMonitor(colorSensor, logger);
	colorMonitor= new ColorMonitor(colorSensor, logger);
	tracer      = new Tracer(driver,lineMonitor, logger, colorMonitor);
	calibration = new Calibration(touchSensor, lineMonitor, colorMonitor);
	mileage     = new Mileage(leftMotor, rightMotor);
	changeEdge  = new ChangeEdge(driver);
	armControler= new ArmControler(armMotor);
	etzumo      = new Etzumo(colorMonitor, lineMonitor, driver, mileage, tracer);
	straightRunner = new StraightRunner(driver, mileage);
	revolver    = new Revolver(driver, mileage);
	returnLine	= new ReturnLine(straightRunner, revolver, lineMonitor, mileage);
	blockErea	= new BlockErea(straightRunner, mileage, revolver, tracer, armControler, colorMonitor, lineMonitor, returnLine, logger);
	basicCourseR = new BasicCourseR(mileage, tracer, changeEdge,straightRunner, logger);

	/* LCD?��?��?��ʕ\?��?�� */
	ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
	ev3_lcd_draw_string("HackEV_Yadamo", 0, CALIB_FONT_HEIGHT*1);

	/* ?��K?��?��?��?��?��[?��^?��[?���??��?��Z?��b?��g */
	//tailMotor->reset();

	/* Open Bluetooth file */
	//bt = ev3_serial_open_file(EV3_SERIAL_BT);
	//assert(bt != NULL);

	/* Bluetooth?��ʐM?��^?��X?��N?��̋N?��?�� */
	//act_tsk(BT_TASK);

	ev3_led_set_color(LED_ORANGE); /* ?��?��?��?��?��?��?��?��?��?��?��ʒm */

	/* ?��X?��^?��[?��g?��ҋ@ */
	rgb_raw_t rgb[3];
	int8_t black;
	int8_t white;

	test_time = clock->now();

	fase = 1;

	calibration->calibrate(rgb, black, white);


	tracer->setTargetBrightness(black, white);
	tracer->setTargetColor(rgb[0], rgb[1]);

	/* ?��?��?��s?��?��?��[?��^?��[?��G?��?��?��R?��[?��_?��[?��?��?��Z?��b?��g */
	//leftMotor->reset();
	//rightMotor->reset();
	mileage->init();

	/* ?��W?��?��?��C?��?��?��Z?��?��?��T?��[?��?��?��Z?��b?��g */
	gyroSensor->reset();
	//balance_init(); /* ?��|?��?��?��U?��qAPI?��?��?��?��?��?�� */



	ev3_led_set_color(LED_GREEN); /* ?��X?��^?��[?��g?��ʒm */

	ev3_sta_cyc(TRACER_CYC);
	slp_tsk();
	ev3_stp_cyc(TRACER_CYC);
	ev3_led_set_color(LED_ORANGE);
	tracer->stop();
	//ter_tsk(BT_TASK);
	//fclose(bt);

	ext_tsk();
}

//*****************************************************************************
// ?��֐�?��?�� : sonar_alert
// ?��?��?��?�� : ?��?��?��?��
// ?��Ԃ�?��l : 1(?��?��?��Q?��?��?��?��?��?��)/0(?��?��?��Q?��?��?��?��?��?��)
// ?��T?��v : ?��?��?��?��?��g?��Z?��?��?��T?��ɂ�?��?��?��?��?��Q?��?��?��?��?��m
//*****************************************************************************
static int32_t sonar_alert(void)
{
	static uint32_t counter = 0;
	static int32_t alert = 0;

	int32_t distance;

	if (++counter == 40/4) /* ?��?��40msec?��?��?��?��?��?��?��ɏ�?��Q?��?��?��?��?��m  */
	{
		/*
		* ?��?��?��?��?��g?��Z?��?��?��T?��ɂ�?��鋗�?��?��?��?��?��?��?��?��?��?��́A?��?��?��?��?��g?��̌�?��?��?��?��?��?��?��Ɉˑ�?��?��?��܂�?��B
		* NXT?��̏ꍇ?��́A40msec?��?��?��?��?��?��?��x?��?��?��o?��?��?��?��?��̍ŒZ?��?��?��?��?��?��?��?��?��ł�?��B
		* EV3?��̏ꍇ?��́A?��v?��m?��F
		*/
		distance = sonarSensor->getDistance();
		if ((distance <= SONAR_ALERT_DISTANCE) && (distance >= 0))
		{
			alert = 1; /* ?��?��?��Q?��?��?��?��?��?��?��m */
		}
		else
		{
			alert = 0; /* ?��?��?��Q?��?��?��?��?��?�� */
		}
		counter = 0;
	}

	return alert;
}



//*****************************************************************************
// ?��֐�?��?�� : bt_task
// ?��?��?��?�� : unused
// ?��Ԃ�?��l : ?��Ȃ�
// ?��T?��v : Bluetooth?��ʐM?��ɂ�?��郊�?��?��[?��g?��X?��^?��[?��g?��B Tera Term?��Ȃǂ̃^?��[?��~?��i?��?��?��\?��t?��g?��?��?��?��?��A
//       ASCII?��R?��[?��h?��?��1?��?��M?��?��?��?��?��ƁA?��?��?��?��?��[?��g?��X?��^?��[?��g?��?��?��?��?��B
//*****************************************************************************
void bt_task(intptr_t unused)
{
	while(1)
	{
		uint8_t c = fgetc(bt); /* ?��?��?��M */
		switch(c)
		{
		case '1':
			bt_cmd = 1;
			break;
		default:
			break;
		}
		fputc(c, bt); /* ?��G?��R?��[?��o?��b?��N */
	}
}
