/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/
//#define SLAVE_ADDRESS 0x1 //(0x02 shifted by one)
//#define SLAVE_ADDRESS 0x7 //(0x0e shifted by )
//#define SLAVE_ADDRESS 0x3 // (0x06 shifted by one)
#define SLAVE_ADDRESS 0xf // (0x1e shifted by one)
/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */
void InitADC(void);
void SwipeSampling(unsigned int* buffer);
