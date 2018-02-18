#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {
    // inputs:
    // - ledkey buttons
    // - beer temperature sensor
    // - chamber temperature sensor
    // - target temperature (hard coded 21 now, no adjustment)
    // - buttons (no use now)
    // outputs:
    // - heater
    // - cooler
    // - fan (always on)
    // - display sensors temperature (segments)
    // - display heating / cooling (leds)
    // state:
    // - time
    // -

    public:
        Controller();
        init();
    private:
};

#endif
