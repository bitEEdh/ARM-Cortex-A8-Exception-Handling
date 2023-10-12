#include <main.h>
#include <s5pv210-irq.h>
/* print the value of coprocessor register CP15-C1 */
void print_state(u32_t cp15_c1)
{
	serial_printf(0, "CP15_C1 = 0x%x\r\n", cp15_c1);
}

void led_init(void)
{
	/* LED1 */
	writel(S5PV210_GPJ0CON, (readl(S5PV210_GPJ0CON) & ~(0xf<<12)) | (0x1<<12));
	writel(S5PV210_GPJ0PUD, (readl(S5PV210_GPJ0PUD) & ~(0x3<<6)) | (0x2<<6));
	writel(S5PV210_GPJ0DAT, (readl(S5PV210_GPJ0DAT) & ~(0x1<<3)) | (0x1<<3));

	/* LED2 */
	writel(S5PV210_GPJ0CON, (readl(S5PV210_GPJ0CON) & ~(0xf<<16)) | (0x1<<16));
	writel(S5PV210_GPJ0PUD, (readl(S5PV210_GPJ0PUD) & ~(0x3<<8)) | (0x2<<8));
	writel(S5PV210_GPJ0DAT, (readl(S5PV210_GPJ0DAT) & ~(0x1<<4)) | (0x1<<4));

	/* LED3 */
	writel(S5PV210_GPJ0CON, (readl(S5PV210_GPJ0CON) & ~(0xf<<20)) | (0x1<<20));
	writel(S5PV210_GPJ0PUD, (readl(S5PV210_GPJ0PUD) & ~(0x3<<10)) | (0x2<<10));
	writel(S5PV210_GPJ0DAT, (readl(S5PV210_GPJ0DAT) & ~(0x1<<5)) | (0x1<<5));

	/* LED4 */
	writel(S5PV210_GPD0CON, (readl(S5PV210_GPD0CON) & ~(0xf<<4)) | (0x1<<4));
	writel(S5PV210_GPD0PUD, (readl(S5PV210_GPD0PUD) & ~(0x3<<2)) | (0x2<<2));
	writel(S5PV210_GPD0DAT, (readl(S5PV210_GPD0DAT) & ~(0x1<<1)) | (0x1<<1));
}

void led_set(int id, int on)
{
	switch(id)
	{
	case 0:
		if(on)
			writel(S5PV210_GPJ0DAT, (readl(S5PV210_GPJ0DAT) & ~(0x1<<3)) | (0x0<<3));
		else
			writel(S5PV210_GPJ0DAT, (readl(S5PV210_GPJ0DAT) & ~(0x1<<3)) | (0x1<<3));
		break;

	case 1:
		if(on)
			writel(S5PV210_GPJ0DAT, (readl(S5PV210_GPJ0DAT) & ~(0x1<<4)) | (0x0<<4));
		else
			writel(S5PV210_GPJ0DAT, (readl(S5PV210_GPJ0DAT) & ~(0x1<<4)) | (0x1<<4));
		break;

	case 2:
		if(on)
			writel(S5PV210_GPJ0DAT, (readl(S5PV210_GPJ0DAT) & ~(0x1<<5)) | (0x0<<5));
		else
			writel(S5PV210_GPJ0DAT, (readl(S5PV210_GPJ0DAT) & ~(0x1<<5)) | (0x1<<5));
		break;

	case 3:
		if(on)
			writel(S5PV210_GPD0DAT, (readl(S5PV210_GPD0DAT) & ~(0x1<<1)) | (0x0<<1));
		else
			writel(S5PV210_GPD0DAT, (readl(S5PV210_GPD0DAT) & ~(0x1<<1)) | (0x1<<1));
		break;

	default:
		break;
	}
}

/* turn on the corresponding led */
void do_led_on(u32_t led_num)
{
	led_set(led_num , 1);
}

/* turn off the corresponding led */
void do_led_off(u32_t led_num)
{
	led_set(led_num , 0);
}

/* print the kind of exception and cpsr value */
void print_exception(u32_t cpsr)
{
	switch (cpsr & 0x1f)
	{
		case 0x13:
			serial_printf(0, "Software interrupt occurred!\r\nCPSR = 0x%x\r\n", cpsr);
			break;
		case 0x17:
			serial_printf(0, "Abort interrupt occurred!\r\nCPSR = 0x%x\r\n", cpsr);
			break;
		case 0x1b:
			serial_printf(0, "Undefined instruction interrupt occurred!\r\nCPSR = 0x%x\r\n", cpsr);
			break;
		default:
			serial_printf(0, "No interrupt occurred.\r\nCPSR = 0x%x\r\n", cpsr);
			break;
	}
}

