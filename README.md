# arrow2nav

Enable navigation keys on keyboards without PgUp/Dn,Home,End
(such as the Asus ROG Zephyrus G14)

## Why

Navigation keys are useful for scrolling and moving the cursor quickly in
terminals and text editors. Most laptops with compact keyboards will have
function keys instead of dedicated navigation keys, but some laptops forego
them entirely.

This plugin allows the arrow keys to act like navigation keys in combination
with LCTRL.

## Dependencies
- [Interception tools](https://gitlab.com/interception/linux/tools)

## Building
```
git clone https://github.com/jakogut/arrow2nav.git
cd arrow2nav
mkdir build && cd build
cmake ..
make
```

## Execution
`arrow2nav` is an [_Interception Tools_](https://gitlab.com/interception/linux/tools) plugin. A suggested
`udevmon` job configuration is:
```yaml
- JOB: "intercept -g $DEVNODE | arrow2nav | uinput -d $DEVNODE"
  DEVICE:
    EVENTS:
      EV_KEY: [KEY_LEFTCTRL, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT]
```

For more information about the [_Interception Tools_](https://gitlab.com/interception/linux/tools), check
the project's website.
