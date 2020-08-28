#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <linux/input.h>

const struct input_event
lctrl_up	     = { .type = EV_KEY, .code = KEY_LEFTCTRL,	.value = 0 },
lctrl_dn	     = { .type = EV_KEY, .code = KEY_LEFTCTRL,	.value = 1 };

int equal(const struct input_event *first, const struct input_event *second)
{
	return first->type == second->type
		&& first->code == second->code
		&& first->value == second->value;
}

int read_event(struct input_event *event)
{
	return fread(event, sizeof(struct input_event), 1, stdin) == 1;
}

void write_event(const struct input_event *event)
{
	if (fwrite(event, sizeof(struct input_event), 1, stdout) != 1)
		exit(EXIT_FAILURE);
}

int main(void)
{
	int lctrl_is_down = 0,
	    override_ctrl = 0;
	struct input_event input;

	setbuf(stdin, NULL);
	setbuf(stdout, NULL);

	while (read_event(&input)) {
		if (input.type == EV_MSC && input.code == MSC_SCAN)
			continue;

		if (input.type != EV_KEY) {
			write_event(&input);
			continue;
		}

		if (lctrl_is_down) {
			if (equal(&input, &lctrl_dn))
				continue;

			if (equal(&input, &lctrl_up)) {
				lctrl_is_down = 0;
				write_event(&input);
				continue;
			}

			override_ctrl = 1;
			switch(input.code) {
				case KEY_UP:    input.code = KEY_PAGEUP;   break;
				case KEY_DOWN:  input.code = KEY_PAGEDOWN; break;
				case KEY_LEFT:  input.code = KEY_HOME;     break;
				case KEY_RIGHT: input.code = KEY_END;      break;
				default: override_ctrl = 0;
			}
		} else if (equal(&input, &lctrl_dn)) {
			lctrl_is_down = 1;
		}

		if (override_ctrl)
			write_event(&lctrl_up);
		write_event(&input);
	}
}
