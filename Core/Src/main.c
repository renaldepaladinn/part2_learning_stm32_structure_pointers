#include <stdint.h>

typedef struct {
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t APB1RSTR;
  volatile uint32_t AHBENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB1ENR;
  volatile uint32_t BDCR;
  volatile uint32_t CSR;
} RCC_TypeDef;

typedef struct {
  volatile uint32_t EVCR;
  volatile uint32_t MAPR;
  volatile uint32_t EXTICR1;
  volatile uint32_t EXTICR2;
  volatile uint32_t EXTICR3;
  volatile uint32_t MAPR2;
} AFIO_TypeDef;

typedef struct {
  volatile uint32_t CRL;
  volatile uint32_t CRH;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t BRR;
  volatile uint32_t LCKR;
} GPIO_TypeDef;

#define PERHIPER_BASE 0x40000000UL
#define AHBPERIPH_BASE (PERHIPER_BASE + 0x00020000UL)
#define RCC_BASE (AHBPERIPH_BASE + 0x00001000UL)

#define APB2PERIPH_BASE (PERHIPER_BASE + 0x00010000UL)
#define AFIO_BASE (APB2PERIPH_BASE + 0x0000000UL)
#define GPIOA_BASE (APB2PERIPH_BASE + 0x00000800UL)
#define GPIOB_BASE (APB2PERIPH_BASE + 0x00000C00UL)
#define GPIOC_BASE (APB2PERIPH_BASE + 0x00001000UL)

#define RCC ((RCC_TypeDef *) RCC_BASE)
#define AFIO ((AFIO_TypeDef *) AFIO_BASE)
#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef *) GPIOC_BASE)

int main(void){
  // Enable Clock for AFIO and GPIOA, GPIOB, GPIOC
  RCC -> APB2ENR |= 0x1D;
  // Disable JTAG and enable SWD
  AFIO -> MAPR &= 0xF8FFFFFF;
  AFIO -> MAPR |= 0x02000000;
  // Clear mode settings GPIOA, GPIOB, GPIOC
  GPIOA -> CRL &= 0x00000000;
  GPIOA -> CRH &= 0x0FF00000;
  GPIOB -> CRL &= 0x00000F00;
  GPIOB -> CRH &= 0x00000000;
  GPIOC -> CRH &= 0x000FFFFF;
  // Set GPIOA, GPIOB, GPIOC as output push-pull, max speed 10 MHz
  GPIOA -> CRL |= 0x11111111;
  GPIOA -> CRH |= 0x10011111;
  GPIOB -> CRL |= 0x11111011;
  GPIOB -> CRH |= 0x11111111;
  GPIOC -> CRH |= 0x11100000;
  // Reset GPIOA, GPIOB, GPIOC Low
  GPIOA -> BSRR = 0x9FFF0000;
  GPIOB -> BSRR = 0xFFFB0000;
  GPIOC -> BSRR = 0xE0000000;
  // Set GPIOA, GPIOB, GPIOC High
  GPIOA -> BSRR = 0x00009FFF;
  GPIOB -> BSRR = 0x0000FFFB;
  GPIOC -> BSRR = 0x0000E000;
}