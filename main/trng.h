// From:
// https://forum.pjrc.com/threads/34808-K66-Beta-Test?p=107134&viewfull=1#post107134

#define RNG_CR (*(volatile uint32_t *)0x40029000) // RNGA Control Register
#define RNG_SR (*(volatile uint32_t *)0x40029004) // RNGA Status Register
#define RNG_ER (*(volatile uint32_t *)0x40029008) // RNGA Entropy Register
#define RNG_OR (*(volatile uint32_t *)0x4002900C) // RNGA Output Register

#define RNG_CR_GO_MASK        0x1u
#define RNG_CR_HA_MASK        0x2u
#define RNG_CR_INTM_MASK      0x4u
#define RNG_CR_CLRI_MASK      0x8u
#define RNG_CR_SLP_MASK       0x10u
#define RNG_SR_OREG_LVL_MASK  0xFF00u
#define RNG_SR_OREG_LVL_SHIFT 8
#define RNG_SR_OREG_LVL(x)    (((uint32_t)(((uint32_t)(x))<<RNG_SR_OREG_LVL_SHIFT))&RNG_SR_OREG_LVL_MASK)
#define SIM_SCGC6_RNGA        ((uint32_t)0x00000200)

uint32_t trng(){
    RNG_CR |= RNG_CR_GO_MASK;
    while((RNG_SR & RNG_SR_OREG_LVL(0xF)) == 0); // wait
    return RNG_OR;
}
