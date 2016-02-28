#include <unistd.h>

#include "stream.hpp"
#include "definition.hpp"

int main()
{
    constexpr size_t pin_led = 66;
    constexpr auto blink_interval = 1; // seconds:w

    bbb::gpio::ostream ogpio(pin_led);

    for (auto i = 0; i < 3; ++i) {
        ogpio << bbb::gpio::pin_level::high;
        sleep(blink_interval);
        ogpio << bbb::gpio::pin_level::low;
    }

    return 0;
}
