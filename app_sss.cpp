/**
 ******************************************************************************
 ** �t�@�C���� : app.cpp
 **
 ** �T�v : 2�֓|���U�q���C���g���[�X���{�b�g��TOPPERS/HRP2�pC++�T���v���v���O����
 **
 ** ���L : sample_cpp (���C���g���[�X/�K�����[�^/�����g�Z���T/�����[�g�X�^�[�g)
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

using namespace ev3api;

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

/* Bluetooth */
static int32_t   bt_cmd = 0;      /* Bluetooth�R�}���h 1:�����[�g�X�^�[�g */
static FILE     *bt = NULL;      /* Bluetooth�t�@�C���n���h�� */

/* ���L�̃}�N���͌�/���ɍ��킹�ĕύX�����K�v�������܂� */
#define GYRO_OFFSET           0  /* �W���C���Z���T�I�t�Z�b�g�l(�p���x0[deg/sec]��) */
//#define LIGHT_WHITE          40  /* ���F�̌��Z���T�l */
//#define LIGHT_BLACK           0  /* ���F�̌��Z���T�l */
#define SONAR_ALERT_DISTANCE 30  /* �����g�Z���T�ɂ������Q�����m����[cm] */
#define TAIL_ANGLE_STAND_UP   0  /* ���S���~���̊p�x[�x] */
#define TAIL_ANGLE_DRIVE     60  /* �o�����X���s���̊p�x[�x] */
#define P_GAIN             2.5F  /* ���S���~�p���[�^���������W�� */
#define PWM_ABS_MAX          60  /* ���S���~�p���[�^����PWM���΍ő��l */
//#define DEVICE_NAME     "ET0"  /* Bluetooth�� hrp2/target/ev3.h BLUETOOTH_LOCAL_NAME�Őݒ� */
//#define PASS_KEY        "1234" /* �p�X�L�[    hrp2/target/ev3.h BLUETOOTH_PIN_CODE�Őݒ� */
#define CMD_START         '1'    /* �����[�g�X�^�[�g�R�}���h */

/* LCD�t�H���g�T�C�Y */
#define CALIB_FONT (EV3_FONT_SMALL)
#define CALIB_FONT_WIDTH (6/*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (8/*TODO: magic number*/)

/* �֐��v���g�^�C�v�錾 */
static int32_t sonar_alert(void);
static void tail_control(int32_t angle);

/* �I�u�W�F�N�g�ւ̃|�C���^���` */
TouchSensor*    touchSensor;
SonarSensor*    sonarSensor;
ColorSensor*    colorSensor;
GyroSensor*     gyroSensor;
Motor*          leftMotor;
Motor*          rightMotor;
Motor*          tailMotor;
Clock*          clock;


static Driver*         driver;
static LineMonitor*    lineMonitor;
static ColorMonitor*   colorMonitor;
static Tracer*         tracer;

void tracer_cyc(intptr_t exinf){
    act_tsk(TRACER_TASK);
}

void tracer_task(intptr_t exinf){
    if(ev3_button_is_pressed(LEFT_BUTTON)){
        wup_tsk(MAIN_TASK);
    }else{
        
        tracer->run();

        //int8_t forward;      /* �O���i���� */
        //int8_t turn;         /* ���񖽗� */
        //int8_t pwm_L, pwm_R; /* ���E���[�^PWM�o�� */

       

       

        /* �K�����[�^�[�̃��Z�b�g */
        //tailMotor->reset();
    
        /* Open Bluetooth file */
        // bt = ev3_serial_open_file(EV3_SERIAL_BT);
        // assert(bt != NULL);

        /* Bluetooth�ʐM�^�X�N�̋N�� */
        //act_tsk(BT_TASK);

        
        /* �X�^�[�g�ҋ@ */


            //tail_control(TAIL_ANGLE_STAND_UP); /* ���S���~�p�p�x�ɐ��� */
        
//        if (bt_cmd == 1)
//        {
//            break; /* �����[�g�X�^�[�g */
//        }

       
        

        //clock->sleep(10);
        


        /**
        * Main loop for the self-balance control algorithm
        */
    
        //int32_t motor_ang_l, motor_ang_r;
        //int32_t gyro, volt;

        
        //tail_control(TAIL_ANGLE_DRIVE); /* �o�����X���s�p�p�x�ɐ��� */

        //if (sonar_alert() == 1) /* ���Q�����m */
        //{
        //    forward = turn = 0; /* ���Q�������m���������~ */
        //}
        //else
        //{
        //    forward = 30; /* �O�i���� */
        //    if (lineMonitor->checkBrightness() >= (LIGHT_WHITE + LIGHT_BLACK)/2)
        //    {
        //        turn =  20; /* �����񖽗� */
        //    }
        //    else
        //    {
        //        turn = -20; /* �E���񖽗� */
        //    }
        //}

        /* �|���U�q����API �ɓn���p�����[�^���擾���� */
        //motor_ang_l = leftMotor->getCount();
        //motor_ang_r = rightMotor->getCount();
        //gyro = gyroSensor->getAnglerVelocity();
        //volt = ev3_battery_voltage_mV();

        /* �|���U�q����API���Ăяo���A�|�����s���邽�߂� */
        /* ���E���[�^�o�͒l�𓾂� */
        /*
        balance_control(
            (float)forward,
            (float)turn,
            (float)gyro,
            (float)GYRO_OFFSET,
            (float)motor_ang_l,
            (float)motor_ang_r,
            (float)volt,
            (int8_t *)&pwm_L,
            (int8_t *)&pwm_R);
        */

        /*
        pwm_L = forward + turn;
        pwm_R = forward - turn;


        leftMotor->setPWM(pwm_L);
        rightMotor->setPWM(pwm_R);
        */

        //driver->run(forward,turn);

    //ter_tsk(BT_TASK);
    //fclose(bt);

    
    }
    ext_tsk();
}

