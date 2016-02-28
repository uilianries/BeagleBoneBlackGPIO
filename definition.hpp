#ifndef BBB_GPIO_DEFINITION_HPP_
#define BBB_GPIO_DEFINITION_HPP_

namespace bbb {
namespace gpio {

    static constexpr unsigned index_max = 115;
    static constexpr auto gpio_class_path = "/sys/class/gpio";
    static constexpr auto gpio_dir_prefix = "gpio";
    static constexpr auto export_file_name = "export";
    static constexpr auto value_file_name = "value";
    static constexpr auto direction_file_name = "direction";

    enum class pin_level : int { low,
                                 high };

    enum class stream_direction : int { input,
                                        output,
                                        bidirectional };
}
}

#endif // BBB_GPIO_DEFINITION_HPP_
