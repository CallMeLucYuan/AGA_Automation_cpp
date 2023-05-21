#pragma once
typedef enum screen_type_enum
{
    e_1024x768_enum  =  0,
    e_1600x900_enum,
    e_1920x1080_enum,
    e_2560x1440_enum,
    MAX_SCREEN_TYPE
}screen_type_enum;


typedef struct
{
	int width;
	int height;
}screen_size_t;


typedef enum state_enum{
    STAY_STATE,
    STATE_IDLE,
    STATE_SELECT,
    STATE_BATTLE,
    STATE_STOP
}state_enum;

static const screen_size_t screen_size_table[] =
{
    {1024,   768    },
    {1600,   900	},
    {1920,   1080   },
    {2560,   1440   },
};


//#define DEBUG