/* ���C���^�X�N */
void main_task(intptr_t unused)
{
    //tracer.init();
 /* �e�I�u�W�F�N�g�𐶐��E���������� */
    touchSensor = new TouchSensor(PORT_1);
    colorSensor = new ColorSensor(PORT_2);
    sonarSensor = new SonarSensor(PORT_3);
    gyroSensor  = new GyroSensor(PORT_4);
    leftMotor   = new Motor(PORT_C);
    rightMotor  = new Motor(PORT_B);
    tailMotor   = new Motor(PORT_A);
    clock       = new Clock();
    driver      = new Driver(rightMotor,leftMotor);
    lineMonitor = new LineMonitor(colorSensor);
    colorMonitor= new ColorMonitor(colorSensor);
    tracer      = new Tracer(driver,lineMonitor);
    
     /* LCD���ʕ\�� */
    ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
    ev3_lcd_draw_string("HackEV_Yadamo", 0, CALIB_FONT_HEIGHT*1);

    ev3_led_set_color(LED_ORANGE); /* �����������ʒm */

    
    rgb_raw_t rgb;
    char red[20] = {0};
    char blue[20] = {0};
    char green[20] = {0};
    int push_count = 0;

    while(1){

        if (touchSensor->isPressed() && !touchSensor->isPressed())
         {
             switch(push_count){
                case 0:
                    colorMonitor->checkColor(rgb);
                    sprintf(red, "RED = %3d", (int)rgb.r);
                    sprintf(blue, "BLUE = %3d", (int)rgb.b);
                    sprintf(green, "GREEN = %3d", (int)rgb.g);           
           
                    ev3_lcd_draw_string(red, 0, CALIB_FONT_HEIGHT*2+1);
                    ev3_lcd_draw_string(blue, 0, CALIB_FONT_HEIGHT*3+1);
                    ev3_lcd_draw_string(green, 0, CALIB_FONT_HEIGHT*4+1);

                    push_count++;    
                    break;
                case 1:
                    goto endloop;
                    break;
             }
        }
    }   
    endloop: ;

    /* ���s���[�^�[�G���R�[�_�[���Z�b�g */
    leftMotor->reset();
    rightMotor->reset();
    
    /* �W���C���Z���T�[���Z�b�g */
    gyroSensor->reset();
    //balance_init(); /* �|���U�qAPI������ */

    ev3_led_set_color(LED_GREEN); /* �X�^�[�g�ʒm */

    ev3_sta_cyc(TRACER_CYC);
    slp_tsk();                    // �N�������A���s�����߂�
    ev3_stp_cyc(TRACER_CYC);
    ev3_led_set_color(LED_ORANGE);
    tracer->stop();
    ext_tsk();
}

//*****************************************************************************
// �֐��� : sonar_alert
// ���� : ����
// �Ԃ��l : 1(���Q������)/0(���Q������)
// �T�v : �����g�Z���T�ɂ������Q�����m
//*****************************************************************************
static int32_t sonar_alert(void)
{
    static uint32_t counter = 0;
    static int32_t alert = 0;

    int32_t distance;

    if (++counter == 40/4) /* ��40msec�������ɏ��Q�����m  */
    {
        /*
         * �����g�Z���T�ɂ��鋗�����������́A�����g�̌��������Ɉˑ����܂��B
         * NXT�̏ꍇ�́A40msec�������x���o�����̍ŒZ���������ł��B
         * EV3�̏ꍇ�́A�v�m�F
         */
        distance = sonarSensor->getDistance();
        if ((distance <= SONAR_ALERT_DISTANCE) && (distance >= 0))
        {
            alert = 1; /* ���Q�������m */
        }
        else
        {
            alert = 0; /* ���Q������ */
        }
        counter = 0;
    }

    return alert;
}

//*****************************************************************************
// �֐��� : tail_control
// ���� : angle (���[�^�ڕW�p�x[�x])
// �Ԃ��l : ����
// �T�v : ���s�̊��S���~�p���[�^�̊p�x����
//*****************************************************************************
static void tail_control(int32_t angle)
{
    float pwm = (float)(angle - tailMotor->getCount()) * P_GAIN; /* ���ᐧ�� */
    /* PWM�o�͖O�a���� */
    if (pwm > PWM_ABS_MAX)
    {
        pwm = PWM_ABS_MAX;
    }
    else if (pwm < -PWM_ABS_MAX)
    {
        pwm = -PWM_ABS_MAX;
    }

    tailMotor->setPWM(pwm);
}

//*****************************************************************************
// �֐��� : bt_task
// ���� : unused
// �Ԃ��l : �Ȃ�
// �T�v : Bluetooth�ʐM�ɂ��郊���[�g�X�^�[�g�B Tera Term�Ȃǂ̃^�[�~�i���\�t�g�����A
//       ASCII�R�[�h��1�𑗐M�����ƁA�����[�g�X�^�[�g�����B
//*****************************************************************************
void bt_task(intptr_t unused)
{
    while(1)
    {
        uint8_t c = fgetc(bt); /* ���M */
        switch(c)
        {
        case '1':
            bt_cmd = 1;
            break;
        default:
            break;
        }
        fputc(c, bt); /* �G�R�[�o�b�N */
    }
}
