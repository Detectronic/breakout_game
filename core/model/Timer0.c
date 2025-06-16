/**
 ********************************************************************************
 * @file    ${file_name}
 * @author  ${user}
 * @date    ${date}
 * @brief
 ********************************************************************************
 */

/*******************************************************************************
 *
 * INCLUDES
 *
 ******************************************************************************/
#include "Timer0.h"

/*******************************************************************************
 *
 * EXTERN VARIABLES
 *
 ******************************************************************************/

bool timer = false;

/*******************************************************************************
 *
 * PRIVATE MACROS AND DEFINES
 *
 ******************************************************************************/

/*******************************************************************************
 *
 * PRIVATE TYPEDEFS
 *
 ******************************************************************************/

/*******************************************************************************
 *
 * STATIC VARIABLES
 *
 ******************************************************************************/
bool Timer0_OF = false;

/*******************************************************************************
 *
 * GLOBAL VARIABLES
 *
 ******************************************************************************/

/*******************************************************************************
 *
 * STATIC FUNCTION PROTOTYPES
 *
 ******************************************************************************/

/*******************************************************************************
 *
 * STATIC FUNCTIONS
 *
 ******************************************************************************/
void Timer0_Init(void)
{

	TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;

	//Disable timer
	timerInit.enable = false;

	//Enable clock
	CMU_ClockEnable(cmuClock_TIMER0,true);

	TIMER_Init(TIMER0,&timerInit);

	//Timer top value
	uint32_t timerfreq = CMU_ClockFreqGet(cmuClock_TIMER0) / (timerInit.prescale + 1);
	uint32_t timerTopval = timerfreq / TIMER0_FREQUENCY;
	TIMER_TopSet(TIMER0,timerTopval);

	//Interrupt enable
	TIMER_IntEnable(TIMER0, TIMER_IEN_OF);
	NVIC_EnableIRQ(TIMER0_IRQn);

}

void Timer0_Enable(void)
{
	uint32_t flags = TIMER_IntGet(TIMER0);
	TIMER_IntClear(TIMER0,flags);
	TIMER_Enable(TIMER0,true);
}

void Timer0_Disable(void)
{
	uint32_t flags = TIMER_IntGet(TIMER0);
	TIMER_IntClear(TIMER0,flags);
	TIMER_Enable(TIMER0,false);
}

void TIMER0_IRQHandler(void)
{
	uint32_t flags = TIMER_IntGet(TIMER0);
	TIMER_IntClear(TIMER0,flags);

    GPIO_PinOutSet(LEDPORT,LEDPIN);
	Timer0_OF = true;

    if (state == GAME ){

    	if (!timer){

    		printf("\n(GAME)            TIMER0_IRQHandler");
			timer = true;

			}

    	memlcd_game(Pmove);


    }

    else if (state == TEST ){

		if (!timer){

			printf("\n(TEST)            TIMER0_IRQHandler");
			timer = true;

			}

		memlcd_game(Pmove);


	}


    GPIO_PinOutClear(LEDPORT,LEDPIN);

}
/*******************************************************************************
 *
 * GLOBAL FUNCTIONS
 *
 ******************************************************************************/
